//
// Created by cychen on 2023/3/8.
//

#include "../include/Config.h"

Config *Config::instance = nullptr;

Config *Config::getInstance() {
    if (instance == nullptr) {
        instance = new Config();
    }
    return instance;
}
