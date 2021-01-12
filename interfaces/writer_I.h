#ifndef WRITER_I_H
#define WRITER_I_H

template <class Storable>
class Writer_I
{
public:
    template <typename T>
    void write(T &&);
};

#endif