// Copyright 2019 Zhupengfei and others
// All rights reserved.

#pragma once

#include <memory>
#include <string>
#include <vector>

namespace Common {

/**
 * A node of a "proof chain".
 * Each node can contain a number of *reasons* as well as *pre_conditions*.
 * When generating a proof, we would follow up the *reasons* line, but for
 * pre_conditions, only the statement is added.
 */
struct ProofChainNode {
    /// The statement of the current proof node.
    std::string statement;

    /// The transform to get the current proof node.
    std::string transform;

    /// The reasons for the current proof node.
    std::vector<std::weak_ptr<ProofChainNode>> reasons;

    /// The pre-conditions of the current proof node.
    std::vector<std::weak_ptr<ProofChainNode>> pre_conditions;
};

std::string GenerateProof(const std::shared_ptr<ProofChainNode>& node);

} // namespace Common