#include "../include/AEAnalysisLatticeNode.h"


bool AEAnalysisLatticeNode::equalsTo(LatticeNode * other) {
    AEAnalysisLatticeNode * otherNode = static_cast<AEAnalysisLatticeNode*>(other);
    //if I am top or bottom:
    if(this->basic != "") {
        return this->basic == otherNode->basic;
    }
    
    if (otherNode->val.size() != this->val.size()) {
		return false;
	}

    for(map<string, string>::iterator it = this->val.begin(); it != this->val.end(); it++) {
        if(otherNode->val.find(it->first) == otherNode->val.end()) { return false; }
        if(otherNode->val.find(it->second)->second != it->second) { return false; }
    }
    
    return true;
}

LatticeNode * AEAnalysisLatticeNode::joinWith(LatticeNode * other) {
    AEAnalysisLatticeNode * otherNode = static_cast<AEAnalysisLatticeNode*>(other);

    if (this->basic == BOTTOM && otherNode->basic == BOTTOM) { return new AEAnalysisLatticeNode(BOTTOM); }
    
    if (this->basic == TOP || otherNode->basic == TOP) { return new AEAnalysisLatticeNode(TOP); }
    
    if (this->basic == BOTTOM) { return new AEAnalysisLatticeNode(otherNode); }
    else if (otherNode->basic == BOTTOM) { return new AEAnalysisLatticeNode(this); }
    
    //common situation
    AEAnalysisLatticeNode *newNode = new AEAnalysisLatticeNode();
    newNode->val = this->val;
    map<string, string>::iterator it;
    for(it = otherNode->val.begin(); it != otherNode->val.end(); it++) {
        if(newNode->val.find(it->first) != newNode->val.end()) {

        }else{

        }
    }
    return newNode;
}


AEAnalysisLatticeNode::AEAnalysisLatticeNode():LatticeNode() {
		
}

AEAnalysisLatticeNode::AEAnalysisLatticeNode(string s):LatticeNode(s) {


}

AEAnalysisLatticeNode::AEAnalysisLatticeNode(AEAnalysisLatticeNode *node) {
    this->basic = node->basic;
    this->val = node->val;
}

AEAnalysisLatticeNode::~AEAnalysisLatticeNode() {
	//Nothing for basic static analysis
}


//bool AEAnalysisLatticeNode::isTopOrBottom() {if(this->basic != "") {}

//void AEAnalysisLatticeNode::printErr() {}