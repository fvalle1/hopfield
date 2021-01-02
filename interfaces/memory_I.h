#ifndef MEMORY_I_H
#define MEMORY_I_H

#include <cstring>
#include <iostream>
#include <stdarg.h>

template <typename sizeType, typename spinType>
struct Memory_I
{
    spinType operator()(sizeType idx);
    sizeType size();
};

#endif