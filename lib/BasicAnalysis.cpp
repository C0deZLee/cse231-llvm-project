#include "../include/BasicAnalysis.h"


LatticeNode*  BasicAnalysis::runFlowFunc(LatticeNode *in, CFGNode *curNode){
    return new LatticeNode();
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
    queue<CFGNode *>workList;
    for(size_t i=0; i < CFGEdges.size(); i++){
        CFGEdges[i]->latticeNode = latticeNodeInit();
    }
    for(size_t i=0; i < CFGNodes.size(); i++){
        workList.push(CFGNodes[i]);
    }

    //run the worklist algorithm
    while(!workList.empty()){
        CFGNode *curNode = workList.front();
        workList.pop();
        //join all the latticeNodes on curNode's inEdges.
        LatticeNode *in = latticeNodeInit();
        for(size_t i = 0; i < curNode->inEdges.size(); i++){
            CFGEdge *e = curNode->inEdges[i];
            LatticeNode *tmp = in->joinWith(e->latticeNode);
            delete in;
            in = tmp;
        }

        //run the flow function and get the new lattice node
        LatticeNode *out = runFlowFunc(in, curNode);

        //check the out changed or not
        for(size_t i =0; i < curNode->outEdges.size(); i++){
            CFGEdge *e = curNode->outEdges[i];
            LatticeNode *newOut = out->joinWith(e->latticeNode);
            if(!out->equalsTo(newOut)){
                delete e->latticeNode;
                e->latticeNode = newOut;
                workList.push(e->dstNode);
            }
        }
        delete out;
    }
}

LatticeNode *BasicAnalysis::latticeNodeInit(){
    return new LatticeNode(LatticeNode::BOTTOM);
}

BasicAnalysis::~BasicAnalysis(){
    //free the memory
    for(size_t i=0; i < CFGNodes.size(); i++){
        delete CFGNodes[i];
    }
    for(size_t i = 0; i<CFGNodes.size(); i++){
        delete CFGEdges[i];
    }
    delete CFGHead;
}


