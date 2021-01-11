#ifndef MATRIX_H
#define MATRIX_H

#include <metal_stdlib>
using namespace metal;

kernel void matvecmul(
    const device float *A [[buffer(0)]],
    const device float *B [[buffer(1)]],
    device float *vOut [[buffer(2)]],
    const device uint16_t *params [[buffer(3)]],
    uint id [[thread_position_in_grid]])
{
    uint16_t N = params[0];
    uint16_t K = params[1];
    uint16_t row = id;
    float temp = 0.0;
    for (uint16_t k = 0; k < K; k++)
    {
        temp += A[row * K + k] * B[k];
    }
    vOut[id] = temp;
}

#endif