cmake_minimum_required(VERSION 3.16..)
project(hopfield)

set (CMAKE_CXX_STANDARD 14)
set (CMAKE_CXX_FLAGS -O3)

find_package(OpenMP)
if (OpenMP_CXX_FOUND)
endif()

include_directories(
    include/
    interfaces/
    tests/)

set(FILES 
    main.cpp
    src/device.cpp
    src/memory.cpp
    src/model.cpp
    src/reader.cpp
    src/writer.cpp
    src/stopwatch.cpp
)

if(APPLE)
add_executable(hopfield
                ${FILES}
                src/matrix_helper.cpp
)

add_library(mtlpp
            src/mtlpp.mm
)

target_compile_options(mtlpp PRIVATE -x objective-c++)
target_link_libraries(hopfield PUBLIC
            "-framework Metal"
            "-framework MetalKit"
            "-framework Cocoa"
            "-framework CoreFoundation"
            "-fobjc-link-runtime"
            mtlpp
            )
else()
find_package(Threads)
add_executable(hopfield
                ${FILES}
)

target_link_libraries(hopfield PUBLIC ${CMAKE_THREAD_LIBS_INIT})
endif()

if(OpenMP_CXX_FOUND)
    target_link_libraries(hopfield PUBLIC OpenMP::OpenMP_CXX)
endif()