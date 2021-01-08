#include "memory.h"
#include "model.h"

using namespace std;

int main(){
    std::vector<Memory> training_dataset;
    training_dataset.emplace_back(Memory(5, 0, 0, 1, 0, 0));
    training_dataset.emplace_back(Memory(5, 1, 1, 1, 0, 0));

    auto model = Model(training_dataset.size(), training_dataset[0].size());
    model.load_memories(training_dataset);

    bool corrupted_data[] = {1, 1, 1, 1, 0};
    Memory corrupted_memory;
    std::memmove(corrupted_memory.fData, corrupted_data, corrupted_memory.size_of());

    model.reconstruct(corrupted_memory);

    cout<<"Reconstructed: "<<endl;
    for(uint8_t i=0;i<corrupted_memory.size();i++){
        cout << corrupted_memory.fData[i]<<" ";
    }
    cout<<endl<<endl;

    cout<<model;

    return 0;
}