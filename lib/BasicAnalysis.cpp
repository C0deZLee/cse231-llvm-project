#include "../include/BasicAnalysis.h"

BasicAnalysis::BasicAnalysis(Function &F){

}

void BasicAnalysis::createCFG(Function &F){
    //adopt BFS to build the CFG
    queue<Instruction *> q;
    map<Instruction *, CFGNode *> m;
    int idx = 1;

    //get the first inst and CFG node
    Instruction *headInst = F.begin()->begin();
    this->CFGHead = new CFGNode(idx++, headInst);
    this->CFGNodes.push_back(CFGHead);
    m[headInst] = this->CFGHead;
    q.push(headInst);

    //do the DFS
    while(!q.empty()){
        Instruction *curInst = q.front();
        CFGNode *curNode = m[curInst];
        q.pop();

        //find current inst's successor insts
        vector<Instruction *> curSuccessors;
        if(isa<BranchInst>(curInst)){
            BranchInst *br = dyn_cast<BranchInst>(curInst);
            for(size_t i=0; i < br->getNumSuccessors(); i++){
                Instruction *nextInst = br->getSuccessor(i)->begin();
                if(nextInst!=NULL) curSuccessors.push_back(nextInst);
            }
        }else{
            if(curInst+1 != NULL) curSuccessors.push_back(curInst+1); 
        }

        //create new edge and node
        for(size_t i=0; i<curSuccessors.size(); i++){
            Instruction *curSuccessor = curSuccessors[i];
            if(m.find(curSuccessor) != m.end()){
                //this inst has been visited
                CFGNode *succrNode = m[curSuccessor];
                CFGEdge *e = new CFGEdge(curNode, succrNode);
                curNode->outEdges.push_back(e);
                succrNode->inEdges.push_back(e);
                this->CFGEdges.push_back(e);
            }else{
                //this inst hasn't been visited
                CFGNode *newNode = new CFGNode(idx++, curSuccessor);
                CFGEdge *e = new CFGEdge(curNode, newNode);
                curNode->outEdges.push_back(e);
                newNode->inEdges.push_back(e);
                q.push(curSuccessor);
                m[curSuccessor] = newNode;
                this->CFGNodes.push_back(newNode);
                this->CFGEdges.push_back(e);
            }
        }
    }
  //
}

void BasicAnalysis::runWorkList(){

}

void BasicAnalysis::init(){

}

BasicAnalysis::~BasicAnalysis(){

}
