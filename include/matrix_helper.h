#ifndef MATRIX_HELPER
#define MATRIX_HELPER

#include <stdio.h>
#include <iostream>
#include <chrono>
#include <thread>
#include <cmath>
#include <numeric>
#include <cstring>
#include <exception>

#ifdef __APPLE__
#include "mtlpp.hpp"

void multiply_matrix_vector(void *, void *, void *, const uint16_t, const uint16_t);
void multiply_matrix_matrix(void *, void *, void *, const uint16_t, const uint16_t, const uint16_t);
#endif


#endif