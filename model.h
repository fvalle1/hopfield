#ifndef MODEL_H
#define MODEL_H

#include <cstring>
#include <vector>
#include <iostream>

#include "memory.h"

using std::cout;
using std::endl;

enum states{
    kUninit,
    kInit,
    kTrained
};

class Model
{
public:
    Model(uint8_t P, uint8_t N) : fP(P), fN(N)
    {
        fState = kUninit;
        cout<< "Creating model" << endl;
        fNeurons = new bool[fN];
        fWeights = new float[fN * fN];
    };

    ~Model()
    {
        cout << "Destroying model" << endl;
        delete fNeurons;
        delete fWeights;
    };

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
    bool *fNeurons;
    float *fWeights;
};

#endif