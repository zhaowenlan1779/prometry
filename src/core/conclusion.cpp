// Copyright 2019 Zhupengfei and others
// All rights reserved.

#include "core/conclusion.h"

namespace Core {

Conclusion::~Conclusion() = default;

std::string Conclusion::Print(Common::PrintFormat format) const {
    return "Unknown";
}

Common::StringPack Conclusion::PrintAll() const {
    return {Print(Common::PrintFormat::Plain), Print(Common::PrintFormat::Latex)};
}

bool Conclusion::operator==(const Conclusion& other) const {
    return GetHash() == other.GetHash();
}

bool Conclusion::operator!=(const Conclusion& other) const {
    return GetHash() != other.GetHash();
}

std::shared_ptr<Common::ProofChainNode> Conclusion::GetProofNode() const {
    return proof_node;
}

}