//
// Created by cychen on 2023/3/8.
//

#include <string>
#include <vector>
#include "preprocess/Input.h"

extern "C" __declspec(dllimport) int execCalculation(vector<string>);

int main(int argc, char *argv[]) {
    std::vector<std::string> wordList;
    // execPreprocess: 解析参数->设置Config->读文件，同时检查参数输入错误
    execPreprocess(argc, argv, wordList);
    execCalculation(wordList);

//      vector<string> wordList;
//      execPreprocess(argc, argv, wordList);
//      execCalculation(wordList);
//    const char* words[]= {"ababa","adoctb","boxa",
//                          "cx","aac","cotb","bard","dddddddddddddddddddddddddddddd",
//                          "cec","ce","ef","fg","ge","cff","fgg","gee","f","ff",
//                          "fff","ffff"};
//    char** result;
//    int l = gen_chain_word(const_cast<char **>(words), 20, result, 0, 0, 0, true);
//    cout << l <<endl;
//    for(int i = 0;i<l;i++){
//        cout << result[i]<<endl;
//    }

    return 0;
}