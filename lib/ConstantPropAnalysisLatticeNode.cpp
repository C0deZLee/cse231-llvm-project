#include "../include/ConstantPropAnalysisLatticeNode.h"

bool ConstantPropAnalysisLatticeNode::equalsTo(LatticeNode *othersuper) { 
    ConstantPropAnalysisLatticeNode *other = static_cast<ConstantPropAnalysisFlow*>(othersuper);
    // either this or other is "top" and "bottom"
    if ((this->basic!="") || (other->basic!="") return (this->basic == other->basic);

    if (this->value.size() != other->value.size) return false;
    
    // for the same key name, compare their values
    for (map<string, float>::iterator it = this->value.begin(); it != this->value.end(); it++) {
	string key = it->first;
	float val = it->second;
	if (other->value.find(key) == other->value.end()) return false;
        if (other->value.find(key)->second != val) return false;
    }
    return true;
} 


