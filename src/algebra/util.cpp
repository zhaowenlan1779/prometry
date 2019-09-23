// Copyright 2019 Zhupengfei and others
// All rights reserved.

#include <symengine/expression.h>
#include <symengine/visitor.h>
#include "algebra/algebra.h"
#include "algebra/util.h"
#include "common/assert.h"

namespace Algebra {

/**
 * Visits items of an expression, checking whether its sign can be determined and what it is
 * if possible.
 */
class SignVisitor : public SymEngine::BaseVisitor<SignVisitor> {
public:
    s8 sign = 1;

    void bvisit(const SymEngine::Number& x) {
        if (x.is_positive())
            sign = 1;
        else if (x.is_negative())
            sign = -1;
        else
            sign = 0;
    }

    void bvisit(const SymEngine::Add& x) {
        s8 cur_sign = -2; // Undetermined
        for (const auto& iter : x.get_args()) {
            iter->accept(*this);
            if (cur_sign != -2 && sign != cur_sign) {
                sign = 0;
                return;
            } else {
                cur_sign = sign;
            }
        }
        sign = cur_sign;
    }

    void bvisit(const SymEngine::Mul& x) {
        s8 cur_sign = 1;
        for (const auto& iter : x.get_args()) {
            iter->accept(*this);
            cur_sign *= sign;
        }
        sign = cur_sign;
    }

    void bvisit(const SymEngine::Pow& x) {
        sign = 1;
    }

    void bvisit(const SymEngine::Symbol& x) {
        sign = 1;
    }

    void bvisit(const SymEngine::Constant& x) {
        if (SymEngine::eq(x, *SymEngine::pi)) {
            sign = 1;
        } else {
            std::cout << x.get_name() << std::endl;
            UNREACHABLE_MSG("Unknown constant in SignVisitor!");
        }
    }

    void bvisit(const SymEngine::Basic& x) {
        std::cout << x.__str__() << std::endl;
        UNREACHABLE_MSG("Unimplemented basic in SignVisitor!");
    }

    s8 accept(const SymEngine::Basic& x) {
        x.accept(*this);
        return sign;
    }
};

s8 CheckSign(const SymEngine::RCP<const SymEngine::Basic>& expr) {
    using namespace SymEngine;
    auto expanded = expand(expr);

    RCP<const Basic> num, den;
    as_numer_denom(expanded, outArg(num), outArg(den));

    SignVisitor visitor;
    s8 numer_sign = visitor.accept(*num);
    s8 denom_sign = visitor.accept(*den);

    return numer_sign * denom_sign;
}

bool IsAcceptable(const SymEngine::Expression& expr) {
    return CheckSign(SymEngine::expand(expr).get_basic()) >= 0;
}

/**
 * Visits items of an expression, dividing it into items that contain square roots
 * and those that do not.
 */
class SqrtVisitor : public SymEngine::BaseVisitor<SqrtVisitor> {
public:
    SymEngine::Expression sqrt_items, non_sqrt_items;
    bool cur = false;
    bool is_mul = false;

    void bvisit(const SymEngine::Add& x) {
        for (const auto& iter : x.get_args()) {
            is_mul = false;
            iter->accept(*this);
        }
    }

    void bvisit(const SymEngine::Mul& x) {
        for (const auto& iter : x.get_args()) {
            cur = false;
            is_mul = true;
            iter->accept(*this);
            if (cur) {
                sqrt_items += SymEngine::Expression(x.rcp_from_this());
                return;
            }
        }
        non_sqrt_items += SymEngine::Expression(x.rcp_from_this());
    }

    void bvisit(const SymEngine::Pow& x) {
        if (SymEngine::eq(*x.get_exp(), *SymEngine::rational(1, 2))) {
            if (is_mul) {
                cur = true;
            } else {
                sqrt_items += SymEngine::Expression(x.rcp_from_this());
            }
        } else {
            if (is_mul) {
                cur = false;
            } else {
                non_sqrt_items += SymEngine::Expression(x.rcp_from_this());
            }
        }
    }

    void bvisit(const SymEngine::Number& x) {
        if (is_mul) {
            cur = false;
        } else {
            non_sqrt_items += SymEngine::Expression(x.rcp_from_this());
        }
    }

    void bvisit(const SymEngine::Symbol& x) {
        if (is_mul) {
            cur = false;
        } else {
            non_sqrt_items += SymEngine::Expression(x.rcp_from_this());
        }
    }

    void bvisit(const SymEngine::Constant& x) {
        if (is_mul) {
            cur = false;
        } else {
            non_sqrt_items += SymEngine::Expression(x.rcp_from_this());
        }
    }

    void bvisit(const SymEngine::Basic& x) {
        std::cout << x.__str__() << std::endl;
        UNREACHABLE_MSG("Unimplemented basic in SqrtVisitor!");
    }

