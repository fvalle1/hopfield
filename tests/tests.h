#include <iostream>
#include <vector>

#include "memory.h"
#include "reader.h"
#include "writer.h"
#include "stopwatch.h"

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

    model.train();
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

    model.train();
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

    model.train();
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

    model.train();
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

void test_5()
{
    std::vector<Memory> training_dataset;
    training_dataset.reserve(100);
    Memory::SetSize(10);
    for (size_t i = 0; i < 100; i++)
    {
        training_dataset.emplace_back(Memory(10, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1));
    }

    auto model = Model(training_dataset.size(), training_dataset[0].size());
    model.load_memories(training_dataset);

    spin corrupted_data[] = {1, 1, 1, 0, 1, 1, 0, 1, 1, 1};
    Memory corrupted_memory;
    std::memmove(corrupted_memory.fData, corrupted_data, corrupted_memory.size_of());

    model.train();
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

void test_6()
{
    std::vector<Memory> training_dataset;
    training_dataset.reserve(100);
    Memory::SetSize(10);
    for (size_t i = 0; i < 100; i++)
    {
        training_dataset.emplace_back(Memory(10, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1));
    }

    auto model = Model(training_dataset.size(), training_dataset[0].size());
    model.load_memories(training_dataset);

    spin corrupted_data[] = {1, 1, 1, 0, 1, 1, 0, 1, 1, 1};
    Memory corrupted_memory;
    std::memmove(corrupted_memory.fData, corrupted_data, corrupted_memory.size_of());

    model.train(kMultiThread);
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

void test_7()
{
    std::vector<Memory> training_dataset;
    training_dataset.reserve(100);
    Memory::SetSize(10);
    for (size_t i = 0; i < 100; i++)
    {
        training_dataset.emplace_back(Memory(10, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1));
    }

    auto model = Model(training_dataset.size(), training_dataset[0].size());
    model.load_memories(training_dataset);

    spin corrupted_data[] = {1, 1, 1, 0, 1, 1, 0, 1, 1, 1};
    Memory corrupted_memory;
    std::memmove(corrupted_memory.fData, corrupted_data, corrupted_memory.size_of());

    model.train(kGPU);
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

void test_8(){
    auto reader = new Reader("test.csv");
    auto training_dataset = vector<Memory>();
    Memory::SetSize(3);
    reader->read(training_dataset);

    auto model = Model(training_dataset.size(), training_dataset[0].size());
    model.load_memories(training_dataset);

    spin corrupted_data[] = {1, 0, 1};
    Memory corrupted_memory;
    std::memmove(corrupted_memory.fData, corrupted_data, corrupted_memory.size_of());

    model.train(kGPU);
    model.reconstruct(corrupted_memory);

    cout << "Reconstructed: " << endl;
    for (uint8_t i = 0; i < corrupted_memory.size(); i++)
    {
        cout << corrupted_memory.fData[i] << " ";
    }
    cout << endl
         << endl;

    cout << model;

    training_dataset.clear();

    delete reader;
}

void test_9()
{
    auto reader = new Reader("test.csv");
    auto writer = new Writer("test_out.csv");
    auto training_dataset = vector<Memory>();
    Memory::SetSize(3);
    reader->read(training_dataset);

    auto model = Model(training_dataset.size(), training_dataset[0].size());
    model.load_memories(training_dataset);

    spin corrupted_data[] = {1, 0, 1};
    Memory corrupted_memory;
    std::memmove(corrupted_memory.fData, corrupted_data, corrupted_memory.size_of());

    model.train(kGPU);
    model.reconstruct(corrupted_memory);
    auto out = std::vector<Memory>();
    out.push_back(corrupted_memory);

    writer->write(out);
    cout << endl
         << endl;

    cout << model;

    training_dataset.clear();

    delete reader;
    delete writer;
}

void test_10(){
    auto reader = new Reader("test.csv");
    auto writer = new Writer("reconstructed.csv");
    auto training_dataset = vector<Memory>();
    Memory::SetSize(3);
    reader->read(training_dataset, ',');

    auto model = Model(training_dataset.size(), training_dataset[0].size());
    model.load_memories(training_dataset);

    model.train(kGPU);

    auto corrupt_reader = new Reader("corrupted.csv");
    auto test_dataset = vector<Memory>();
    corrupt_reader->read(test_dataset, ',');
    model.reconstruct(test_dataset[0]);

    writer->write(test_dataset);
    cout << endl
         << endl;

    cout << model;

    training_dataset.clear();

    delete reader;
    delete writer;
}

void test_11()
{
    std::vector<Memory> training_dataset;
    
    Memory::SetSize(6);
    training_dataset.emplace_back(Memory(6, 1, 1, 0, 0, 1, 1));
    training_dataset.emplace_back(Memory(6, 1, 1, 1, 1, 1, 1));

    auto model = Model(training_dataset.size(), training_dataset[0].size(), 4, kOMP);
    model.load_memories(training_dataset);

    spin corrupted_data[] = {1, 1, 1, 1, 1, 0};
    Memory corrupted_memory;
    std::memmove(corrupted_memory.fData, corrupted_data, corrupted_memory.size_of());

    model.train();
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