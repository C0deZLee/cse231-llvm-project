#ifndef RANGE_ANALYSIS
#define RANGE_ANALYSIS

#include "BasicAnalysis.h"
#include "RangeAnalysisLatticeNode.h"
#include "llvm/IR/Constants.h"

class RangeAnalysis: public BasicAnalysis{
public:
    RangeAnalysis(Function &F): BasicAnalysis(){
        errs()<<"Range Analysis start.\n";
        //this->createCFG(F);
    };

    virtual LatticeNode *runFlowFunc(LatticeNode *in, CFGNode *curNode);
    LatticeNode *latticeNodeInit();
    ~RangeAnalysis();

private:

    RangeAnalysisLatticeNode *visitAOpB(RangeAnalysisLatticeNode *in, Instruction *curInst);
    Range *getOperandRange(Value *operand, RangeAnalysisLatticeNode *in);
    Range *opRange(Range *leftRange, Range *rightRange, string opName);
    
};



#endif
