//
// Created by cychen on 2023/3/7.
//

#include "../include/API.h"
#include "../include/Controller.h"
#include "../include/Error.h"
#include "../include/Utils.h"

using namespace std;

int gen_chains_all(char *words[], int len, char **&result) {
    Config *config = Config::getInstance();

    if (config->getState() == STATE_EMPTY) {
        config->setState(STATE_NUM);
        checkConfig();
    }

    vector<std::string> str_vector;

    for (int i = 0; i < len; i++) {
        string str(words[i]);
        str_vector.push_back(str);
    }
    vector<vector<string>> preResult;
    genChainsAllCtrl(str_vector, preResult);

    //输出
    getOutPutChar(preResult, result);
    return 0;

}

int gen_chain_word(char *words[], int len, char **&result, char head, char tail, char reject, bool enable_loop) {
    Config *config = Config::getInstance();

    if (config->getState() == STATE_EMPTY) {
        if (!isalpha(head)) {
            config->setHeadLimit(-1);
        } else {
            config->setHeadLimit(head - 'a');
        }
        if (!isalpha(tail)) {
            config->setTailLimit(-1);
        } else {
            config->setTailLimit(tail - 'a');
        }
        if (!isalpha(reject)) {
            config->setRejectLimit(-1);
        } else {
            config->setRejectLimit(reject - 'a');
        }
        config->setRing(enable_loop);
        config->setState(STATE_WORD_COUNT);
        checkConfig();
    }

    vector<std::string> str_vector;

    for (int i = 0; i < len; i++) {
        string str(words[i]);
        str_vector.push_back(str);
    }
    vector<string> preResult;
    genChainWordCtrl(str_vector, preResult);
    vectorToCharArray(preResult, result);
    int l = static_cast<int>(preResult.size());
    return l;
}

int gen_chain_char(char *words[], int len, char **&result, char head, char tail, char reject, bool enable_loop) {
    Config *config = Config::getInstance();
    if (config->getState() == STATE_EMPTY) {
        if (!isalpha(head)) {
            config->setHeadLimit(-1);
        } else {
            config->setHeadLimit(head - 'a');
        }
        if (!isalpha(tail)) {
            config->setTailLimit(-1);
        } else {
            config->setTailLimit(tail - 'a');
        }
        if (!isalpha(reject)) {
            config->setRejectLimit(-1);
        } else {
            config->setRejectLimit(reject - 'a');
        }
        config->setRing(enable_loop);
        config->setState(STATE_CHAR_COUNT);
        checkConfig();
    }

    vector<std::string> str_vector;

    for (int i = 0; i < len; i++) {
        string str(words[i]);
        str_vector.push_back(str);
    }
    vector<string> preResult;
    genChainCharCtrl(str_vector, preResult);
    vectorToCharArray(preResult, result);
    return static_cast<int>(preResult.size());
}