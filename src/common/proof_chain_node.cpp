// Copyright 2019 Zhupengfei and others
// All rights reserved.

#include <unordered_set>
#include "common/proof_chain_node.h"

namespace Common {

std::string GenerateProof(const std::shared_ptr<ProofChainNode>& node,
                          std::unordered_set<std::shared_ptr<ProofChainNode>>& visited) {
    std::string proof;

    visited.emplace(node);
    for (const auto& reason_weak : node->reasons) {
        if (auto reason = reason_weak.lock()) {
            if (!visited.count(reason)) {
                proof += GenerateProof(reason, visited);
            }
        }
    }
    for (const auto& pre_weak : node->pre_conditions) {
        if (auto pre_condition = pre_weak.lock()) {
            if (!visited.count(pre_condition) && !pre_condition->statement.empty()) {
                proof += "\n" + pre_condition->statement;
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
                if (reason->statement == node->statement) {
                    // Ignore meaningless algebra transforms
                    break;
                }
            }
        }

        if (!node->reasons.empty()) {
            proof += "\nSince     ";
            for (const auto& reason_weak : node->reasons) {
                if (auto reason = reason_weak.lock()) {
                    proof += reason->statement + ", ";
                }
            }
            proof += "\nTherefore " + node->statement;
        } else {
            proof += "\nWe have   " + node->statement;
        }

        if (!node->transform.empty()) {
            proof += " (" + node->transform + ")";
        }
    } while (0);

    return proof;
}

std::string GenerateProof(const std::shared_ptr<ProofChainNode>& node) {
    std::unordered_set<std::shared_ptr<ProofChainNode>> visited;
    return GenerateProof(node, visited);
}

} // namespace Common
