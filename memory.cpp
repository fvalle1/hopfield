#include "memory.h"

std::ostream &operator<<(std::ostream &out, Memory &m){
    for (uint8_t i = 0; i < m.fSize; i++)
    {
        out<<m(i)<<" ";
    }
    out<<std::endl;
    return out;
}