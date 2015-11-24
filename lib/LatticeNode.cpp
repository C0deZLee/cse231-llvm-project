#include "LatticeNode.h"

LatticeNode::TOP = "top";
LatticeNode::Bottom = "bottom";


LatticeNode::LatticeNode(){
    basic = "";
}

LatticeNode::LatticeNode(string s){
  if(s!="")
    basic = s;
}

LatticeNode *LatticeNode::LatticeNode()


LatticeNode *LatticeNode::joinWith(LatticeNode *other){
  //most basic(conservative) join
  return new LatticeNode(TOP);
}

LatticeNode ~LatticeNode(){}//do nothing here
