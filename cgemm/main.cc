#include <iostream>
#include <functional>
#include <common.cuh>
#include "v1.h"
#include "v2.h"

using datatype = float;

// todo
std::vector<std::function<void(uint, uint, uint, float*, float*, float*)> functions;

int main()
{
    constexpr int M = 1024, N = 16, K = 1024;
    constexpr int loop_time = 1;
    
    datatype *h_a, *h_b, *h_c;
    datatype alpha = 1.0f, beta = 0.0f;

    // check if the kernel give correct result.

    ///////////////////////////////////////////////////////////////
    Timer t;
    t.start();
    // for(int i = 0; i < loop_time; i ++)
        run_v1(M, N, K, h_a, h_b, h_c);
    t.stop();
    t.report_sgemm_with_loop(M, N, K, alpha, beta, loop_time);
    t.reset();

    t.start();
    // for(int i = 0; i < loop_time; i ++)
        run_v2(M, N, K, h_a, h_b, h_c);
    t.stop();
    t.report_sgemm_with_loop(M, N, K, alpha, beta, loop_time);
    t.reset();

    
    ///////////////////////////////////////////////////////////////

    return 0;
}
