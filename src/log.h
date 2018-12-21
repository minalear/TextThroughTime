//
// Created by Trevor Fisher on 10/11/2018.
//

#ifndef TEXTTHROUGHTIME_LOG_H
#define TEXTTHROUGHTIME_LOG_H

#include <string>

class Log {
    std::string *lines;
    int capacity, size;

    void shift();

public:
    explicit Log(int capacity=500);
    ~Log();

    void add(std::string str);
    void remove(int i);
    void clear();
    int count();

    std::string operator[](int i);
};


#endif //TEXTTHROUGHTIME_LOG_H
