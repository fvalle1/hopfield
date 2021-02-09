#include "memory.h"
#include "model.h"
#include "tests/test.h"
#include "device.h"

using namespace std;

//#undef __APPLE__

int main()
{
    PrintDevices();

    // Test<std::function<void()>, StopwatchMillis>(test_1, "test 1");
    // Test<std::function<void()>, StopwatchMillis>(test_2, "test 2");
    // Test<std::function<void()>, StopwatchMillis>(test_3, "test 3");
    // Test<std::function<void()>, StopwatchMillis>(test_4, "test 4");
    // Test<std::function<void()>, StopwatchMillis>(test_5, "test 5");
    // Test<std::function<void()>, StopwatchMillis>(test_6, "test 6");

    // if (IsGPUAvailable())
    // {
    //     Test<std::function<void()>, StopwatchMillis>(test_7, "test 7");
    //     Test<std::function<void()>, StopwatchMillis>(test_8, "test 8");
    //     Test<std::function<void()>, StopwatchMillis>(test_9, "test 9");
    //     Test<std::function<void()>, StopwatchMillis>(test_10, "test 10");
    // }

    // Test<std::function<void()>, StopwatchMillis>(test_11, "test 11");

    auto reader = new Reader("X.txt");
    auto writer = new Writer("reconstructed.csv");
    auto training_dataset = vector<Memory>();
    Memory::SetSize(784);
    reader->read(training_dataset, ' ');

    auto model = Model(training_dataset.size(), training_dataset[0].size(), 12, kOMP);
    model.load_memories(training_dataset);

    model.train();

    auto corrupt_reader = new Reader("corrupted.txt");
    auto test_dataset = vector<Memory>();
    corrupt_reader->read(test_dataset, ' ');
    model.reconstruct(test_dataset[0]);

    writer->write(test_dataset);
    cout << endl
            << endl;

    //cout << model;

    training_dataset.clear();

    delete reader;
    delete writer;


    return 0;
}
