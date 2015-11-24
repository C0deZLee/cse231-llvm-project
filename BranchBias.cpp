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

using namespace llvm;
using namespace std;
namespace {
  struct BranchBias : public ModulePass {
    static char ID;
    BranchBias() : ModulePass(ID) {}    
    bool runOnModule(Module &M)   {
      //get external function
      vector<Type *> stringIntTy;
      stringIntTy.push_back(Type::getInt8PtrTy(M.getContext()));
      stringIntTy.push_back(Type::getInt1Ty(M.getContext()));
      FunctionType* FuncTy_2 = FunctionType::get(Type::getVoidTy(M.getContext()), stringIntTy, false);
      Function *recordFunc = cast<Function>(M.getOrInsertFunction("_Z12branchRecordPci", FuncTy_2));
      Function *printFunc = cast<Function>(M.getOrInsertFunction("_Z5printv", Type::getVoidTy(M.getContext()), (Type*) 0));
      
      IRBuilder<> Builder(M.getContext());

      for(Module::iterator func = M.begin(); func != M.end(); func++){
        for(Function::iterator block = func->begin(); block != func->end(); block++){
          TerminatorInst* termInst = block->getTerminator();
          BranchInst* branchInst = (BranchInst*)(termInst);
          if(branchInst->isConditional()){
            //is branch
            //errs()<<"Branch!!!!!!!!!!!\n";
            Builder.SetInsertPoint(block, termInst);
            Value *condition = branchInst->getCondition();
            
            vector<Value*> argVec;
            Value *funcName = Builder.CreateGlobalStringPtr(func->getName());
            argVec.push_back(funcName);
            argVec.push_back(condition);
            Builder.CreateCall(recordFunc, argVec); 
            
          }
          //find the return inst in main func
          if(func->getName() == "main"){
            BasicBlock::iterator it;
            for(it = block->begin(); it != block->end(); it++){
              if(((string)it->getOpcodeName() == "ret")){
                Builder.SetInsertPoint(block, it);
                Builder.CreateCall(printFunc);
              }
            }
          }
        }
      }
      return true;
    }
  };
}

char BranchBias::ID = 0;
static RegisterPass<BranchBias> XX("branchBias", "Count Branch Bias",false, false);
