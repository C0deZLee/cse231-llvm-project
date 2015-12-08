#ifndef BASIC_ANALYSIS
#define BASIC_ANALYSIS

#include "CFGUtils.h"
#include "llvm/Pass.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/Instruction.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/Support/InstIterator.h"

#include "LatticeNode.h"
#include <vector>
#include <queue>

using namespace llvm;
using namespace std;

class BasicAnalysis{
public:

  BasicAnalysis() {}
  BasicAnalysis(Function &F) {
    errs()<<"Basic Analysis start.\n";
    this->createCFG(F);
  }
  
  void createCFG(Function &F);
  void runWorkList();
  virtual LatticeNode *runFlowFunc(LatticeNode *in, CFGNode *curNode);
  virtual LatticeNode *latticeNodeInit();// Can write in the createCFG func or not?
  virtual ~BasicAnalysis();


private:
  vector<CFGNode *> CFGNodes;
  vector<CFGEdge *> CFGEdges;
  CFGNode *CFGHead;

};
#endif
