#ifndef LATTICE_NODE
#define LATTICE_NODE

#include <string>

using namespace std;
//using namespace llvm;

class LatticeNode{
private:
  static string TOP;
  static string BOTTOM;
  string basic;
public:
  LatticeNode();
  LatticeNode(string s);
  //Join Function: for the merge operation, should be overridden by subclasses.
  virtual LatticeNode *joinWith(LatticeNode *other);
  virtual bool equalsTo(LatticeNode *other);
  virtual ~LatticeNode();
};


#endif
