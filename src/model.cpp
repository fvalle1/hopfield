#include "model.h"

std::mutex Model::fLoading_mutex;

Model::Model(uint16_t P, uint16_t N, size_t num_threads, devices device) : fP(P),
                                                                           fN(N),
                                                                           fNumThreads(num_threads),
                                                                           fDevice(device)
{
    fState = kUninit;
    cout << "Creating model" << endl;
    cout << "with " << fN << " neurons" << endl;
    cout << "and " << fP << " memories" << endl;
    fNeurons = new spin[fN];
    fWeights = new float[fN * fN];
};

Model::~Model()
{
    cout << "Destroying model" << endl;
    delete fNeurons;
    delete fWeights;
};

void Model::init()
{
    for (auto i = 0; i < fN; i++)
    {
        fNeurons[i] = 1;
        for (auto j = 0; j < fN; j++)
        {
            fWeights[i * fN + j] = 0;
        }
    }
    fState = kInit;
}

void Model::set_weights(const uint16_t start, const uint16_t end, const uint16_t N, const std::vector<Memory> &e, float *weights)
{
    for (auto i = start; i < end; i++)
    {
        for (auto j = 0; j < N; j++)
        {
            auto psum = 0.;
            for (auto memory : e)
            {
                psum += memory[i] * memory[j];
            }
            {
                std::lock_guard<std::mutex> guard(fLoading_mutex);
                weights[i * N + j] += 1. / N * psum;
            }
        }
    }
}

void Model::load_memories(std::vector<Memory> e)
{
    if (fState < kInit)
        init();

    cout << "Loading memories" << endl;

    using std::thread;
    thread workers[fNumThreads];
    uint16_t step = fN / fNumThreads;
    {
        size_t t = 0;
        for (; t < fNumThreads - 1; t++)
        {
            workers[t] = thread(Model::set_weights, t * step, (t + 1) * step, std::ref(fN), std::ref(e), std::ref(fWeights));
        }
        workers[t] = thread(Model::set_weights, t * step, fN, std::ref(fN), std::ref(e), std::ref(fWeights));
    }
    for (size_t t = 0; t < fNumThreads; t++)
    {
        workers[t].join();
    }

    fState = kTrained;
    //w_ij = 1/N sum_mu e_i e_j
}

void Model::train(devices device)
{
    if (device != kNull)
        fDevice = device;

    switch (fDevice)
    {
    case kNull:
        trainCPU();
        break;
    case kCPU:
        trainCPU();
        break;
    case kMultiThread:
        train(fNumThreads);
        break;
    case kOMP:
#ifdef _OPENMP
        trainOMP(fNumThreads);
#else
        std::cerr<<"OpenMP not available"<<std::endl;
        train(fNumThreads);
#endif
        break;
    case kGPU:
    #ifdef __APPLE__
        trainGPU();
        #else
        std::cerr<<"GPU not available"<<std::endl;
        train(fNumThreads);
    #endif
        break;
    default:
        break;
    }
}

void Model::trainCPU()
{
    cout << "Training model [CPU]" << endl;
    for (auto i = 0; i < fN; i++)
    {
        auto h = 0.;
        for (auto j = 0; j < fN; j++)
        {
            h += fWeights[i * fN + j] * (fNeurons[j] ? 1 : -1);
        }

        fNeurons[i] = h > 0.;
    }
    //h_i = sum_j w_ij S_j
    //S_i=sgn(h_i)
}

void Model::sum_neurons(const uint16_t start, const uint16_t end, const uint16_t N, const float *weight, spin *neurons)
{

    for (auto i = start; i < end; i++)
    {
        auto h = 0.;
        for (auto j = 0; j < N; j++)
        {
            h += weight[i * N + j] * (neurons[j] ? 1 : -1);
        }

        neurons[i] = h > 0.;
    }
}

void Model::train(size_t num_threads)
{
    cout << "Training model [std::thread]" << endl;

    using std::thread;
    thread workers[num_threads];
    uint8_t step = fN / num_threads;
    {
        size_t t = 0;
        for (; t < num_threads - 1; t++)
        {
            workers[t] = thread(Model::sum_neurons, t * step, (t + 1) * step, std::ref(fN), std::ref(fWeights), std::ref(fNeurons));
        }
        workers[t] = thread(Model::sum_neurons, t * step, fN, std::ref(fN), std::ref(fWeights), std::ref(fNeurons));
    }
    for (size_t t = 0; t < num_threads; t++)
    {
        workers[t].join();
    }

    //h_i = sum_j w_ij S_j
    //S_i=sgn(h_i)
}

#ifdef __APPLE__
void Model::trainGPU()
{
    cout << "Training model [GPU]" << endl;

    float h[fN];

    multiply_matrix_vector(fWeights, fNeurons, h, this->fN, this->fN);

    for (auto i = 0; i < fN; i++)
    {
        fNeurons[i] = h[i] > 0.;
    }

    //h_i = sum_j w_ij S_j
    //S_i=sgn(h_i)
}
#endif

#ifdef _OPENMP
void Model::trainOMP(size_t num_threads){
    cout << "Training model [OpenMP]" << endl;
   
    omp_set_num_threads(num_threads);
    omp_set_nested(1);

#pragma omp parallel for shared(fWeights, fNeurons)
    for (auto i = 0; i < fN; i++)
    {
        auto h = 0.;
#pragma omp parallel for shared(fWeights, fNeurons) reduction(+: h)
        for (auto j = 0; j < fN; j++)
        {
            h += fWeights[i * fN + j] * (fNeurons[j] ? 1 : -1);
        }

        #pragma omp atomic write
        fNeurons[i] = h > 0.;
    }
}
#endif

void Model::predict(Memory img)
{
    if (fState < kTrained)
    {
        std::cerr << "Please load_memories before predicting" << std::endl;
        return;
    }

    cout << "Predicting" << endl;
    //set neurons
    std::memcpy(fNeurons, img.fData, img.size_of());
    train();
    std::memcpy(img.fData, fNeurons, fN * sizeof(spin));
}

void Model::reconstruct(Memory &img)
{
    cout << "Reconstructing" << endl;
    //set neurons
    predict(img);
    std::memcpy(img.fData, fNeurons, fN * sizeof(spin));
}

std::ostream &operator<<(std::ostream &out, Model &m)
{
    out << "*********** Model ***********" << endl;
    out << "***** Weights *****" << endl;
    for (auto i = 0; i < m.fN; i++)
    {
        for (auto j = 0; j < m.fN; j++)
        {
            out << m.fWeights[i * m.fN + j] << "\t";
        }
        out << endl;
    }

    out << "***** Neurons *****" << endl;
    for (auto i = 0; i < m.fN; i++)
    {
        out << m.fNeurons[i] << "\t";
    }
    out << endl;

    return out;
}
