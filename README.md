![CI](https://github.com/fvalle1/hopfield/workflows/Compile/badge.svg)
![Run](https://github.com/fvalle1/hopfield/workflows/Run/badge.svg)

# hopfield
hopfield network implementation in C++

# compile
```bash
make
```

## Linux
This repository uses the [Metal](https://developer.apple.com/metal/) framework to offload jobs to GPU. This works only on Apple machines and it is not supported by other systems. If you are running under Linux, please compile using
```bash
make all_nometal CXX=g++
```

It will ceate an executable called *hopfield_nometal.out*

# run
```bash
./hopfield
```

# License
See [LICENSE](LICENSE)
