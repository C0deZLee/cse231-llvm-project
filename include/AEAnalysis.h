#ifndef AE_ANALYSIS
#define AE_ANALYSIS

#include "BasicAnalysis.h"
#include "AEAnalysisLatticeNode.h"
#include "llvm/IR/Constants.h"
#include <string>


using namespace llvm;
using namespace std;

class AEAnalysis: public BasicAnalysis{

public:
	/*
    AEAnalysis(Function &F);
    AEAnalysisLatticeNode *runFlowFunc(LatticeNode *in, CFGNode *currentNode);
    AEAnalysisLatticeNode *latticeNodeInit();
    ~AEAnalysis();
    */
    
    virtual LatticeNode *runFlowFunc(LatticeNode *in, CFGNode *currentNode);
    LatticeNode *latticeNodeInit();

    AEAnalysis(Function &F);//:BasicAnalysis(F){};
    ~AEAnalysis();
private:
    AEAnalysisLatticeNode *analyzeAOpB(AEAnalysisLatticeNode *in, Instruction *inst);

};



#endif
