//
// Created by cychen on 2023/3/7.
//

#include "../include/Graph.h"
#include "../include/Config.h"
Graph::Graph() {
    edgeCnt = 0;
    edges = *new vector<Word>;
    memset(pointSelfLoopCnt, 0, sizeof(pointSelfLoopCnt));
    memset(indegree, 0, sizeof(indegree));
    memset(pointSelfLoopCharNum, 0, sizeof(pointSelfLoopCharNum));
}

Graph::Graph(vector<Word> &edges,bool banReject) : edges() {
    this->edgeCnt = 0;
    memset(pointSelfLoopCnt, 0, sizeof(pointSelfLoopCnt));
    memset(indegree, 0, sizeof(indegree));
    memset(pointSelfLoopCharNum, 0, sizeof(pointSelfLoopCharNum));
    for (auto &edge: edges) {
        this->addEdge(edge,banReject);
    }
}


int Graph::addEdge(Word& word,bool banRejectLimit) {
    int r = 0;
    int start = word.getBegin();
    Config *config = Config::getInstance();
    if(!banRejectLimit && start == config->getRejectLimit()){
        return 0;//没有ban并且reject，就不添加
    }

    word.setId(this->edgeCnt);
    edges.push_back(word);
    adj[start].push_back(edgeCnt);
    this->edgeCnt += 1;
    //自环暂时不计入入度的计数，入度列表目前仅用于topstort
    if (word.getAnEnd() != word.getBegin()) {
        //非自环计入入度
        indegree[word.getAnEnd()]++;
    } else {
        //自环计入自环数,同时计入该点的自环字母总数
        pointSelfLoopCnt[word.getBegin()]++;
        pointSelfLoopCharNum[word.getBegin()] += word.getLength();
    }
    return r;
}

void Graph::subIndgree(int point) {
    indegree[point] -= 1;
}
