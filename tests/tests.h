#include <iostream>
#include <vector>

#include "memory.h"
#include "memory.h"

using namespace std;

void test_1()
{
    std::vector<Memory> training_dataset;
    training_dataset.emplace_back(Memory(6, 1, 1, 0, 0, 1, 1));
    training_dataset.emplace_back(Memory(6, 1, 1, 1, 1, 1, 1));

    auto model = Model(training_dataset.size(), training_dataset[0].size());
    model.load_memories(training_dataset);

    spin corrupted_data[] = {1, 1, 1, 1, 1, 0};
    Memory corrupted_memory;
    std::memmove(corrupted_memory.fData, corrupted_data, corrupted_memory.size_of());

    model.reconstruct(corrupted_memory);

    cout << "Reconstructed: " << endl;
    for (uint8_t i = 0; i < corrupted_memory.size(); i++)
    {
        cout << corrupted_memory.fData[i] << " ";
    }
    cout << endl
         << endl;

    cout << model;
}

void test_2()
{
    std::vector<Memory> training_dataset;
    training_dataset.emplace_back(Memory(6, 1, 1, 0, 0, 1, 1));
    training_dataset.emplace_back(Memory(6, 1, 1, 1, 1, 1, 1));
    training_dataset.emplace_back(Memory(6, 0, 0, 1, 1, 0, 0));
    training_dataset.emplace_back(Memory(6, 1, 1, 1, 1, 1, 1));

    auto model = Model(training_dataset.size(), training_dataset[0].size());
    model.load_memories(training_dataset);

    spin corrupted_data[] = {1, 1, 0, 0, 1, 0};
    Memory corrupted_memory;
    std::memmove(corrupted_memory.fData, corrupted_data, corrupted_memory.size_of());

    model.reconstruct(corrupted_memory);

    cout << "Reconstructed: " << endl;
    for (uint8_t i = 0; i < corrupted_memory.size(); i++)
    {
        cout << corrupted_memory.fData[i] << " ";
    }
    cout << endl
         << endl;

    cout << model;
}

void test_3()
{
    std::vector<Memory> training_dataset;
    training_dataset.emplace_back(Memory(6, 1, 1, 1, 1, 1, 1));
    training_dataset.emplace_back(Memory(6, 1, 1, 1, 1, 1, 1));
    training_dataset.emplace_back(Memory(6, 1, 1, 1, 1, 1, 1));
    training_dataset.emplace_back(Memory(6, 1, 1, 1, 1, 1, 1));
    training_dataset.emplace_back(Memory(6, 1, 1, 1, 1, 1, 1));
    training_dataset.emplace_back(Memory(6, 1, 1, 1, 1, 1, 1));
    training_dataset.emplace_back(Memory(6, 1, 1, 1, 1, 1, 1));
    training_dataset.emplace_back(Memory(6, 1, 1, 1, 1, 1, 1));

    auto model = Model(training_dataset.size(), training_dataset[0].size());
    model.load_memories(training_dataset);

    spin corrupted_data[] = {1, 1, 0, 0, 1, 0};
    Memory corrupted_memory;
    std::memmove(corrupted_memory.fData, corrupted_data, corrupted_memory.size_of());

    model.reconstruct(corrupted_memory);

    cout << "Reconstructed: " << endl;
    for (uint8_t i = 0; i < corrupted_memory.size(); i++)
    {
        cout << corrupted_memory.fData[i] << " ";
    }
    cout << endl
         << endl;

    cout << model;
}

void test_4()
{
    std::vector<Memory> training_dataset;
    training_dataset.reserve(100);
    for (size_t i = 0; i < 100; i++)
    {
        training_dataset.emplace_back(Memory(6, 1, 1, 1, 0, 0, 1));
    }

    auto model = Model(training_dataset.size(), training_dataset[0].size());
    model.load_memories(training_dataset);

    spin corrupted_data[] = {1, 1, 0, 0, 1, 0};
    Memory corrupted_memory;
    std::memmove(corrupted_memory.fData, corrupted_data, corrupted_memory.size_of());

    model.reconstruct(corrupted_memory);

    cout << "Reconstructed: " << endl;
    for (uint8_t i = 0; i < corrupted_memory.size(); i++)
    {
        cout << corrupted_memory.fData[i] << " ";
    }
    cout << endl
         << endl;

    cout << model;
}