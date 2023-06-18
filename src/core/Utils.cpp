//
// Created by cychen on 2023/3/7.
//
#include <cctype>
#include <stack>
#include <queue>
#include <algorithm>
#include <set>
#include "../include/Utils.h"
#include "../include/Config.h"
#include "../include/Const.h"

using namespace std;

int char2int(char c) {
    int r = -1;
    if (islower(c)) {
        r = c - 'a';
    } else if (isupper(c)) {
        r = c - 'A';
    }
    return r;
}

char int2char(int n) {
    char c = 'a';
    if (n < 0 || n > 26) {
        //TODO error
    } else {
        c += n;
    }
    return c;
}

int genWordFromList(vector<string> &wordList, vector<Word> &edges) {
    int r = 0;
    set<string> list(wordList.begin(), wordList.end());
    for (const auto &i: list) {
        edges.emplace_back(i);
    }
    return r;
}

int getOutPutChar(vector<vector<string>> vec, char **&result) {
    result = new char *[vec.size()];

    for (size_t i = 0; i < vec.size(); ++i) {
        string str_line;
        unsigned long long l = vec[i].size();
        for (unsigned long long j = 0; i < l; i++) {
            str_line += vec[i][j];
            if (j < l - 1) {
                str_line += " ";
            }
        }
        result[i] = new char[str_line.size() + 1];
        strcpy(result[i], str_line.c_str());
    }
    return 0;
}

int vectorToCharArray(vector<string> &strings, char **&result) {
    const int size = strings.size();

    // Allocate memory for char*[] array
    result = (char **) malloc(size * sizeof(char *));

    // Convert each string to char* pointer and store in char*[] array
    for (int i = 0; i < size; i++) {
        const char *str = strings[i].c_str();
        char *charPtr = (char *) malloc((strlen(str) + 1) * sizeof(char));
        strcpy(charPtr, str);
        result[i] = charPtr;
    }
    return 0;
}


int findFirstOccurrence(const std::vector<int> &vec, int target) {
    for (int i = 0; i < vec.size(); i++) {
        if (vec[i] == target) {
            return i;
        }
    }
    return -1; // 如果没有找到，返回-1
}

bool dfsCycle(const Graph &graph, vector<int> &visited, int node, vector<int> &path) {
    visited[node] = 1;
    path.push_back(node);
    for (auto &e: graph.getAdj()[node]) {
        Word w = graph.getEdges()[e];
        int neighbor = w.getAnEnd();
        if (visited[neighbor] == 1) {
            int pos = findFirstOccurrence(path, neighbor);
            if (path.size() - findFirstOccurrence(path, neighbor) >= 2) {
                return true;
            } else {
                path.push_back(neighbor);
            }
        } else if (visited[neighbor] == 0) {
            if (dfsCycle(graph, visited, neighbor, path)) {
                return true;
            }
        }
    }
    path.pop_back();
    return false;
}

bool hasCycle(const Graph &graph) {
    vector<int> visited(MAXN_POINT, 0);

    for (int i = 0; i < MAXN_POINT; i++) {
        if (visited[i] == 0) {
            vector<int> path;
            if (dfsCycle(graph, visited, i, path)) {
                return true;
            }
        }
    }
    return false;
}

//从start节点开始dfs
int dfsGraph(Graph graph, int start, bool mustMore2, vector<bool> &visited, vector<string> &path,
             vector<vector<string>> &pathList) {
    if ((!mustMore2 && path.size() >= 1) || (mustMore2 && path.size() >= 2)) {
        pathList.push_back(path);
    }
    int r = 0;
    for (auto i = graph.getAdj()[start].begin(); i != graph.getAdj()[start].end(); ++i) {
        //i 是与start点相连的edge（word）的编号
        Word &w = const_cast<Word &>(graph.getEdges()[*i]);
        int to = w.getAnEnd();
        if (!visited[*i]) {
            visited[*i] = true; //标记此边已经遍历
            path.push_back(w.getStr());
            r = dfsGraph(graph, to, mustMore2, visited, path, pathList);
            path.pop_back();
            visited[*i] = false;
        }
    }
    return r;
}

