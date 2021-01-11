#ifndef MODEL_H
#define MODEL_H

#include <cstring>
#include <vector>
#include <iostream>

#include <thread>
#include <mutex>

#include "model_I.h"
#include "memory.h"
#include "matrix_helper.h"


using std::cout;
using std::endl;

enum states
{
    kUninit,
    kInit,
    kTrained
};

class Model : public Model_I<Memory>
{
public:
    Model(uint8_t P, uint8_t N, size_t num_threads = 4);

    ~Model();

    friend std::ostream &operator<<(std::ostream &out, Model &m);

    void load_memories(std::vector<Memory>);
    void train();
    void train(size_t num_threads);
    void trainGPU();
    void predict(Memory);
    void reconstruct(Memory &);

private:
    void init();
    static void sum_neurons(const uint8_t , const uint8_t , const uint8_t, const float *, spin *);
    static void set_weights(const uint8_t start, const uint8_t end, const uint8_t N, const std::vector<Memory> &e, float *weights);

    states fState;
    uint8_t fP;
    uint8_t fN;
    size_t fNumThreads;
    spin *fNeurons;
    float *fWeights;

    static std::mutex fLoading_mutex;
};

#endif