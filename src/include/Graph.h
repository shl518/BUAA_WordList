//
// Created by cychen on 2023/3/7.
//

#ifndef WORKLIST_GRAPH_H
#define WORKLIST_GRAPH_H

#include <iostream>
#include "Word.h"
#include <string.h>
#include "Const.h"
#include <vector>

using namespace std;

class Graph {
private:
    vector<Word> edges;//存贮边的信息
    vector<int> adj[MAXN_POINT];//邻接列表
    int edgeCnt;//边数，也可以作为编号
    int pointSelfLoopCnt[MAXN_POINT];//每个点的自环数
    int pointSelfLoopCharNum[MAXN_POINT];//每个点自环上的总字母数
    int indegree[MAXN_POINT];

public:
    explicit Graph(vector<Word> &edges, bool banReject = false);

    const vector<Word> &getEdges() const {
        return edges;
    }

    const vector<int> *getAdj() const {
        return adj;
    }

    int getEdgeCnt() const {
        return edgeCnt;
    }

    int getPointSelfLoopCnt(int point) const {
        return pointSelfLoopCnt[point];
    }

    Graph();


    const int *getIndegree() const {
        return indegree;
    }

    void subIndgree(int point);

    vector<int> getEdgeFrom(int from) const {
        return adj[from];
    }

    int getSelfEdgeCharSum(int point) {
        return pointSelfLoopCharNum[point];
    }

    vector<string> getSelfEdgeChain(int point) {
        vector<string> result;
        for (auto &edgeid: adj[point]) {
            Word w = edges[edgeid];
            if (w.getAnEnd() == point) {
                result.push_back(w.getStr());
            }
        }
        return result;
    }

    Word getEdgeBetween(int start,int end,bool maxChar = false){
        int maxnum = 0;
        Word result;
        if(maxChar){
            Word rec;
            for(auto &edgeid:adj[start]){
                Word w = edges[edgeid];
                if(w.getAnEnd() == end){
                  if(w.getLength() > maxnum){
                     rec = w;
                     maxnum = w.getLength();
                  }
                }
            }
            return rec;
        } else{
            for(auto &edgeid:adj[start]){
                Word w = edges[edgeid];
                if(w.getAnEnd() == end){
                    return w;
                }
            }
        }
        return result;
    }

    int addEdge(Word& word, bool banRejectLimit);
};


#endif //WORKLIST_GRAPH_H
