#ifndef CONSTANT_PROP_ANALYSIS_H
#define CONSTANT_PROP_ANALYSIS_H

#include "BasicAnalysis.h"
#include "ConstantPropAnalysisLatticeNode.h"
#include "llvm/IR/Constants.h"
#include "llvm/IR/Instructions.h"
#include "llvm/IR/Instruction.h"
#include "llvm/IR/Function.h"
#include "llvm/Support/raw_ostream.h"

using namespace std;
using namespace llvm;

class ConstantPropAnalysis: public BasicAnalysis {
private:

public:
	ConstantPropAnalysis(Function &F);
	~ConstantPropAnalysis();
	ConstantPropAnalysisLatticeNode *latticeNodeInit();
	ConstantPropAnalysisLatticeNode *runFlowFunc(LatticeNode *in, CFGNode *curNode);
	float calcOpInst(float left, float right, unsigned opcode);
	ConstantPropAnalysisLatticeNode *executeOpInst(ConstantPropAnalysisLatticeNode *in, Instruction *inst, unsigned opcode);
};

#endif
