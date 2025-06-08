#include <iostream>
#include <functional>
#include <common.cuh>
#include "v1.h"

using datatype = float;
using kernel_function = std::function<void(uint, uint, uint, float*, float*, float*)>;

// todo
std::vector<kernel_function> kernels;

int main()
{
    constexpr int M = 1024, N = 16, K = 1024;
    constexpr int loop_time = 1;
    
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
    // check if the kernel give correct result.
    kernels.push_back(run_v1);
    ///////////////////////////////////////////////////////////////
    
    Timer t;
    for(int i = 0; i < kernels.size(); i ++)
    {
        const auto& kernel = kernels[i];
        t.start();

        for(int j = 0; j < loop_time; j ++)
        {
            kernel(M, N, K, d_a, d_b, d_c);
        }
        t.stop();
        t.report_sgemm_with_loop(M, N, K, alpha, beta, loop_time);
        t.reset();

    }

    ///////////////////////////////////////////////////////////////

    cudaFree(h_a);
    cudaFree(h_b);
    cudaFree(h_c);
    cudaFree(d_a);
    cudaFree(d_b);
    cudaFree(d_c);

    return 0;
}
