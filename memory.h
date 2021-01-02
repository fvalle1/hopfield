#ifndef MEMORY_H
#define MEMORY_H

#include <cstring>
#include <iostream>

typedef unsigned char uint8_t;
typedef bool spin;

struct Memory{
Memory(){
    fData = new spin[fSize];
}

Memory(const Memory &source){
    fData = new spin[fSize];
    std::memcpy(this->fData, source.fData, source.fSize);
}

~Memory(){
    delete fData;
}

int8_t operator()(uint8_t idx){return fData[idx]?1:-1;};
uint8_t size(){return fSize;};
friend std::ostream& operator<<(std::ostream& out, Memory& m);

spin *fData;

private:
    static constexpr uint8_t fSize = 5;
};

#endif