    std::pair<SymEngine::Expression, SymEngine::Expression> accept(const SymEngine::Basic& x) {
        sqrt_items = non_sqrt_items = 0;
        x.accept(*this);
        return {sqrt_items, non_sqrt_items};
    }
};

SymEngine::Expression SimplifyEquation(const SymEngine::Expression& expr) {
    using namespace SymEngine;
    Expression expanded = expand(expr);

    RCP<const Basic> num, den;
    as_numer_denom(expanded.get_basic(), outArg(num), outArg(den));

    SqrtVisitor visitor;
    auto [sqrt_items, non_sqrt_items] = visitor.accept(*num);

    if (sqrt_items == 0) {
        return expand(div(non_sqrt_items.get_basic(), den));
    } else {
        // TODO: Handle limitations here (sqrt_items and non_sqrt_items must be non-negative)
        return SimplifyEquation(
            div(sub(expand(pow(non_sqrt_items, integer(2))), expand(pow(sqrt_items, integer(2)))),
                den));
    }
}

/**
 * Visits items of an expression, dividing it into items that contain symbols
 * and those that do not.
 */
class SymbolVisitor : public SymEngine::BaseVisitor<SymbolVisitor> {
public:
    SymEngine::Expression symbol_items, non_symbol_items;

    void bvisit(const SymEngine::Add& x) {
        for (const auto& iter : x.get_args()) {
            iter->accept(*this);
        }
    }

    void bvisit(const SymEngine::Basic& x) {
        if (SymEngine::free_symbols(x).empty()) {
            non_symbol_items += SymEngine::Expression(x.rcp_from_this());
        } else {
            symbol_items += SymEngine::Expression(x.rcp_from_this());
        }
    }

    std::pair<SymEngine::Expression, SymEngine::Expression> accept(const SymEngine::Basic& x) {
        symbol_items = non_symbol_items = 0;
        x.accept(*this);
        return {symbol_items, -non_symbol_items};
    }
};

/**
 * Visits items of an expression, checking the sign of the symbols.
 */
class SymbolSignVisitor : public SymEngine::BaseVisitor<SymbolSignVisitor> {
public:
    s8 sign = 1;

    void bvisit(const SymEngine::Number& x) {
        if (x.is_positive())
            sign = 1;
        else if (x.is_negative())
            sign = -1;
        else
            sign = 0;
    }

    void bvisit(const SymEngine::Add& x) {
        s8 cur_sign = -2; // Undetermined
        for (const auto& iter : x.get_args()) {
            if (SymEngine::free_symbols(*iter).empty()) {
                continue;
            }
            iter->accept(*this);
            if (cur_sign != -2 && sign != cur_sign) {
                sign = 0;
                return;
            } else {
                cur_sign = sign;
            }
        }
        if (cur_sign == -2) { // No symbols at all
            cur_sign = 0;
        }
        sign = cur_sign;
    }

    void bvisit(const SymEngine::Mul& x) {
        s8 cur_sign = 1;
        for (const auto& iter : x.get_args()) {
            iter->accept(*this);
            cur_sign *= sign;
        }
        sign = cur_sign;
    }

    void bvisit(const SymEngine::Basic& x) {
        sign = 1;
    }

    s8 accept(const SymEngine::Basic& x) {
        x.accept(*this);
        return sign;
    }
};

std::string EquationToString(const SymEngine::Expression& expr) {
    using namespace SymEngine;
    Expression expanded = expand(expr);

    RCP<const Basic> num, den;
    as_numer_denom(expanded.get_basic(), outArg(num), outArg(den));

    {
        // Special check for linear equations
        const auto& symbols = free_symbols(*num);
        if (symbols.size() == 1) {
            const auto& symbol = *symbols.begin();
            const Expression expr(num);
            // TODO: Using diff for this is simply horrible
            if (expr.diff(symbol).diff(symbol) == 0) {
                const auto& solns =
                    SolveSingle(expr, rcp_static_cast<const SymEngine::Symbol>(symbol));
                if (solns.size() == 1) {
                    return symbol->__str__() + " = " + solns[0].get_basic()->__str__();
                }
            }
        }
    }

    // Split the equation into symbol part and non-symbol part
    SymbolVisitor symbol_visitor;
    auto [symbol_items, non_symbol_items] = symbol_visitor.accept(*num);

    // Flip the sign when symbol part is all negative
    SymbolSignVisitor symbol_sign_visitor;
    s8 symbol_items_sign = symbol_sign_visitor.accept(*num);

    if (symbol_items_sign == -1) {
        symbol_items = -symbol_items;
        non_symbol_items = -non_symbol_items;
    }

    return symbol_items.get_basic()->__str__() + " = " + non_symbol_items.get_basic()->__str__();
}

} // namespace Algebra
