#ifndef MODEL_H
#define MODEL_H

#include <cstring>
#include <vector>
#include <iostream>

#include <thread>
#include <mutex>

#ifdef _OPENMP
    #include <omp.h>
#endif

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
    Model(uint16_t P, uint16_t N, size_t num_threads = 4, devices device = kNull);

    ~Model();

    friend std::ostream &operator<<(std::ostream &out, Model &m);

    void load_memories(std::vector<Memory>);
    void train(devices device = kNull);
    void predict(Memory);
    void reconstruct(Memory &);

private:
    void init();
    void trainCPU();
    void train(size_t num_threads);
    #ifdef _OPENMP
    void trainOMP(size_t num_threads);
    #endif
    #ifdef __APPLE__
    void trainGPU();
    #endif
    static void sum_neurons(const uint16_t , const uint16_t , const uint16_t, const float *, spin *);
    static void set_weights(const uint16_t start, const uint16_t end, const uint16_t N, const std::vector<Memory> &e, float *weights);

    states fState;
    uint16_t fP;
    uint16_t fN;
    size_t fNumThreads;
    spin* fNeurons;
    float *fWeights;
    devices fDevice;

    static std::mutex fLoading_mutex;
};

#endif