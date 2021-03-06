#include "../include/RangeAnalysisLatticeNode.h"




RangeAnalysisLatticeNode::RangeAnalysisLatticeNode():LatticeNode(){
    
}

RangeAnalysisLatticeNode::RangeAnalysisLatticeNode(string s):LatticeNode(s){

}

RangeAnalysisLatticeNode::RangeAnalysisLatticeNode(RangeAnalysisLatticeNode *node){
    this->basic = node->basic;
    this->val = node->val;
}

LatticeNode* RangeAnalysisLatticeNode::joinWith(LatticeNode *other){
    RangeAnalysisLatticeNode *otherNode = static_cast<RangeAnalysisLatticeNode *>(other);
    //if one of the two nodes is a bottom:
    if(this->basic == BOTTOM || otherNode->basic == BOTTOM){
        if(this->basic==BOTTOM){
            return new RangeAnalysisLatticeNode(otherNode);
        }else{
            return new RangeAnalysisLatticeNode(this);
        }
    }

    //if one of the two nodes is a top
    if(this->basic == TOP || this->basic == TOP){
        return new RangeAnalysisLatticeNode(TOP);
    }

    //common situation
    RangeAnalysisLatticeNode *newNode = new RangeAnalysisLatticeNode();
    newNode->val = this->val;
    map<string, Range*>::iterator it;
    for(it=otherNode->val.begin(); it!=otherNode->val.end();it++){
        if(newNode->val.find(it->first) != newNode->val.end()){
            //Found. Let's join the range
            Range *r1 = newNode->val[it->first];
            Range *r2 = it->second;
            r1->left = min(r1->left, r2->left);
            r1->right = max(r1->right, r2->right);
        }else{
            //Not found. just add it in the newnode
            newNode->val[it->first] = it->second;
        }
    }
    return newNode;
    
}

bool RangeAnalysisLatticeNode::equalsTo(LatticeNode *other){
    RangeAnalysisLatticeNode *otherNode = static_cast<RangeAnalysisLatticeNode*>(other);
    //if I am top or bottom:
    if(this->basic != ""){
        return this->basic == otherNode->basic;
    }

    //I am not top or bottom:
    if(this->val.size() != otherNode->val.size()) return false;
    map<string, Range*>::iterator it;
    for(it=this->val.begin(); it!=this->val.end(); it++){
        if(otherNode->val.find(it->first) != otherNode->val.end()){
            //have the same var
            Range *otherRange = otherNode->val[it->first];
            Range *myRange = it->second;
            if(!myRange->equalsTo(otherRange))
                return false;
        }else{
            return false;
        }
    }
    return true;
}

LatticeNode::~LatticeNode(){

}//do nothing here

