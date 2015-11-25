#ifndef BASIC_ANALYSIS
#define BASIC_ANALYSIS

#include "CFGUtils.h"
#include "llvm/Pass.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/Instruction.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/Support/InstIterator.h"
#include <vector>

using namespace llvm;
using namespace std;

class BasicAnalysis{
private:
  vector<CFGNode *> CFGNodes;
  vector<CFGEdge *> CFGEdges;
  CFGNode *CFGHead;

public:
  BasicAnalysis();
  BasicAnalysis(Function &F);
  void createCFG(Function &F);
  void runWorkList();

  virtual LatticeNode *runFlowFunc(LatticeNode *in, CFGNode *curNode);
  virtual void init();// Can write in the createCFG func or not?
  virtual ~BasicAnalysis();

};
#endif
