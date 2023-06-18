//
// Created by cychen on 2023/3/7.
//

#include "Input.h"
#include <cctype>
#include <vector>
#include <fstream>
#include <getopt.h>
#include <algorithm>
#include <cstring>
#include "../include/ErrorCode.h"

using namespace std;

extern "C" int setConfig(int _state, int _head, int _tail, int _reject, bool _ring, string &_filePath);

extern "C" void throwError(int ErrorCode, string Info);

int char2int_(char c) {
    int r = -1;
    if (islower(c)) {
        r = c - 'a';
    } else if (isupper(c)) {
        r = c - 'A';
    }
    return r;
}

int execPreprocess(int argc, char *argv[], vector<string> &result) {
    int r = 0;
    string fileData;
    parseArgument(argc, argv, fileData);
    getWordFromStr(fileData, result);
    return r;
}


string toLowercase(string str) {
    std::transform(str.begin(), str.end(), str.begin(),
                   [](unsigned char c) { return std::tolower(c); });
    return str;
}

int getWordFromStr(string str, vector<string> &wordList) {
    int r = 0;
    int begin = 0;
    bool lexState = false;
    unsigned long long len = str.length();
    for (int i = 0; i < len; ++i) {
        if (isalpha(str[i])) {
            if (!lexState) {
                // 开始解析
                begin = i;
                lexState = true;
            }
        } else {
            if (lexState) {
                string newStr = str.substr(begin, i - begin);
                wordList.push_back(toLowercase(newStr));
                lexState = false;
            }
        }
    }
    if (lexState) {
        wordList.push_back(toLowercase(str.substr(begin)));
    }

    return r;
}

int readFile(const string &filePath, string &result) {
    // "为处理简单起见，输入的单词文本限定为以.txt扩展名结尾的文件。"
    int r = 0;
    if (filePath.substr(filePath.length() - 4) != ".txt") {
        r = ILLEGAL_FILE;
        throwError(r, (string &) filePath);
    }
    std::ifstream inFile(filePath.c_str());
    if (inFile.good()) {
        std::string content((std::istreambuf_iterator<char>(inFile)), // 读取文件内容到字符串中
                            (std::istreambuf_iterator<char>()));
        result.assign(content);
        inFile.close();
    } else {
        throwError(NOT_EXIST_FILE, (string &) filePath);
        r = -1;
    }
    return r;
}

bool moreThanOnePara(char *argv[]) {
    return optarg != nullptr
           && argv[optind] != nullptr
           && argv[optind][0] != '-';
}

// command -> Config对象
int parseArgument(int argc, char *argv[], string &result) {
    int r = 0;
    static struct option long_options[] = {
            {"num",         required_argument, nullptr, 'n'},
            {"wordCount",   required_argument, nullptr, 'w'},
            {"charCount",   required_argument, nullptr, 'c'},
            {"headLimit",   required_argument, nullptr, 'h'},
            {"tailLimit",   required_argument, nullptr, 't'},
            {"rejectLimit", required_argument, nullptr, 'j'},
            {"ring",        no_argument,       nullptr, 'r'},
            {nullptr,       0,                 nullptr, 0}
    };
    int c;

    int state = STATE_EMPTY;
    int head = -1;
    int tail = -1;
    int reject = -1;
    bool ring = false;
    string filePath;
    while ((c = getopt_long(argc, argv, "n:w:c:h:t:j:r", long_options, nullptr)) != -1) {
        switch (c) {
            case 'n':
            case 'w':
            case 'c': {
                // file path
                if (state != STATE_EMPTY) {
                    r = MORE_THAN_ONE_STATE;
                    throwError(r, string(1, (char) c));
                }
                switch (c) {
                    case 'n':
                        state = STATE_NUM;
                        break;
                    case 'w':
                        state = STATE_WORD_COUNT;
                        break;
                    case 'c':
                        state = STATE_CHAR_COUNT;
                        break;
                    default:
                        break;
                }
                if (optarg == nullptr) {
                    r = LACK_OF_FILE;
                    throwError(r, NO_INFO);
                } else if (moreThanOnePara(argv)) {
                    // 如果选项多于一个参数
                    r = MORE_THAN_ONE_FILE;
                    throwError(r, string(1, (char) c));
                }
                filePath = optarg;
                break;
            }
            case 'h':
            case 't':
            case 'j': {
                if (optarg == nullptr) {
                    r = LACK_OF_CHAR;
                    throwError(r, string(1, (char) c));
                } else if (moreThanOnePara(argv) || strlen(optarg) != 1) {
                    r = MORE_THAN_ONE_CHAR;
                    throwError(r, string(1, (char) c));
                } else if (!isalpha(optarg[0])) {
                    r = ILLEGAL_PARAMETER_VALUE;
                    throwError(r, string(1, (char) c));
                }
                switch (c) {
                    case 'h': {
                        if (head != -1) {
                            r = DUPLICATE_PARAMETER;
                            throwError(r, string(1, (char) c));
                        }
                        head = char2int_(optarg[0]);
                        break;
                    }
                    case 't': {
                        if (tail != -1) {
                            r = DUPLICATE_PARAMETER;
                            throwError(r, string(1, (char) c));
                        }
                        tail = (char2int_(optarg[0]));
                        break;
                    }
                    case 'j': {
                        if (reject != -1) {
                            r = DUPLICATE_PARAMETER;
                            throwError(r, string(1, (char) c));
                        }
                        reject = (char2int_(optarg[0]));
                        break;
                    }
                    default:
                        break;
                }
                break;
            }
            case 'r': {
                if (optarg != nullptr) {
                    r = UNEXPECTED_PARAMETER;
                    throwError(r, string(1, (char) c));
                }
                if (ring) {
                    r = DUPLICATE_PARAMETER;
                    throwError(r, string(1, (char) c));
                }
                ring = true;
                break;
            }
            default: {
                if (argv[optind] != nullptr
                    && argv[optind][0] == '-') {
                    r = NOT_EXIST_PARAMETER;
                    throwError(r, string(1, (char) c));
                }
                break;
            }
        }
    }

    if (!filePath.empty()) {
        setConfig(state, head, tail, reject, ring, filePath);
        readFile(filePath, result);
    } else {
        r = -1;
    }
    return r;
}

