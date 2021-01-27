#ifndef TEST_H
#define TEST_H

#include <string>
#include <iostream>
#include <functional>

#include "tests.h"
#include "stopwatch.h"

template <typename test_type, typename stop_watch>
class Test
{
public:
Test(test_type f, std::string name){
    std::cout << std::endl;
    stop_watch sw(name);
    f();
    std::cout << std::endl;
};
};

#endif