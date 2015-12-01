#include "../include/AEAnalysisLatticeNode.h"


bool AEAnalysisLatticeNode::equalsTo(LatticeNode *other) {
    AEAnalysisLatticeNode *otherNode = static_cast<AEAnalysisLatticeNode*>(other);
    //if I am top or bottom:
    if(this->basic != "") {
        return this->basic == otherNode->basic;
    }
    
    if (otherNode -> val.size() != this -> val.size()) {
		return false;
	}

    for(map<string, string>::iterator it = this->val.begin(); it != this -> val.end(); it++) {
        if(otherNode -> val.find(it -> first) == otherNode -> val.end()) {
            return false;
        }
        if(otherNode -> val.find(it -> second) -> second != it -> second) {
            return false;
        }
    }
    
    return true;
}

LatticeNode * AEAnalysisLatticeNode::joinWith(LatticeNode *other) {
    return other;
}


AEAnalysisLatticeNode::AEAnalysisLatticeNode():LatticeNode() {
		
}

AEAnalysisLatticeNode::AEAnalysisLatticeNode(string s):LatticeNode(s) {


}


AEAnalysisLatticeNode::~AEAnalysisLatticeNode() {
	//Nothing for basic static analysis
}


//bool AEAnalysisLatticeNode::isTopOrBottom() {if(this->basic != "") {}

//void AEAnalysisLatticeNode::printErr() {}