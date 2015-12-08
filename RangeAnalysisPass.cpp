#include "llvm/Pass.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/Instruction.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/Support/InstIterator.h"
#include <map>
#include <iomanip>
#include <iostream>
#include "llvm/IR/IRBuilder.h"

#include "include/RangeAnalysis.h"
#include "include/RangeAnalysisLatticeNode.h"

using namespace std;
using namespace llvm;


namespace {
    struct RangeAnalysisPass : public FunctionPass {
    static char ID;
    vector<BasicAnalysis *> rangeAnalysisVec;
    RangeAnalysisPass() : FunctionPass(ID) {}
    
    bool runOnFunction(Function &F){
        //rangeAnalysisVec.push_back(new RangeAnalysis(F));
        BasicAnalysis * BA = new RangeAnalysis(F);
        return true;
    }

    void print(llvm::raw_ostream &O, const Module *M) const{
        vector<RangeAnalysis *>::iterator it;
        for(size_t i = 0; i < rangeAnalysisVec.size();i++){

        }
    }
  };
}

char RangeAnalysisPass::ID = 0;
static RegisterPass<RangeAnalysisPass> X("rangeAnalysis", "Range Analysis",false, false);

