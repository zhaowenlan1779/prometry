// Copyright 2019 Zhupengfei and others
// All rights reserved.

#include <unordered_set>
#include "common/proof_chain_node.h"

namespace Common {

/**
 * String resources.
 */
static const StringPack LineBreak = {/*Plain*/ "\n", /*Latex*/ "\n\n"};
static const StringPack StrSince = {/*Plain*/ "Since     ", /*Latex*/ "\\because "};
static const StringPack StrTherefore = {/*Plain*/ "Therefore ", /*Latex*/ "\\therefore "};
static const StringPack StrWeHave = {/*Plain*/ "We have   ", /*Latex*/ "We have "};

std::string GenerateProof(const std::shared_ptr<ProofChainNode>& node,
                          std::unordered_set<std::shared_ptr<ProofChainNode>>& visited,
                          PrintFormat format) {
    std::string proof;

    visited.emplace(node);
    for (const auto& reason_weak : node->reasons) {
        if (auto reason = reason_weak.lock()) {
            if (!visited.count(reason)) {
                proof += GenerateProof(reason, visited, format);
            }
        }
    }
    for (const auto& pre_weak : node->pre_conditions) {
        if (auto pre_condition = pre_weak.lock()) {
            if (!visited.count(pre_condition) && !pre_condition->statement.Get(format).empty()) {
                proof += LineBreak.Get(format) + pre_condition->statement.Get(format);
                visited.emplace(pre_condition);
            }
        }
    }

    if (node->hidden) {
        return proof;
    }

    do {
        if (node->reasons.size() == 1) {
            if (auto reason = node->reasons[0].lock()) {
                if (reason->statement.Get(format) == node->statement.Get(format)) {
                    // Ignore meaningless algebra transforms
                    break;
                }
            }
        }

        if (!node->reasons.empty()) {
            proof += LineBreak.Get(format) + StrSince.Get(format);
            for (const auto& reason_weak : node->reasons) {
                if (auto reason = reason_weak.lock()) {
                    proof += reason->statement.Get(format) + ", ";
                }
            }
            proof += LineBreak.Get(format) + StrTherefore.Get(format) + node->statement.Get(format);
        } else {
            proof += LineBreak.Get(format) + StrWeHave.Get(format) + node->statement.Get(format);
        }

        if (!node->transform.Get(format).empty()) {
            proof += " (" + node->transform.Get(format) + ")";
        }
    } while (0);

    return proof;
}

std::string GenerateProof(const std::shared_ptr<ProofChainNode>& node, PrintFormat format) {
    std::unordered_set<std::shared_ptr<ProofChainNode>> visited;
    return GenerateProof(node, visited, format);
}

} // namespace Common
