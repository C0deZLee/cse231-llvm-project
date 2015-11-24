#ifndef CFG_NODE
#define CFG_NODE

#include "CFGEdge.h"
#include "llvm/IR/Instructions.h"
#include <vector>

using namespace std;

Class CFGNode{
public:
  unsigned idx; //the index of the current instruction/
  Instruction *inst;
  vector<CFGEdge *> inEdges;
  vector<CFGEdge *> outEdges;
  CFGNode(unsigned idx, Instruction* inst){
    this->idx = idx;
    this->inst = inst;
  }
}

#endif