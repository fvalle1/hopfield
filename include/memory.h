#ifndef MEMORY_H
#define MEMORY_H

#include <cstring>
#include <iostream>
#include <fstream>
#include <stdarg.h>
#include <cassert>
#include <vector>
#include <algorithm>

#include "memory_I.h"

typedef unsigned char uint8_t;
typedef bool spin;

struct Memory : public Memory_I<uint8_t, int8_t>
{

    Memory();
    Memory(int size, ...);
    Memory(std::vector<int> data);
    Memory(const Memory &source);
    ~Memory();

    inline int operator[](uint16_t idx) { return fData[idx] ? 1 : -1; };
    inline uint16_t size() { return fSize; };
    inline uint16_t size_of() { return fSize * sizeof(spin); };
    friend std::ostream &operator<<(std::ostream &out, Memory &m);
    friend std::ofstream &operator<<(std::ofstream &out, Memory &m);

    inline static void SetSize(uint16_t size) { fSize = size; };

    spin *fData;

private:
    static uint16_t fSize;

    template <typename Streamer>
    static Streamer &PrintMe(Streamer &out, Memory &m, char sep = ' ');
};

#endif