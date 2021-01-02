#ifndef MODEL_H
#define MODEL_H

#include <cstring>
#include <vector>
#include <iostream>

#include "model_I.h"
#include "memory.h"

using std::cout;
using std::endl;

enum states{
    kUninit,
    kInit,
    kTrained
};

class Model : public Model_I<Memory>
{
public:
    Model(uint8_t P, uint8_t N);

    ~Model();

    friend std::ostream &operator<<(std::ostream &out, Model &m);

    void load_memories(std::vector<Memory>);
    void train();
    void predict(Memory);
    void reconstruct(Memory&);

private:
    void init();

    states fState;
    uint8_t fP;
    uint8_t fN;
    spin *fNeurons;
    float *fWeights;
};

#endif