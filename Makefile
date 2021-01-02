CXX = clang++
CFLAGS = -O3 -std=c++14
TARGETS = memory.o model.o


all: hopfield.out

hopfield.out: main.cpp $(TARGETS)
	$(CXX) $(CFLAGS) $^ -o $@

%.o: %.cpp
	$(CXX) $(CFLAGS) -c $< -o $@

.PHONY:
clean:
	rm -rf *.out *.o