#include "../include/ConstantPropAnalysis.h"
using namespace std;
using namespace llvm;

ConstantPropAnalysis::ConstantPropAnalysis(Function &F):BasicAnalysis(F) {
	errs()<<"Constant Propagation Analysis starts.\n";
}

ConstantPropAnalysis::~ConstantPropAnalysis() {}

// initialize the flow with bottom, does not inherit
ConstantPropAnalysisLatticeNode* ConstantPropAnalysis::latticeNodeInit() {
	return new ConstantPropAnalysisLatticeNode(ConstantPropAnalysisLatticeNode::BOTTOM); 
}

ConstantPropAnalysisLatticeNode* ConstantPropAnalysis::runFlowFunc(LatticeNode *in, CFGNode *curNode) {
	ConstantPropAnalysisLatticeNode *newIn = static_cast<ConstantPropAnalysisLatticeNode *>(in);
	ConstantPropAnalysisLatticeNode *out;
	Instruction *inst = curNode->inst;
	//check $ROOTCSE231/llvm/src/include/llvm/IR/Instruction.def
	switch(inst->getOpcode()) {
	case 8: // Add 
	case 10: // Sub
		out = executeOpInst(newIn, inst, inst->getOpcode());
		break;
	default: 
		out = new ConstantPropAnalysisLatticeNode();
		out->basic = newIn->basic;
		out->value = newIn->value; 
	}
	return out;	
}

float calcOpInst(float left, float right, unsigned opcode) {
	float result;
	switch(opcode) {
	case 8 : // Add
		result = left + right;
	case 10 : //Sub
		result = left - right;
	}
	return result;
}

ConstantPropAnalysisLatticeNode* ConstantPropAnalysis::executeOpInst(ConstantPropAnalysisLatticeNode *in, Instruction *inst, unsigned opcode) {
	Value *left = inst->getOperand(0);
	Value *right = inst->getOperand(1);
	map<string, float> value;
	ConstantPropAnalysisLatticeNode *f = new ConstantPropAnalysisLatticeNode();
	f->basic = in->basic;
	f->value = in->value;
	if (ConstantInt *CIleft = dyn_cast<ConstantInt>(left)) {
		if (ConstantInt *CIright = dyn_cast<ConstantInt>(right)) {
			float leftval = CIleft->getZExtValue();
			float rightval = CIright->getZExtValue();
			float result = calcOpInst(leftval, rightval, opcode);
			ConstantPropAnalysisLatticeNode *ff = new ConstantPropAnalysisLatticeNode();
			value[inst->getName()] = result;
			ff->value = value;
			ConstantPropAnalysisLatticeNode *t = static_cast<ConstantPropAnalysisLatticeNode*>(ff->joinWith(f));
			return t;
		} else {
			if (f->value.find(right->getName()) != f->value.end()) {
			float leftval = CIleft->getZExtValue(); 
                        float rightval = f->value.find(right->getName())->second;
                        float result = calcOpInst(leftval, rightval, opcode);
			ConstantPropAnalysisLatticeNode *ff = new ConstantPropAnalysisLatticeNode();
			value[inst->getName()] = result;
			ff->value = value;
			ConstantPropAnalysisLatticeNode *t = static_cast<ConstantPropAnalysisLatticeNode*>(ff->joinWith(f));
			return t;
			}
		}
	} else {
		if (ConstantInt *CIright = dyn_cast<ConstantInt>(right)) {			
			float rightval = CIright->getZExtValue(); 
                        float leftval = f->value.find(left->getName())->second;
                        float result = calcOpInst(leftval, rightval, opcode);
			ConstantPropAnalysisLatticeNode *ff = new ConstantPropAnalysisLatticeNode();
			value[inst->getName()] = result;
			ff->value = value;
			ConstantPropAnalysisLatticeNode *t = static_cast<ConstantPropAnalysisLatticeNode*>(ff->joinWith(f));
			return t;
		} else {
			float rightval = f->value.find(right->getName())->second;  
                        float leftval = f->value.find(left->getName())->second;
                        float result = calcOpInst(leftval, rightval, opcode);
			ConstantPropAnalysisLatticeNode *ff = new ConstantPropAnalysisLatticeNode();
			value[inst->getName()] = result;
			ff->value = value;
			ConstantPropAnalysisLatticeNode *t = static_cast<ConstantPropAnalysisLatticeNode*>(ff->joinWith(f));
			return t;
		}
	}
	return f;
}
