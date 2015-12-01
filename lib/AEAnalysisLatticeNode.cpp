#include "../include/AEAnalysisLatticeNode.h"

/*
\\                 May                Must
\\
\\ Forward     Reaching def.     **Available exp.**
\\
\\ Backward      Liveness		 very busy exp.
\\
\\
\\  Top = empty   Bottom = FS
\\
\\
*/

LatticeNode* AEAnalysisLatticeNode::joinWith(LatticeNode* other){
  

  return result;
}


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