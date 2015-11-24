#ifndef LATTICE_NODE
#define LATTICE_NODE

#include <string>

using namespace std;
using namespace llvm;

Class LatticeNode{
private:
  String TOP;
  String BOTTOM;
  String Basic;
public:
  LatticeNode();
  //Join Function: for the merge operation, should be overridden by subclasses.
  virtual LatticeNode *joinWith(LatticeNode *other);
  virtual bool equalsTo(LatticeNode *other);
  virtual ~LatticeNode();
}


#endif