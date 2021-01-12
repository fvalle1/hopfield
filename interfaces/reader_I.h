#ifndef READER_I_H
#define READER_I_H

#include <string>
#include <vector>

template <class Storable>
class Reader_I{
public:
    template<typename T>
    void read(T&&);
};

#endif