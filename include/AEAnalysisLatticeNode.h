#ifndef AE_ANALYSIS_LATTICE_NODE
#define AE_ANALYSIS_LATTICE_NODE

#include "LatticeNode.h"
#include <climits>
#include <map>
#include <algorithm>

/*
\\                 May                Must
\\
\\ Forward     Reaching def.     **Available exp.**
\\
\\ Backward      Liveness		 very busy exp.
\\
\\
\\  Top = empty   Botom = FS
\\
\\
*/



class AE {

	void printErr();


};

class AEAnalysisLatticeNode: public LatticeNode {
public:
    map<string, float> value;


    bool equalsTo(LatticeNode *other);
    LatticeNode *joinwith(LatticeNode *other);

	
	AEAnalysisLatticeNode(); // init
    AEAnalysisLatticeNode(string s); // initialize with TOP or BOTTOM

    ~AEAnalysisLatticeNode();


};
#endif 