int topoSort(Graph graph, vector<int> &result) {
    queue<int> q;
    int r = 0;
    for (int i = 0; i < MAXN_POINT; i++) {
        if (graph.getIndegree()[i] == 0) {
            q.push(i);
        }
    }
    while (!q.empty()) {
        int first = q.front();
        q.pop();
        result.push_back(first);
        for (auto i = graph.getAdj()[first].begin(); i != graph.getAdj()[first].end(); ++i) {
            Word &w = const_cast<Word &>(graph.getEdges()[*i]);
            int to = w.getAnEnd();

            if (to == first) {
                continue; //自环跳过
            }
            graph.subIndgree(to);
            if (graph.getIndegree()[to] == 0) {
                q.push(to);
            }
        }
    }
    return r;
}


int dp_loopless(Graph graph, vector<int> &result) {
    Config *config = Config::getInstance();

    vector<int> dp(MAXN_POINT, -1);// dp的1*26数组
    vector<int> pre(MAXN_POINT, -1);//记录pre的1*26数组
    // 初始化 dp数组
    if (config->getHeadLimit() == -1) {
        //没有首字母限制，dp初始化为每个点的自环数目或者自环字母总数
        if (config->getState() == STATE_WORD_COUNT) {
            for (int i = 0; i < MAXN_POINT; i++) {
                dp[i] = graph.getPointSelfLoopCnt(i);
            }
        } else if (config->getState() == STATE_CHAR_COUNT) {
            for (int i = 0; i < MAXN_POINT; i++) {
                dp[i] = graph.getSelfEdgeCharSum(i);
            }
        }

    } else {
        //有首字母限制
        int head = config->getHeadLimit();
        if (config->getState() == STATE_WORD_COUNT) {
            dp[head] = graph.getPointSelfLoopCnt(head);
        } else if (config->getState() == STATE_CHAR_COUNT) {
            dp[head] = graph.getSelfEdgeCharSum(head);
        }

    }

    vector<int> topResult;

    int r = topoSort(graph, topResult);
    if (r != 0) {
        return r;
    }

    //dp 最多单词数
    for (int i = 0; i < MAXN_POINT; i++) {
        int from = topResult[i];//起点

        if (from == config->getRejectLimit()) {
            continue; //拒绝指定首字母，直接跳过
        }

        if (dp[from] < 0) {
            continue;
        }

        vector<int> edge_from = graph.getEdgeFrom(from);
        for (int &it: edge_from) {
            Word &w = const_cast<Word &>(graph.getEdges()[it]);
            if (w.getBegin() == w.getAnEnd()) {
                continue; //自环跳过
            }
            int to = w.getAnEnd();//终点
            int tmp = 0;
            if (config->getState() == STATE_WORD_COUNT) { //最多单词数
                tmp = dp[from] + 1 + graph.getPointSelfLoopCnt(to);
            } else if (config->getState() == STATE_CHAR_COUNT) { //最多字母数
                tmp = dp[from] + w.getLength() + graph.getSelfEdgeCharSum(to);
            }
            if (tmp > dp[to]) {
                dp[to] = tmp;
                pre[to] = from;
            }
        }
    }

    //找到最佳dp
    if (config->getTailLimit() != -1) { //指定尾字母

        int n = config->getTailLimit();
        if (pre[n] == -1) {
            if (config->getHeadLimit() != -1 && config->getHeadLimit() != config->getTailLimit()) {
                return 0;
            }
        }
        result.push_back(n);
        while (pre[n] != -1) {
            result.push_back(pre[n]);
            n = pre[n];
        }
    } else {
        int max = -1;
        int n = -1;
        for (int i = 0; i < MAXN_POINT; i++) {
            if (dp[i] > max) {
                max = dp[i];
                n = i;
            }
        }
        result.push_back(n);
        while (pre[n] != -1) {
            result.push_back(pre[n]);
            n = pre[n];
        }
    }
    return 0;
}


