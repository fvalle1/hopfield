#include "model.h"

Model::Model(uint8_t P, uint8_t N) : fP(P), fN(N)
{
    fState = kUninit;
    cout << "Creating model" << endl;
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

void Model::load_memories(std::vector<Memory> e)
{
    if (fState < kInit) init();
    

    cout << "Loading memories" << endl;
    for (uint8_t i = 0; i < fN; i++)
    {
        for (uint8_t j = 0; j < fN; j++)
        {
            auto psum = 0.;
            for (auto memory : e)
            {
                psum += memory(i) * memory(j);
            }

            fWeights[i * fN + j] += 1. / fN * psum;
        }
    }

    fState = kTrained;
    //w_ij = 1/N sum_mu e_i e_j
}

void Model::train()
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

void Model::predict(Memory img)
{
    if (fState < kTrained) {
        std::cerr<<"Please load_memories before predicting"<<std::endl;
        return;
    }

    cout << "Predicting" << endl;
    //set neurons
    std::memcpy(fNeurons, img.fData, img.size());
    train();
    std::memcpy(img.fData, fNeurons, fN);
}

void Model::reconstruct(Memory &img)
{
    cout << "Reconstructing" << endl;
    //set neurons
    predict(img);
    std::memcpy(img.fData, fNeurons, fN);
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
