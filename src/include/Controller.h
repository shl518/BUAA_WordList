//
// Created by cychen on 2023/3/10.
//

#ifndef LIST_CONTROLLER_H
#include <vector>
#include <string>
#include "../preprocess/Input.h"
#include "Config.h"

using namespace std;
extern "C" {
// 伪main函数，只供命令行程序使用
__declspec(dllexport) int execCalculation(vector<string> wordList);

__declspec(dllexport) int setConfig(int _state, int _head, int _tail, int _reject, bool _ring, string &_filePath);
}
#define LIST_CONTROLLER_H


/* for -n
 * words: 文件内容分割出的单词，Input::getWordFromStr的第二个参数；
 * count: 单词链数目
 * result: 存放结果单词链集合
 * config: 命令行参数，Input创建的全局静态变量；这里其实没啥用了。
 */
int genChainsAllCtrl(vector<string> &words, vector<vector<string>> &result);

/* for -w
 * words: 文件内容分割出的单词，Input::getWordFromStr的第二个参数；
 * result: 存放结果单词链
 * config: 命令行参数，Input创建的全局静态变量
*/
int genChainWordCtrl(vector<string> &words, vector<string> &result);

/* for -c
 * words: 文件内容分割出的单词，Input::getWordFromStr的第二个参数；
 * result: 存放结果单词链
 * config: 命令行参数，Input创建的全局静态变量
*/
int genChainCharCtrl(vector<string> &words, vector<string> &result);

int printChain(char* chain[], int len);
#endif //LIST_CONTROLLER_H
