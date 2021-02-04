![Compile](https://github.com/fvalle1/hopfield/workflows/Compile/badge.svg)
![Compile w/o Metal](https://github.com/fvalle1/hopfield/workflows/Compile%20w/o%20Metal/badge.svg)
![Build CMake Linux](https://github.com/fvalle1/hopfield/workflows/Build%20CMake/badge.svg?branch=main)
![Build CMake Macos](https://github.com/fvalle1/hopfield/workflows/Build%20CMake%20Macos/badge.svg)
![Run Linux](https://github.com/fvalle1/hopfield/workflows/Run%20Ubuntu/badge.svg)
![Run MacOS](https://github.com/fvalle1/hopfield/workflows/Run/badge.svg)

# hopfield
hopfield network implementation in C++

# compile
```bash
mkdir build && cd build
cmake ..
make
```

## Linux
This repository uses the [Metal](https://developer.apple.com/metal/) framework to offload jobs to GPU. This works only on Apple machines and it is not supported by other systems. If you are running under Linux, please compile using
```bash
make all_nometal CXX=g++
```
it will ceate an executable called *hopfield_nometal.out*

Alternatively you can use *cmake* which automatically handles libraries

```bash
mkdir build && cd build
cmake ..
make
```

# Run
```bash
./hopfield
```

On Apple devices be sure to run from the home folder (shaders are required to be in the correct path at runtime)

# Example
```cpp

    // Create a dataset with memories
    std::vector<Memory> training_dataset;
    training_dataset.emplace_back(Memory(6, 1, 1, 0, 0, 1, 1));
    training_dataset.emplace_back(Memory(6, 1, 1, 1, 1, 1, 1));

    //Create a model
    auto model = Model(training_dataset.size(), training_dataset[0].size());
    model.load_memories(training_dataset);


    // Build a corrupted memory
    spin corrupted_data[] = {1, 1, 1, 1, 1, 0};
    Memory corrupted_memory;
    std::memmove(corrupted_memory.fData, corrupted_data, corrupted_memory.size_of());

    // Train the model. Use can use kNull, kCPU, kGPU, kMultiThread, kOMP
    // If the chosen device is not available another one is automatically picked up
    model.train(kCPU);
    model.reconstruct(corrupted_memory);

    cout << "Reconstructed: " << endl;
    for (uint8_t i = 0; i < corrupted_memory.size(); i++) cout << corrupted_memory.fData[i] << " ";

    cout << model;
```

More examples are in the [tests](tests/tests.h) folder.

# Issues
The Github Action RunMacOS sometime fails due to lack of GPU access.

# License
See [LICENSE](LICENSE)