int tarjan(int u, Graph graph, vector<int> &dfn, vector<int> &low, vector<int> &inStack, stack<int> &stk,
           vector<vector<int>> &scc) {
    static int timeStamp = 0;
    dfn[u] = low[u] = ++timeStamp;
    stk.push(u);
    inStack[u] = true;

    for (auto it = graph.getAdj()[u].begin(); it != graph.getAdj()[u].end(); it++) {
        Word &w = const_cast<Word &>(graph.getEdges()[*it]);
        int v = w.getAnEnd();
        if (dfn[v] == 0) {
            tarjan(v, graph, dfn, low, inStack, stk, scc);
            low[u] = min(low[u], low[v]);
        } else if (inStack[v]) {
            low[u] = min(low[u], dfn[v]);
        }
    }

    if (dfn[u] == low[u]) {
        vector<int> component;
        int v;
        do {
            v = stk.top();
            stk.pop();
            inStack[v] = false;
            component.push_back(v);
        } while (v != u);
        scc.push_back(component);
    }

    return 0;
}


int getScc(Graph graph, vector<vector<int>> &result) {
    vector<int> dfn(MAXN_POINT), low(MAXN_POINT), instack(MAXN_POINT);
    stack<int> stk;
    int r = 0;
    for (int i = 0; i < MAXN_POINT; i++) {
        if (dfn[i] == 0) {
            r = tarjan(i, graph, dfn, low, instack, stk, result);
            if (r != 0) {
                return r;
            }
        }
    }
    return 0;
}

int totalLetters(const vector<string> &vec) {
    int count = 0;
    for (const auto &str: vec) {
        count += static_cast<int>(str.size());
    }
    return count;
}

//得到图中任意两点的最长路径/最长字母数路径,传入26*26初始值为0的二维数组 TODO 这里可以直接记录路径，之后回溯时再做
//指定拒绝首字母，直接跳过这条路径
int getMaxDist(const Graph &graph, vector<vector<int>> &result, vector<vector<vector<string>>> &maxPathRecord, int i) {
    Config *config = Config::getInstance();
    for (int i = 0; i < 26; ++i) {
        if (i == config->getRejectLimit()) {
            continue; //指定拒绝首字母直接跳过
        }
        vector<bool> visited(graph.getEdgeCnt(), false);
        vector<string> path;
        vector<vector<string>> pathList;
        dfsGraph(graph, i, false, visited, path, pathList);
        for (const auto &vec: pathList) {
            int to = vec.back().back() - 'a';
            if (config->getState() == STATE_WORD_COUNT) { //记录最长单词数路径
                if (result[i][to] < vec.size()) {
                    result[i][to] = static_cast<int>(vec.size());//强制类型转换
                    maxPathRecord[i][to] = vec;
                }
            } else if (config->getState() == STATE_CHAR_COUNT) { //记录最长字母数路径
                int totolLetter = totalLetters(vec);
                if (result[i][to] < totolLetter) {
                    result[i][to] = totolLetter;
                    maxPathRecord[i][to] = vec;
                }
            }
        }
    }
    return 0;
}


//深克隆得到只包含points的生成子图
int getSubGraph(const Graph &graph, vector<int> points, Graph &newGraph, int i) {
    vector<string> words;
    for (const auto &it: graph.getEdges()) {
        int from = it.getBegin(), to = it.getAnEnd();
        if (find(points.begin(), points.end(), from) != points.end()
            && find(points.begin(), points.end(), to) != points.end()) { //起点终点都在这个强连通分量里
            const string &str = it.getStr();
            words.push_back(str);
        }
    }
    vector<Word> edges;
    int r = 0;
    r = genWordFromList(words, edges);
    if (r != 0) {
        return r;
    }
    newGraph = Graph(edges);
//    for(auto &e:newGraph.getEdges()){
//        cout << e.getId()<<endl;
//    }
    return 0;
}

int getSccId(const vector<vector<int>> &sccInput, int point, int &result) {
    int sccNum = static_cast<int>(sccInput.size());
    for (int i = 0; i < sccNum; i++) {
        vector<int> vec = sccInput[i];
        if (find(vec.begin(), vec.end(), point) != vec.end()) {
            result = i;
            return 0;
        }
    }
    //TODO 这个最后删掉
    cout << "error at getSccid" << endl;
    return -1;
}

