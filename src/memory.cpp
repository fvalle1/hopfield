#include "memory.h"

uint16_t Memory::fSize = 6;

Memory::Memory()
{
    fData = new spin[fSize];
}

Memory::Memory(const Memory &source)
{
    fData = new spin[fSize];
    std::memcpy(this->fData, source.fData, source.fSize*sizeof(spin));
}

Memory::Memory(int size, ...)
{
    assert(size==fSize);
    va_list ap;
    va_start(ap, size);
    fData = new spin[fSize];
    for (auto i = 0; i < size; i++)
    {
        fData[i] = va_arg(ap, int) > 0;
    }
    va_end(ap);
}

Memory::Memory(std::vector<int> data)
{
    assert(data.size() == fSize);
    fData = new spin[fSize];
    uint8_t i = 0;
    std::for_each(data.begin(), data.end(), [this, &i](auto&& point) {
        this->fData[i++] = point > 0;
    });
}

Memory::~Memory(){
    delete fData;
}

std::ostream& operator<<(std::ostream &out, Memory &m)
{
    return Memory::PrintMe<std::ostream>(out, m, ' ');
}

std::ofstream &operator<<(std::ofstream &out, Memory &m)
{
    return Memory::PrintMe<std::ofstream>(out, m, ',');
}

template<typename Streamer>
Streamer& Memory::PrintMe(Streamer& out, Memory &m, char sep){
    auto i = 0;
    for (; i < m.fSize - 1; i++)
    {
        out << (m[i] > 0 ? 1 : 0) << sep;
    }
    out << (m[i] > 0 ? 1 : 0);
    return out;
}