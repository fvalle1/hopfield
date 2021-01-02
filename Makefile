CXX = clang++
CFLAGS = -O3 -std=c++14
TARGETS = memory.o model.o
INCLUDES = -Iinclude/ -Iinterfaces/


all: hopfield.out

hopfield.out: main.cpp $(TARGETS)
	$(CXX) $(CFLAGS) $(INCLUDES) $^ -o $@

%.o: src/%.cpp include/%.h
	$(CXX) $(CFLAGS) $(INCLUDES) -c $< -o $@

.PHONY:
clean:
	rm -rf *.out *.o