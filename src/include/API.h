//
// Created by cychen on 2023/3/7.
//

/*
 * API: 只写六条需求的API
 */

/*
 * 实现`int gen_chain_word(char* words[], int len, char* result[], char head, char tail, bool enable_loop)`接口，计算**最多单词数量**的最长单词链，其中前三个参数已经在上文进行了说明，`head`和`tail`分别为单词链**首字母**与**尾字母**约束（如果传入0，表示没有约束），当`enable_loop`为`true`时表示**允许**输入单词文本中隐含“单词环”
 * 实现`int gen_chains_all(char* words[], int len, char* result[])` 接口，参数的意义同上，函数返回所有符合定义的单词链，函数返回值为单词链的总数
 * 实现`int gen_chain_word_unique(char* words[], int len, char* result[])` 接口，参数的意义同上，函数返回首字母不同的，单词数最多的单词链，函数返回值为单词链的长度
 * 实现`int gen_chain_char(char* words[], int len, char* result[], char head, char tail, bool enable_loop)`接口，计算**最多字母数量**的最长单词链，参数意义同`gen_chain_word`
 * 指针数组result的长度上限为20000，超出上限时报错并保证返回值正确，此时输出到solution.txt中的单词链可以为空。
 */

#ifndef WORKLIST_API_H
extern "C" {
__declspec(dllexport) int gen_chains_all(char* words[], int len, char** &result);
__declspec(dllexport)int gen_chain_word(char* words[], int len, char** &result, char head, char tail, char reject, bool enable_loop);
__declspec(dllexport) int gen_chain_char(char* words[], int len, char** &result, char head, char tail, char reject, bool enable_loop);

};
#define WORKLIST_API_H



#endif //WORKLIST_API_H




