#include "llvm/Pass.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/Instruction.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/Support/InstIterator.h"
#include <map>
#include <iomanip>
#include <iostream>


using namespace llvm;
using namespace std;
namespace {
  struct CountStaticInstructions : public ModulePass {
    static char ID;
    map <string, int> opCount;
    CountStaticInstructions() : ModulePass(ID) {}
    
    bool runOnModule(Module &M)   {
      int totalCount = 0;
      //iterate funcs in the module
      for(Module::iterator func = M.begin(); func != M.end(); func++){
        //iterate insts in the func
        for(inst_iterator inst = inst_begin(func); inst != inst_end(func); inst++){
          //errs() << "raw: "<<*inst<<"opcode: "<<inst->getOpcode()<<"name: "<<inst->getName()<<'\n';
          std::string name = inst->getOpcodeName();
          opCount[name] ++;
          totalCount ++;
        }
      }
      return true;
    }

    void print(llvm::raw_ostream &O, const Module *M) const{
      int totalCount =0;
      for(map<string, int>::const_iterator it = opCount.begin(); it != opCount.end(); it++){
        cout<<setw(9)<<left<<it->first<<' '<<it->second<<endl;
        totalCount += it->second;
      }  
      cout<<setw(9)<<left<<"TOTAL"<<' '<< totalCount<<endl;
    }
  };
}

char CountStaticInstructions::ID = 0;
static RegisterPass<CountStaticInstructions> X("countInst", "Count Static Instructions",false, false);
