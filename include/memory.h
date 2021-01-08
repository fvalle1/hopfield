#ifndef MEMORY_H
#define MEMORY_H

#include <cstring>
#include <iostream>
#include <stdarg.h>

#include "memory_I.h"

typedef unsigned char uint8_t;
typedef bool spin;

struct Memory : public Memory_I<uint8_t,int8_t>
{
    
Memory();
Memory(int size, ...);
Memory(const Memory &source);
~Memory();

inline int8_t operator[](uint8_t idx){return fData[idx]?1:-1;};
inline uint8_t size(){return fSize;};
inline uint8_t size_of() { return fSize * sizeof(spin); };
friend std::ostream& operator<<(std::ostream& out, Memory& m);

inline static void SetSize(uint8_t size) { fSize = size; };

spin *fData;

private:
    static uint8_t fSize;
};

#endif