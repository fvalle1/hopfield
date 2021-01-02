#ifndef MEMORY_I_H
#define MEMORY_I_H

template <typename sizeType, typename spinType>
struct Memory_I
{
    spinType operator()(sizeType idx);
    sizeType size();
};

#endif