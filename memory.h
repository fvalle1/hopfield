#ifndef MEMORY_H
#define MEMORY_H

#include <cstring>
#include <iostream>
#include <stdarg.h>

typedef unsigned char uint8_t;
typedef bool spin;

struct Memory{
    
Memory();
Memory(int size, ...);
Memory(const Memory &source);
~Memory();

int8_t operator()(uint8_t idx){return fData[idx]?1:-1;};
uint8_t size(){return fSize;};
friend std::ostream& operator<<(std::ostream& out, Memory& m);

spin *fData;

private:
    static constexpr uint8_t fSize = 5;
};

#endif