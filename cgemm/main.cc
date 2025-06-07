#include <iostream>
#include <functional>
#include <typeinfo>
#include <iterator>
#include <common.cuh>
#include "v1.h"

using datatype = float;
using kernel_function = std::function<void(uint, uint, uint, float*, float*, float*)>;

// todo
std::vector<kernel_function> kernels;

int main()
{
    constexpr int M = 16, N = 16, K = 16;
    constexpr int loop_time = 10;
    
    datatype *h_a, *h_b, *h_c;
    datatype alpha = 1.0f, beta = 0.0f;
    h_a = new float[M * K];
    h_b = new float[K * N];
    h_c = new float[M * N];
    // check if the kernel give correct result.
    kernels.push_back(run_v1);
    utils::generate_T_matrix<float>(h_a, M, K);
    utils::generate_T_matrix<float>(h_b, K, N);
    ///////////////////////////////////////////////////////////////
    
    Timer t;
    for(int i = 0; i < kernels.size(); i ++)
    {
        std::cout << "Running kernel_v" << i + 1 << ":" << std::endl;
        const auto &kernel = kernels[i];
        t.start();
        for(int i = 0; i < loop_time; i ++)
            kernel(M, N, K, h_a, h_b, h_c);
        t.stop();
        t.report_sgemm_with_loop(M, N, K, alpha, beta, loop_time);
        t.reset();
    }

    ///////////////////////////////////////////////////////////////

    return 0;
}
