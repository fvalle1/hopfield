![Compile](https://github.com/fvalle1/hopfield/workflows/Compile/badge.svg)
![Compile w/o Metal](https://github.com/fvalle1/hopfield/workflows/Compile%20w/o%20Metal/badge.svg)
![Compile CMake](https://github.com/fvalle1/hopfield/workflows/Compile%20CMake/badge.svg?branch=main)
![Run Ubuntu](https://github.com/fvalle1/hopfield/workflows/Run%20Ubuntu/badge.svg)
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

# run
```bash
./hopfield
```

On Apple devices be sure to run from the home folder (shaders are required to be in the correct path at runtime)

# Issues
The Github Action RunMacOS sometime fails due to lack of GPU access.

# License
See [LICENSE](LICENSE)
