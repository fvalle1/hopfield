#ifndef STOPWATCH_H
#define STOPWATCH_H

#include "stopwatch_I.h"

class Stopwatch: public Stopwatch_I<std::chrono::seconds, Seconds>
{
public:
    Stopwatch(std::string name = ""):Stopwatch_I(name){};
    ~Stopwatch(){};
};

class StopwatchMillis : public Stopwatch_I<std::chrono::milliseconds, Milliseconds>
{
public:
    StopwatchMillis(std::string name = "") : Stopwatch_I(name){};
    ~StopwatchMillis(){};
};

#endif //STOPWATCH_H