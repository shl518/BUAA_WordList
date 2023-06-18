//
// Created by Lenovo on 2023/3/11.
//
#include "../../googletest/include/gtest//gtest.h"

extern "C" int gen_chains_all(char *words[], int len, char **&result);

extern "C" int gen_chain_word(char *words[], int len, char **&result, char head, char tail, char reject, bool enable_loop);

extern "C" int gen_chain_char(char *words[], int len, char **&result, char head, char tail, char reject, bool enable_loop);

class FileIOTest : public ::testing::Test {
protected:
    void SetUp() override {
    }

    void TearDown() override {
    }
};

bool chainIsValid(int len, char **result, char head, char tail, char reject) {
    if (len == 0) {
        return true;
    }
    //验证head
    if (head != 0) {
        if (result[0][0] != head) {
            return false;
        }
    }
    //验证tail
    if (tail != 0) {
        char *s = result[len - 1];
        char last_char = s[strlen(s) - 1];
        if (last_char != tail) {
            return false;
        }
    }
    //验证reject
    for (int i = 0; i < len; i++) {
        if (reject != 0 && result[i][0] == reject) {
            return false;
        }
    }
    //验证首尾相接
    for (int i = 1; i <= len - 1; i++) {
        char *pre = result[i - 1];
        char *next = result[i];
        char last_char = pre[strlen(pre) - 1];
        char first_char = next[0];
        if (last_char != first_char) {
            return false;
        }
    }
    return true;
}

//无环简单测试
TEST(HelloTest, BasicAssertions) {
    const char *words[] = {"aa", "ab", "bc"};
    char **result;
    int l = gen_chain_word(const_cast<char **>(words), 3, result, 'a', 0, 0, false);
    EXPECT_TRUE(chainIsValid(l, result, 'a', 0, 0));
    EXPECT_EQ(l, 3);
}

//有环复杂测试
TEST(core, 1) {
    const char *words[] = {"ababa", "adoctb", "boxa",
                           "cx", "aac", "cotb", "bard", "dddddddddddddddddddddddddddddd",
                           "cec", "ce", "ef", "fg", "ge", "cff", "fgg", "gee", "f", "ff",
                           "fff", "ffff",};
    char **result;
    int l = gen_chain_word(const_cast<char **>(words), 20, result, 0, 0, 0, true);
    EXPECT_TRUE(chainIsValid(l, result, 0, 0, 0));
    EXPECT_EQ(l, 15);
}


int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}