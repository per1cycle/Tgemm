#include <iostream>
#include <common.cuh>
#include "v1.h"

using datatype = float;

int main()
{
    constexpr int M = 1024, N = 16, K = 1024;
    constexpr int loop_time = 100;
    
    datatype *h_a, *h_b, *h_c;
    datatype *d_a, *d_b, *d_c;
    datatype alpha = 1.0f, beta = 0.0f;

    cudaMallocHost(&h_a, sizeof(datatype) * M * K);
    cudaMallocHost(&h_b, sizeof(datatype) * K * N);
    cudaMallocHost(&h_c, sizeof(datatype) * M * N);

    cudaMalloc(&d_a, sizeof(datatype) * M * K);
    cudaMalloc(&d_b, sizeof(datatype) * K * N);
    cudaMalloc(&d_c, sizeof(datatype) * M * N);

    cudaMemcpy(d_a, h_a, sizeof(datatype) * M * K, cudaMemcpyHostToDevice);
    cudaMemcpy(d_b, h_b, sizeof(datatype) * K * N, cudaMemcpyHostToDevice);
    cudaMemcpy(d_c, h_c, sizeof(datatype) * M * N, cudaMemcpyHostToDevice);
    for(int i = 0; i < loop_time; i ++) run_v1(M, N, K, d_a, d_b, d_c);

    ///////////////////////////////////////////////////////////////
    Timer t;
    t.start();
    for(int i = 0; i < loop_time; i ++)
        run_v1(M, N, K, d_a, d_b, d_c);
    t.stop();
    ///////////////////////////////////////////////////////////////

    cudaFree(h_a);
    cudaFree(h_b);
    cudaFree(h_c);
    cudaFree(d_a);
    cudaFree(d_b);
    cudaFree(d_c);

    return 0;
}