//每一个强连通分量缩成一个点，返回新的图,这个图的边没有任何意义，只是为了拓扑排序
int getNewGraph(const Graph &graph, const vector<vector<int>> &sccInput, Graph &newGraph,
                vector<vector<vector<Word *>>> &edgesBetweenScc) {
    int r = 0;
    int sccNum = static_cast<int>(sccInput.size());
    vector<string> words;
    vector<Word> edges;
    //从每一个块A出发，遍历这个块里的所有点，遍历点的所有边，找到边对应的终点块号B，A ！= B，加一条A到B的边
    for (int fromScc = 0; fromScc < sccNum; fromScc++) {
        for (auto &point: sccInput[fromScc]) {
            for (auto it = graph.getAdj()[point].begin(); it != graph.getAdj()[point].end(); it++) {
                Word &w = const_cast<Word &>(graph.getEdges()[*it]);
                int to = w.getAnEnd();
                int toScc = -1;// 终点块号
                r = getSccId(sccInput, to, toScc);
                if (r != 0) {
                    return r;
                }
                if (toScc != fromScc) {
                    char a = static_cast<char>('a' + fromScc);
                    char b = static_cast<char>('a' + toScc);
                    string str = string(1, a) + b;;
                    words.push_back(str);
                    edgesBetweenScc[fromScc][toScc].push_back(&w);
                    w.setToSccId(toScc);
                }
            }
        }
    }
    genWordFromList(words, edges);
    newGraph = Graph(edges, true);//这里唯一一处ban掉Reject
    return 0;
}

int getSccTopoSort(const Graph &sccGraph, const int sccNum, vector<int> &results) {
    vector<int> preResults;
    int r = 0;
    r = topoSort(sccGraph, preResults);
    if (r != 0) {
        return r;
    }
    for (int i = 0; i < MAXN_POINT; i++) {
        if (preResults[i] >= 0 && preResults[i] < sccNum) {
            results.push_back(preResults[i]);
        }
    }
    return 0;
}


