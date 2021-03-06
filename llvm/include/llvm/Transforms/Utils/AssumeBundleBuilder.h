//===- AssumeBundleBuilder.h - utils to build assume bundles ----*- C++ -*-===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// This file contain tools to preserve informations. They should be used before
// performing a transformation that may move and delete instructions as those
// transformation may destroy or worsen information that can be derived from the
// IR.
//
//===----------------------------------------------------------------------===//

#ifndef LLVM_TRANSFORMS_UTILS_ASSUMEBUNDLEBUILDER_H
#define LLVM_TRANSFORMS_UTILS_ASSUMEBUNDLEBUILDER_H

#include "llvm/IR/Attributes.h"
#include "llvm/IR/Instruction.h"
#include "llvm/IR/PassManager.h"

namespace llvm {
class IntrinsicInst;
class AssumptionCache;

/// Build a call to llvm.assume to preserve informations that can be derived
/// from the given instruction.
/// If no information derived from \p I, this call returns null.
/// The returned instruction is not inserted anywhere.
IntrinsicInst *buildAssumeFromInst(Instruction *I);

/// Calls BuildAssumeFromInst and if the resulting llvm.assume is valid insert
/// if before I. This is usually what need to be done to salvage the knowledge
/// contained in the instruction I.
void salvageKnowledge(Instruction *I, AssumptionCache *AC = nullptr);

/// This pass will try to build an llvm.assume for every instruction in the
/// function. Its main purpose is testing.
struct AssumeBuilderPass : public PassInfoMixin<AssumeBuilderPass> {
  PreservedAnalyses run(Function &F, FunctionAnalysisManager &AM);
};

} // namespace llvm

#endif
