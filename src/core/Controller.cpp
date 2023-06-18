//
// Created by cychen on 2023/3/10.
//

#include <iostream>
#include "../include/Controller.h"
#include "../postprocess/Output.h"
#include "../include/Graph.h"
#include "../include/Utils.h"
#include "../include/Const.h"
#include "../include/ErrorCode.h"
#include "../include/Error.h"
#include "../include/API.h"

int execCalculation(vector<string> wordList) {
    int len = (int) wordList.size();
    char **words;
    vectorToCharArray(wordList, words);
    Config *config = Config::getInstance();
    char **result;
    int ret = 0;
    checkConfig();

    switch (config->getState()) {
        case STATE_NUM: {
            ret = gen_chains_all(words, len, result);

            break;
        }
        case STATE_WORD_COUNT: {
            ret = gen_chain_word(words, len, result,
                                 int2char(config->getHeadLimit()),
                                 int2char(config->getTailLimit()),
                                 int2char(config->getRejectLimit()),
                                 config->isRing());
            break;
        }
        case STATE_CHAR_COUNT: {
            ret = gen_chain_char(words, len, result,
                                 int2char(config->getHeadLimit()),
                                 int2char(config->getTailLimit()),
                                 int2char(config->getRejectLimit()),
                                 config->isRing());
            break;
        }
        default:
            cout << "Config is empty" << endl;
            std::exit(0);
    }
    cout << ret << endl;
    printChain(result, ret);
    return 0;
}

int genChainsAllCtrl(vector<string> &words, vector<vector<string>> &result) {
    //直接调用dfs遍历所有路径即可
    int r = 0;
    vector<Word> edges;
    genWordFromList(words, edges);
    Graph graph = Graph(edges);
    if (hasCycle(graph)) {
        r = NOT_EXIST_RING_PARA;
        throwError(r, NO_INFO);
    }
    for (int i = 0; i < edges.size(); ++i) {
        cout << edges[i].getId() << endl;
    }
    for (int i = 0; i < 26; ++i) {
        vector<bool> visited(graph.getEdgeCnt(), false);
        vector<string> path;
        dfsGraph(graph, i, true, visited, path, result);
    }

    return r;
}

int genChainWordCtrl(vector<string> &words, vector<string> &result) {
    Config *config = Config::getInstance();
    //TODO 目前仅适用于无环
    int r = 0;
    vector<Word> edges;
    genWordFromList(words, edges);
    Graph graph = Graph(edges);
    if (!config->isRing()) {
        if (hasCycle(graph)) {
            r = NOT_EXIST_RING_PARA;
            throwError(r, NO_INFO);
        }
        vector<int> dp_results;
        //直接调用dp_loopless返回逆序结果
        dp_loopless(graph, dp_results);
        int len = static_cast<int>(dp_results.size());
        for (int i = len - 1; i >= 0; i--) {
            //逆向遍历
            int point = dp_results[i];
            if (i < len - 1) {
                Word betweenPath = graph.getEdgeBetween(dp_results[i + 1], dp_results[i]);
                result.push_back(betweenPath.getStr());
            }
            vector<string> selfPath = graph.getSelfEdgeChain(point);
            for (auto &str: selfPath) {
                result.push_back(str);
            }
        }
    } else {
        vector<vector<string>> dp_loop_results;
        dp_loop(graph, dp_loop_results);
        int s = static_cast<int>(dp_loop_results.size());
        for (int i = s - 1; i >= 0; i--) {
            for (auto &str: dp_loop_results[i]) {
                result.push_back(str);
            }
        }

    }
    return 0;
};

int genChainCharCtrl(vector<string> &words, vector<string> &result) {
    Config *config = Config::getInstance();
    int r = 0;
    vector<Word> edges;
    genWordFromList(words, edges);
    Graph graph = Graph(edges);
    if (!config->isRing()) {
        if (hasCycle(graph)) {
            r = NOT_EXIST_RING_PARA;
            throwError(r, NO_INFO);
        }
        vector<int> dp_results;
        //直接调用dp_loopless返回逆序结果
        dp_loopless(graph, dp_results);
        int len = static_cast<int>(dp_results.size());
        for (int i = len - 1; i >= 0; i--) {
            //逆向遍历
            int point = dp_results[i];
            if (i < len - 1) {
                Word betweenPath = graph.getEdgeBetween(dp_results[i + 1], dp_results[i], true);
                result.push_back(betweenPath.getStr());
            }
            vector<string> selfPath = graph.getSelfEdgeChain(point);
            result.insert(result.end(), selfPath.begin(), selfPath.end());
        }
    } else {
        vector<vector<string>> dp_loop_results;
        dp_loop(graph, dp_loop_results);
        int s = static_cast<int>(dp_loop_results.size());
        for (int i = s - 1; i >= 0; i--) {
            for (auto &str: dp_loop_results[i]) {
                result.push_back(str);
            }
        }
    }
    return 0;
}

int printChain(char *chain[], int len) {
    int r = 0;
    if (len < 2) {
        return 0;
    }
    for (int i = 0; i < len; ++i) {
        cout << chain[i] << endl;
    }
    return r;
}

int setConfig(int _state, int _head, int _tail, int _reject, bool _ring, string &_filePath) {
    Config *config = Config::getInstance();
    if (_state != -1) {
        config->setState(_state);
    }
    if (_head != -1) {
        config->setHeadLimit(_head);
    }
    if (_tail != -1) {
        config->setTailLimit(_tail);
    }
    config->setRing(_ring);
    if (_filePath.length() > 0) {
        config->setFilePath(_filePath);
    }
    return 0;
}


