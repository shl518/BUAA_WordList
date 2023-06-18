//
// Created by cychen on 2023/3/8.
//

#ifndef LIST_CONFIG_H
#define LIST_CONFIG_H

#include <string>
#include <ostream>
#include "Const.h"

using namespace std;

class Config {
private:
    static Config *instance;
    bool ring = false;
    int headLimit = -1;
    int tailLimit = -1;
    int rejectLimit = -1;
    int state = STATE_EMPTY;
    string filePath;

    Config() = default;

public:
    static Config *getInstance();

    void setRing(bool _ring) {
        Config::ring = _ring;
    }

    void setHeadLimit(int _headLimit) {
        Config::headLimit = _headLimit;
    }

    void setTailLimit(int _tailLimit) {
        Config::tailLimit = _tailLimit;
    }

    void setRejectLimit(int _rejectLimit) {
        Config::rejectLimit = _rejectLimit;
    }

    void setState(int _state) {
        Config::state = _state;
    }

    void setFilePath(const string &_filePath) {
        Config::filePath = _filePath;
    }


    const string &getFilePath() const {
        return filePath;
    }

    bool isRing() const {
        return ring;
    }

    int getHeadLimit() const {
        return headLimit;
    }

    int getTailLimit() const {
        return tailLimit;
    }

    int getRejectLimit() const {
        return rejectLimit;
    }

    int getState() const {
        return state;
    }

    friend ostream &operator<<(ostream &os, const Config &config) {
        os << "ring: " << config.ring << " headLimit: " << config.headLimit << " tailLimit: " << config.tailLimit
           << " rejectLimit: " << config.rejectLimit << " state: " << config.state << " filePath: " << config.filePath;
        return os;
    }

};


#endif //LIST_CONFIG_H
