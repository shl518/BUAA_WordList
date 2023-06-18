//
// Created by cychen on 2023/3/10.
//

#ifndef LIST_ERROR_H
#include <string>
#include <vector>

using namespace std;


    string genErrorInfo(int ErrorCode, string Info);
extern "C" {

__declspec(dllexport) void throwError(int ErrorCode, string Info);

__declspec(dllexport) int checkConfig();
}
#define LIST_ERROR_H



#endif //LIST_ERROR_H
