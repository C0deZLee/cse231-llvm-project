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

#include "include/AEAnalysis.h"
#include "include/AEAnalysisLatticeNode.h"

using namespace llvm;
using namespace std;


namespace {
  struct AEAnalysisPass : public FunctionPass {
    static char ID;
    vector<BasicAnalysis *> aeAnalysisVec;

    AEAnalysisPass() : FunctionPass(ID) {}

    bool runOnFunction(Function &F){
        //for (Function::iterator I = F.begin(), E = F.end(); I != E; ++I) {
            //aeAnalysisVec.push_back(new AEAnalysis(F));
        //}
        
        BasicAnalysis * BA = new AEAnalysis(F);
        //aeAnalysisVec.push_back(new AEAnalysis(F));
        return true;
    }

    void print(llvm::raw_ostream &O, const Module *M) const{
        vector<AEAnalysis *>::iterator it;
        for(size_t i = 0; i < aeAnalysisVec.size();i++){

        }
    }
  };
}

char AEAnalysisPass::ID = 0;
static RegisterPass<AEAnalysisPass> X("aeAnalysis", "Available Expression Analysis Pass", false, false);
