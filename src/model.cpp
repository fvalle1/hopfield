#include "model.h"

std::mutex Model::fLoading_mutex;

Model::Model(uint8_t P, uint8_t N, size_t num_threads, devices device) : fP(P),
                                                                         fN(N),
                                                                         fNumThreads(num_threads),
                                                                         fDevice(device)
{
    fState = kUninit;
    cout << "Creating model" << endl;
    cout << "with " << (unsigned int)fN << " neurons" << endl;
    cout << "and " << (unsigned int)fP << " memories" << endl;
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
    for (uint8_t i = 0; i < fN; i++)
    {
        fNeurons[i] = 1;
        for (uint8_t j = 0; j < fN; j++)
        {
            fWeights[i * fN + j] = 0;
        }
    }
    fState = kInit;
}

void Model::set_weights(const uint8_t start, const uint8_t end, const uint8_t N, const std::vector<Memory> &e, float *weights)
{
    for (uint8_t i = start; i < end; i++)
    {
        for (uint8_t j = 0; j < N; j++)
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
    uint8_t step = fN / fNumThreads;
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
    case kGPU:
        trainGPU();
        break;
    default:
        break;
    }
}

void Model::trainCPU()
{
    cout << "Training model" << endl;
    for (uint8_t i = 0; i < fN; i++)
    {
        auto h = 0.;
        for (uint8_t j = 0; j < fN; j++)
        {
            h += fWeights[i * fN + j] * (fNeurons[j] ? 1 : -1);
        }

        fNeurons[i] = h > 0.;
    }
    //h_i = sum_j w_ij S_j
    //S_i=sgn(h_i)
}

void Model::sum_neurons(const uint8_t start, const uint8_t end, const uint8_t N, const float *weight, spin *neurons)
{

    for (uint8_t i = start; i < end; i++)
    {
        auto h = 0.;
        for (uint8_t j = 0; j < N; j++)
        {
            h += weight[i * N + j] * (neurons[j] ? 1 : -1);
        }

        neurons[i] = h > 0.;
    }
}

void Model::train(size_t num_threads)
{
    cout << "Training model" << endl;

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

void Model::trainGPU()
{
    cout << "Training model on GPU" << endl;

    float h[fN];

    multiply_matrix_vector(fWeights, fNeurons, h, this->fN, this->fN);

    for (uint8_t i = 0; i < fN; i++)
    {
        fNeurons[i] = h[i] > 0.;
    }

    //h_i = sum_j w_ij S_j
    //S_i=sgn(h_i)
}

void Model::predict(Memory img)
{
    if (fState < kTrained)
    {
        std::cerr << "Please load_memories before predicting" << std::endl;
        return;
    }

    cout << "Predicting" << endl;
    //set neurons
    std::memcpy(fNeurons, img.fData, img.size());
    train();
    std::memcpy(img.fData, fNeurons, fN * sizeof(uint8_t));
}

void Model::reconstruct(Memory &img)
{
    cout << "Reconstructing" << endl;
    //set neurons
    predict(img);
    std::memcpy(img.fData, fNeurons, fN * sizeof(uint8_t));
}

std::ostream &operator<<(std::ostream &out, Model &m)
{
    out << "*********** Model ***********" << endl;
    out << "***** Weights *****" << endl;
    for (uint8_t i = 0; i < m.fN; i++)
    {
        for (uint8_t j = 0; j < m.fN; j++)
        {
            out << m.fWeights[i * m.fN + j] << "\t";
        }
        out << endl;
    }

    out << "***** Neurons *****" << endl;
    for (uint8_t i = 0; i < m.fN; i++)
    {
        out << m.fNeurons[i] << "\t";
    }
    out << endl;

    return out;
}
