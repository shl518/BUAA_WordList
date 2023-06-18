//
// Created by cychen on 2023/3/7.
//

#include <string>
#include "../include/Word.h"
#include "../include/Utils.h"

Word::Word(const std::string &str) : str(str) {
    this->str = str;
    this->begin = char2int(str[0]);
    this->end = char2int(str.back());
    this->length = (int) str.length();
    this->toSccId = -1;
}

Word::Word() {
    this->str = std::string("");
    this->id = -1;
    this->begin = this->end = this->length = 0;
}

const std::string &Word::getStr() const {
    return str;
}

int Word::getBegin() const {
    return begin;
}

int Word::getAnEnd() const {
    return end;
}

int Word::getLength() const {
    return length;
}

void Word::setId(int _id) {
    Word::id = _id;
}
void Word::setToSccId(int _id) {
    Word::toSccId = _id;
}

int Word::getToSccId() const {
    return toSccId;
}

int Word::getId() const {
    return id;
}
