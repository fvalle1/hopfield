#include "memory.h"

uint8_t Memory::fSize = 6;

Memory::Memory()
{
    fData = new spin[fSize];
}

Memory::Memory(const Memory &source)
{
    fData = new spin[fSize];
    std::memcpy(this->fData, source.fData, source.fSize);
}

Memory::Memory(int size, ...)
{
    va_list ap;
    va_start(ap, size);
    fData = new spin[fSize];
    for (uint8_t i = 0; i < size; i++)
    {
        fData[i] = va_arg(ap, int) > 0;
    }
    va_end(ap);
}

Memory::~Memory(){
    delete fData;
}

std::ostream& operator<<(std::ostream &out, Memory &m)
{
    for (uint8_t i = 0; i < m.fSize; i++)
    {
        out<<(static_cast<int>(m[i])>0?1:0)<<" ";
    }
    out<<std::endl;
    return out;
}