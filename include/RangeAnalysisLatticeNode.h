#ifndef RANGE_ANALYSIS_LATTICE_NODE
#define RANGE_ANALYSIS_LATTICE_NODE

#include "LatticeNode.h"
#include <climits>
#include <map>
#include <algorithm>

class Range{
public:
    int left, right;
    Range(int left, int right){
        this->left = left;
        this->right = right;
    }

    Range(){
        //default bottom value with range [INT_MAX, INT_MIN]
        //BTW, top value is range[INT_MIN, INT_MAX]
        this->left = INT_MAX;
        this->right = INT_MIN;
    }

    bool equalsTo(Range* other){
        return (this->left == other->left) && (this->right == other->right);
    }
};

class RangeAnalysisLatticeNode: public LatticeNode{
public:
    map<string, Range *> val; //KEY: map that stores var and its range
    
    RangeAnalysisLatticeNode();
    RangeAnalysisLatticeNode(RangeAnalysisLatticeNode *node);
    RangeAnalysisLatticeNode(string s);//for top and bottom
    LatticeNode *joinWith(LatticeNode *other);
    bool equalsTo(LatticeNode *other);

    ~RangeAnalysisLatticeNode();
};

#endif
