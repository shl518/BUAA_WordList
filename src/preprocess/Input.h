//
// Created by cychen on 2023/3/7.
//

#ifndef WORKLIST_INPUT_H
#define WORKLIST_INPUT_H
#define STATE_EMPTY 0
#define STATE_NUM 1
#define STATE_WORD_COUNT 2
#define STATE_CHAR_COUNT 3
#include <string>
#include <utility>
#include <vector>
#include <ostream>
#include "../include/Word.h"

using namespace std;

int execPreprocess(int argc, char *argv[], vector<string>& result);

string toLowercase(string str);

int char2int_(char c);

int getWordFromStr(string str, vector<string> &wordList);

bool moreThanOnePara(char *argv[]);

// *FILE -> string
int readFile(const string &filePath, string &result);

int parseArgument(int argc, char *argv[], string &result);



#endif //WORKLIST_INPUT_H
