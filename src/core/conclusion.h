// Copyright 2019 Zhupengfei and others
// All rights reserved.

#pragma once

#include <memory>
#include <string>
#include <vector>
#include "common/common_types.h"
#include "common/printer.h"
#include "common/proof_chain_node.h"

namespace Core {

class Element;
class Transform;

/**
 * Type of the "type" field of a conclusion.
 */
using ConclusionType = u8;

/**
 * Virtual interface for conclusions.
 * A hash function is used to compare the equality of two conclusions.
 */
class Conclusion {
public:
    virtual ~Conclusion();

    virtual std::string Print(Common::PrintFormat format = Common::PrintFormat::Plain) const;
    Common::StringPack PrintAll() const;

    /**
     * Get the elements related to this conclusion.
     * When adding this conclusion to the system, the elements related will be updated as well.
     */
    virtual std::vector<std::shared_ptr<Element>> GetRelatedElements() const = 0;

    virtual ConclusionType GetType() const = 0;
    virtual u64 GetHash() const = 0;

    std::shared_ptr<Common::ProofChainNode> GetProofNode() const;

    /// Comparison operators
    bool operator==(const Conclusion& other) const;
    bool operator!=(const Conclusion& other) const;

protected:
    std::shared_ptr<Common::ProofChainNode> proof_node;

    friend class System;
};

} // namespace Core
