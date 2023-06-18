//
// Created by cychen on 2023/3/7.
//

/*
 * 写算法: dfs, dp, tarjan
 * 写工具函数: char2int, int2char
 */

#ifndef WORKLIST_UTILS_H
#define WORKLIST_UTILS_H

#include "Graph.h"
#include "../preprocess/Input.h"

int char2int(char c);

char int2char(int n);

int genWordFromList(vector<string> &wordList, vector<Word> &edges);

// vector<vector<string>> to char* []
int getOutPutChar(vector<vector<string>> vec, char **&result);

// vector<string> to char*
int vectorToCharArray(vector<string> &strings, char **&result);

int dfsGraph(Graph graph, int start, bool mustMore2, vector<bool> &visited, vector<string> &path,
             vector<vector<string>> &pathList);

bool hasCycle(const Graph &graph);

int dp_loopless(Graph graph, vector<int> &result);

int dp_loop(const Graph &graph, vector<vector<string>> &result);

#endif //WORKLIST_UTILS_H