int dp_loop(const Graph &graph, vector<vector<string>> &result) {
    Config *config = Config::getInstance();
    //得到强连通分量分配结果
    vector<vector<int>> sccResult;
    int r = getScc(graph, sccResult);
    if (r != 0) {
        return r;
    }
    int sccNum = static_cast<int>(sccResult.size());//得到强连通分量个数
    //预处理每个强连通分量内部任意各点的最大距离 sccNum * 26 * 26 ,初始值为0
    vector<vector<vector<int>>> sccMaxDist(sccNum, vector<vector<int>>(26, vector<int>(26, 0)));
    vector<vector<vector<vector<string>>>> sccMaxPathRecord(sccNum, vector<vector<vector<string>>>(26,
                                                                                                   vector<vector<string>>(
                                                                                                           26)));//TODO 好丑 主要是记录每个SCC内任意两点的最长路径，避免以后还得找，但是应该有更好的数据结构
    for (int i = 0; i < sccNum; i++) {
        //第i个强连通分量的子图
        Graph sccGraph;
        getSubGraph(graph, sccResult[i], sccGraph, i);
        getMaxDist(sccGraph, sccMaxDist[i], sccMaxPathRecord[i], i);
    }
    //缩点
    Graph newGraph;
    vector<vector<vector<Word *>>> edgesBetweenScc(sccNum, vector<vector<Word *>>(sccNum));//强连通分量之间连接的word
    getNewGraph(graph, sccResult, newGraph, edgesBetweenScc);
    // 对缩点后的图，得到强连通分量的topo排序结果
    vector<int> sccTopoResults;
    getSccTopoSort(newGraph, sccNum, sccTopoResults);
    //以上为预处理

    //-----------------------------------------------------------------------------
    //开始dp
    //1.dp初始化

    vector<int> dp(MAXN_POINT, -1);
    vector<int> pre(MAXN_POINT, -1);//这里有所不同，我们存储了块之间的边的编号
    //dp[26]初始化为这个点所在SCC内，以这个点为结尾的最长单词数路径长度/字母数路径长度
    if (config->getHeadLimit() == -1) {
        for (int i = 0; i < sccNum; i++) { //第i个scc
            for (auto &point: sccResult[i]) { //第i个scc里面的点point
                int max = 0;
                for (int j = 0; j < MAXN_POINT; j++) { //找到第i个scc，sccMaxDist第point列的最大值
                    if (sccMaxDist[i][j][point] > max) {
                        max = sccMaxDist[i][j][point];
                    }
                }
                dp[point] = max;
            }
        }
    } else { //有首字母限制
        int head = config->getHeadLimit();
        //这个块内的点都要设置为从head到该点的长度
        int sccId;
        getSccId(sccResult, head, sccId);
        for (auto &point: sccResult[sccId]) {
            dp[point] = sccMaxDist[sccId][head][point];
        }
//        for (int i = 0; i < sccNum; i++) { //第i个scc
//            int flag = 0;
//            for (auto &point: sccResult[i]) { //第i个scc里面的点point
//                if (point == head) {
//                    int max = 0;
//                    for (int j = 0; j < MAXN_POINT; j++) { //找到第i个scc，sccMaxDist第point列的最大值
//                        if (sccMaxDist[i][j][point] > max) {
//                            max = sccMaxDist[i][j][point];
//                        }
//                    }
//                    dp[point] = max;
//                    flag = 1;
//                    break;
//                }
//            }
//            if (flag == 1) {
//                break;
//            }
//        }
    }

    //2. 开始推导dp数组
    for (int i = 0; i < sccNum; i++) {
        int fromScc = sccTopoResults[i]; //从topo第一个Scc开始
        for (auto &edgesFromScc: edgesBetweenScc[fromScc]) {
            for (auto &w: edgesFromScc) { //该Scc出发的边
                int from = w->getBegin();
                if (dp[from] < 0) {
                    continue;
                }
                int to = w->getAnEnd();
                int toScc = w->getToSccId();
                for (auto &pointInToScc: sccResult[toScc]) {
                    //更新toScc内的每一个点，记录pre
                    int tmp = 0;

                    if (config->getState() == STATE_WORD_COUNT) {
                        tmp = dp[from] + 1 + sccMaxDist[toScc][to][pointInToScc];
                    } else if (config->getState() == STATE_CHAR_COUNT) {
                        tmp = dp[from] + w->getLength() + sccMaxDist[toScc][to][pointInToScc];
                    }
                    if (tmp > dp[pointInToScc]) {
                        dp[pointInToScc] = tmp;
                        pre[pointInToScc] = w->getId();
                    }
                }
            }
        }
    }

    int n = 0;
    //找到最佳dp
    if (config->getTailLimit() != -1) { //指定尾字母
        n = config->getTailLimit();
    } else {
        int max = -1;
        n = -1;
        for (int i = 0; i < MAXN_POINT; i++) {
            if (dp[i] > max) {
                max = dp[i];
                n = i;
            }
        }
    }

    int sccId;
    getSccId(sccResult, n, sccId);
    //这里特判一下，既有-h 又有 -t
    if (config->getHeadLimit() != -1 && config->getTailLimit() != -1) {
        if (pre[n] == -1) {
            int headSccId;
            int head = config->getHeadLimit();
            getSccId(sccResult, head, headSccId);
            if (sccId == headSccId) {
                result.push_back(sccMaxPathRecord[sccId][head][n]);
                return 0;
            } else {
                return 0;
            }
        }
    }

    while (true) {
        if (pre[n] == -1) {

            int max = 0;
            int rec = -1;
            getSccId(sccResult, n, sccId);
            int head = config->getHeadLimit();
            if (head != -1) {
                result.push_back(sccMaxPathRecord[sccId][head][n]);
                break;
            }
            for (int j = 0; j < MAXN_POINT; j++) { //找到第i个scc，sccMaxDist第point列的最大值
                if (sccMaxDist[sccId][j][n] > max) {
                    max = sccMaxDist[sccId][j][n];
                    rec = j;
                }
            }
            if (rec == -1) {
                //找不到大于0，说明没有以这个点结尾的路径
                vector<string> v;
                result.push_back(v);
            } else {
                result.push_back(sccMaxPathRecord[sccId][rec][n]);
            }
            break;
        } else {
            Word &w = const_cast<Word &>(graph.getEdges()[pre[n]]);
            int from = w.getBegin();
            int to = w.getAnEnd();
            getSccId(sccResult, n, sccId);
            result.push_back(sccMaxPathRecord[sccId][to][n]);
            vector<string> s({w.getStr()});
            result.push_back(s);
            n = from;
        }
    }

    return 0;
}


