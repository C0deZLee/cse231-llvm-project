#ifndef CONTANT_PROP_ANALYSIS_LATTICE_NODE_H
#define CONTANT_PROP_ANALYSIS_LATTICE_NODE_H
#include <string>
#include <map>
#include <algorithm>
#include "llvm/Support/raw_ostream.h"
#include "LatticeNode.h"

using namespace std;
using namespace llvm;
/*
 * Must-point-to Analysis
 *   
 */

class ConstantPropAnalysisLatticeNode: public LatticeNode {
public:
        bool equalsTo(LatticeNode *other);
        
        LatticeNode *joinwith(LatticeNode *other);

	// initialize with an empty map
	ConstantPropAnalysisLatticeNode();

	// initialize with TOP or BOTTOM
        ConstantPropAnalysisLatticeNode(string input);

        ~ConstantPropAnalysisLatticeNode();

	map<string, float> value;
}
#endif 
