//
// Created by cychen on 2023/3/10.
//

#include <sstream>
#include <iostream>
#include <utility>
#include "../include/Error.h"
#include "../include/ErrorCode.h"
#include "../include/Config.h"

string genErrorInfo(int ErrorCode, string Info) {
    stringstream ErrorInfo;
    ErrorInfo << "Error: ";
    switch (ErrorCode) {
        case NOT_EXIST_FILE:
            ErrorInfo << "找不到文件: " << Info;
            break;
        case ILLEGAL_FILE:
            ErrorInfo << "文件不合法，可能是格式非.txt";
            break;
        case LACK_OF_FILE:
            ErrorInfo << "未输入文件";
            break;
        case MORE_THAN_ONE_FILE:
            ErrorInfo << "输入多于一个文件";
            break;
        case NOT_EXIST_PARAMETER:
            ErrorInfo << "输入参数: -" << Info[0] << " 不存在";
            break;
        case DUPLICATE_PARAMETER:
            ErrorInfo << "重复输入参数: -" << Info[0];
            break;
        case MORE_THAN_ONE_CHAR:
            ErrorInfo << "输入参数: -" << Info[0] << " 的值多于一个字符";
            break;
        case LACK_OF_CHAR:
            ErrorInfo << "输入参数: -" << Info[0] << " 缺少值";
            break;
        case ILLEGAL_PARAMETER_VALUE:
            ErrorInfo << "输入参数: -" << Info[0] << " 的值不是合法字母";
            break;
        case MORE_THAN_ONE_STATE:
            ErrorInfo << "输入参数: -" << Info[0] << " 指定了多于一项任务";
            break;
        case LACK_OF_STATE:
            ErrorInfo << "输入参数未指定任务";
            break;
        case NOT_EXIST_RING_PARA:
            ErrorInfo << "输入参数不包含 -r, 但单词文本包含隐含环";
            break;
        case UNEXPECTED_PARAMETER:
            ErrorInfo << "输入参数: " << Info[0] << " 不应出现值";
        case NOT_COMPATIBLE_PARAMETER:
            ErrorInfo << "参数不兼容";
            break;
        case HEAD_TAIL_LIMIT_SAME:
            ErrorInfo << "单词文本不包含隐含环, 但首尾指定了同一字母，这是矛盾的";
            break;
        case HEAD_LIMIT_CONTRADICTION:
            ErrorInfo << "-h 和 -j 指定的字母相同, 这是矛盾的";
            break;
        case UNDEFINED_EXCEPTION:
            ErrorInfo << "未定义的错误";
            break;
        default:
            ErrorInfo << "";
            break;
    }
    return ErrorInfo.str();
}

void throwError(int ErrorCode, string Info) {
    string ErrorInfo = genErrorInfo(ErrorCode, std::move(Info));
    cout << ErrorCode << endl;
    exit(0);
}

int checkConfig() {
    int r = 0;
    Config *config = Config::getInstance();
    // 缺少任务
    if (config->getState() == STATE_EMPTY) {
        r = LACK_OF_STATE;
        throwError(r, NO_INFO);
    }

    // 无-r首位限制相同
    if (!config->isRing()
        && config->getHeadLimit() == config->getTailLimit()
        && config->getHeadLimit() != -1) {
        r = HEAD_TAIL_LIMIT_SAME;
        throwError(r, NO_INFO);
    }

    // 首字母限制矛盾
    if (config->getHeadLimit() == config->getRejectLimit()
        && config->getHeadLimit() != -1) {
        r = HEAD_LIMIT_CONTRADICTION;
        throwError(r, NO_INFO);
    }
    return r;
}
