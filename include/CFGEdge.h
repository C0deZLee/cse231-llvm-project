#ifndef CFG_EDGE
#define CFG_EDGE

#include "CFGNode.h"
#include "LatticeNode.h"
#include "llvm/IR/Instructions.h"
#include <vector>

using namespace std;

Class CFGEdge{
public:
  CFGNode *srcNode;
  CFGNode *dstNode;
  LatticeNode *latNode;
  CFGEdge(srcNode, dstNode){
    this->srcNode = srcNode;
    this->dstNode = dstNode;
  }
}

#endif