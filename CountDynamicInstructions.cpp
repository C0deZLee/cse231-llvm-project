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
  struct CountDynamicInstructions : public ModulePass {
    static char ID;
    CountDynamicInstructions() : ModulePass(ID) {}
    
    bool runOnModule(Module &M)   {
      //get external function
      //Function *exFunc = cast<Function>(M.getOrInsertFunction("print", (Type *)0)); 
      //Function *exFunc = cast<Function>(M.getOrInsertFunction("_Z5printii", Type::getVoidTy(M.getContext()), (Type*)0));//find the function's name in count.ll - -# 
      vector<Type *> IntTy_2(2, Type::getInt32Ty(M.getContext()));
      FunctionType* FuncTy_2 = FunctionType::get(Type::getVoidTy(M.getContext()), IntTy_2, false);
      Function *countFunc = cast<Function>(M.getOrInsertFunction("_Z5countii", FuncTy_2));
      Function *printFunc = cast<Function>(M.getOrInsertFunction("_Z5printv", Type::getVoidTy(M.getContext()), (Type*) 0));
      //for each function
      for(Module::iterator func = M.begin(); func != M.end(); func++){
        //for each block
        for(Function::iterator block = func->begin(); block != func->end(); block++){
          map<int, int> tmpCount;
          //for each instruction
          for(BasicBlock::iterator it = block->begin(); it != block->end(); it++){
            tmpCount[it->getOpcode()]++;
          }
          
          //insert Count Function
          IRBuilder<> Builder(block);
          Builder.SetInsertPoint(block, block->getTerminator());
          map<int, int>::iterator it;
          for(it = tmpCount.begin(); it != tmpCount.end(); it++){
            vector<Value *> ArgsV;
            Value* opCode = ConstantInt::get(Type::getInt32Ty(M.getContext()), it->first);
            Value* opCount = ConstantInt::get(Type::getInt32Ty(M.getContext()), it->second);
            ArgsV.push_back(opCode);
            ArgsV.push_back(opCount);
            //errs()<<"!!!!!";
            Builder.CreateCall(countFunc, ArgsV);
          }
          
          //insert Print Function
          for(BasicBlock::iterator it = block->begin(); it != block->end(); it++){
            //if the Func name == 'main' and the instuction name == 'ret', last inst
            if(func->getName() == "main" && ((string)it->getOpcodeName()) == "ret"){
              IRBuilder<> Builder(block);
              Builder.SetInsertPoint(it);
              vector<Value *> ArgsV;
              Builder.CreateCall(printFunc, ArgsV);
            }
          } 
        }
      }
      return true;
    }
  };
}

char CountDynamicInstructions::ID = 0;
static RegisterPass<CountDynamicInstructions> X("countDymInst", "Count Dynamic Instructions",false, false);
