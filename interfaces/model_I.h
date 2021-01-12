#ifndef MODEL_I_H
#define MODEL_I_H

#include <vector>

enum devices
{
    kNull,
    kCPU,
    kMultiThread,
    kGPU
};

template <class data>
class Model_I
{
    virtual void load_memories(std::vector<data>);
    virtual void train(devices);
    virtual void predict(data);
    virtual void reconstruct(data &);
};

#endif