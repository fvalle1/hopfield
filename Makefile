CXX=clang++
LINKER_FLAGS =-framework Metal -framework MetalKit -framework Cocoa -framework CoreFoundation -fobjc-link-runtime
COMPILER_FLAGS = -x objective-c++
INCLUDE_FLAGS = -Iinclude/ -Iinterfaces/
CFLAGS = -O3 -std=c++14
TARGETS = memory.o model.o matrix_helper.o mtlpp.so
TOCLEAN = *.o *.out
OBJECTS= argument.o compute_pipeline.o library.o sampler.o blit_command_encoder.o depth_stencil.o ns.o stage_input_output_descriptor.o buffer.o device.o parallel_render_command_encoder.o texture.o command_buffer.o                  drawable.o                        render_command_encoder.o          vertex_descriptor.o command_encoder.o   fence.o                           render_pass.o command_queue.o                   function_constant_values.o        render_pipeline.o compute_command_encoder.o         heap.o                            resource.o
LIBS = mtlpp.so


all: hopfield.out

hopfield.out: main.cpp $(TARGETS) $(LIBS)
	$(CXX) $(CFLAGS) $(INCLUDE_FLAGS) $(LINKER_FLAGS) $^ -o $@

%.o: src/%.cpp include/%.h
	$(CXX) $(CFLAGS) $(INCLUDE_FLAGS) -c $< -o $@

%.so: %.o
	ar rcs $@ $^

%.o: src/%.mm
	$(CXX) $(CFLAGS) $(INCLUDE_FLAGS) $(COMPILER_FLAGS) -c $< -o $@


.PHONY:
clean:
	rm -rf *.out *.o