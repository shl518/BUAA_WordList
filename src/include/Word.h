//
// Created by cychen on 2023/3/7.
//

#ifndef WORKLIST_WORD_H
#define WORKLIST_WORD_H

#include <string>

class Word {
private:
    std::string str;
    int begin, end;
    int length;
    int id;
    int toSccId;
public:
    Word();
    explicit Word(const std::string &str);

    const std::string &getStr() const;

    int getToSccId() const;

    int getId() const;

    void setId(int id);

    int getBegin() const;

    int getAnEnd() const;

    int getLength() const;

    void setToSccId(int _id);
};


#endif //WORKLIST_WORD_H
