#include "../include/ConstantPropAnalysisLatticeNode.h"

ConstantPropAnalysisLatticeNode::ConstantPropAnalysisLatticeNode(): LatticeNode() {}

ConstantPropAnalysisLatticeNode::ConstantPropAnalysisLatticeNode(string input): LatticeNode(input) {}

ConstantPropAnalysisLatticeNode::~ConstantPropAnalysisLatticeNode() {}

bool ConstantPropAnalysisLatticeNode::equalsTo(LatticeNode *othersuper) { 
    ConstantPropAnalysisLatticeNode *other = static_cast<ConstantPropAnalysisLatticeNode*>(othersuper);
    // either this or other is "top" and "bottom"
    if ((this->basic!="") || (other->basic!="")) return (this->basic == other->basic);

    if (this->value.size() != other->value.size()) return false;
    
    // for the same key name, compare their values
    for (map<string, float>::iterator it = this->value.begin(); it != this->value.end(); it++) {
	string key = it->first;
	float thisval = it->second;
	// cannot find this key
	if (other->value.find(key) == other->value.end()) return false;
	// find this key in other but cannot match
        if (other->value.find(key)->second != thisval) return false;
    }
    return true;
} 

LatticeNode *ConstantPropAnalysisLatticeNode::joinWith(LatticeNode *othersuper) {
    ConstantPropAnalysisLatticeNode *other = static_cast<ConstantPropAnalysisLatticeNode*>(othersuper);
    if (this->basic == TOP || other->basic == TOP) return new ConstantPropAnalysisLatticeNode(TOP);
    if (this->basic == BOTTOM && other->basic == BOTTOM ) return new ConstantPropAnalysisLatticeNode(BOTTOM);

    ConstantPropAnalysisLatticeNode *f = new ConstantPropAnalysisLatticeNode();
    if (this->basic == BOTTOM) {
	f->value = other->value;
	f->basic = other->basic;
	return f;
    }

    if (other->basic == BOTTOM) {
	f->value = this->value;
	f->basic = this->basic;
	return f;
    }

    for (map<string, float>::iterator it = this->value.begin(); it != this->value.end(); it++) {
	if (other->value.find(it->first) == other->value.end()) {
	    f->value[it->first] = this->value.find(it->first)->second;
	} else if (it->second == other->value.find(it->first)->second) 
	    f->value[it->first] = this->value.find(it->first)->second;
    }

    for (map<string, float>::iterator it = other->value.begin(); it != other->value.end(); it++) {
	if (this->value.find(it->first) == this->value.end()) {
	    f->value[it->first] = other->value.find(it->first)->second;
	} else if (it->second == this->value.find(it->first)->second) 
	    f->value[it->first] = this->value.find(it->first)->second;
    }

    return f;
}
