#include "memory.h"
#include "model.h"

using namespace std;

int main(){
    bool memory[] = {0, 0, 1, 0, 0};
    Memory m;
    std::memmove(m.fData, memory, m.size());
    cout<<m<<endl;

    bool memory_1[] = {1, 1, 1, 0, 0};
    Memory m_1;
    std::memmove(m_1.fData, memory_1, m_1.size());

    std::vector<Memory> training_dataset;
    training_dataset.push_back(m);
    training_dataset.push_back(m_1);

    auto model = Model(training_dataset.size(), m.size());
    model.load_memories(training_dataset);
    model.train();

    bool corrupted_data[] = {1, 1, 0, 0, 0};
    Memory corrupted_memory;
    std::memmove(corrupted_memory.fData, corrupted_data, corrupted_memory.size());

    model.reconstruct(corrupted_memory);

    cout<<"Reconstructed: "<<endl;
    for(uint8_t i=0;i<corrupted_memory.size();i++){
        cout << corrupted_memory.fData[i]<<" ";
    }
    cout<<endl;

    cout<<model;

    return 0;
}