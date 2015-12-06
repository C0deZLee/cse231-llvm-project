#include "llvm/Pass.h"
#include "llvm/IR/Module.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/Support/InstIterator.h"
#include <string>
#include <vector>
#include "include/ConstantPropAnalysis.h"

using namespace std;
using namespace llvm;

namespace {
	struct ConstantPropPass : public FunctionPass {
		static char ID;
		vector<ConstantPropAnalysis *> cpa;
		ConstantPropPass() : FunctionPass(ID) {}
		virtual bool runOnFunction(Function &F) {
			cpa.push_back(new ConstantPropAnalysis(F));
			return false;
		}
		void print (raw_ostream &OS, const Module*) const {
			for (unsigned int i = 0; i < cpa.size(); i++)
				cpa[i]->runWorkList();
			OS << "Done!" << "\n";
		}
	};
}

char ConstantPropPass::ID = 0;
static RegisterPass<ConstantPropPass> X("ConstantProp", "Constant Propagation Analysis Pass", false, false);
