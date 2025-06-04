#include <cuda_fp16.h>
/**
 * In the naive implementation, the grid has 2 dim, and the block also have two dim
 */
template<
	const uint BM,
	const uint BN, 
	const uint BK
>
__global__ void v1(uint M, uint N, uint K, half *a, half *b, half *c)
{
	int tx = threadIdx.x, ty = threadIdx.y;
	int x = tx + blockIdx.x * BM;
	int y = ty + blockIdx.y * BN; // in y dim the step is BN, aka blockDim.y.
	
	float tmp = 0.0f; // the half result must be compute to float than tranfer to float using __float2half().
	for(int i = 0; i < K; i ++)
		tmp += __half2float(a[x * K + i]) * __half2float(b[i * N + y]);
	c[x * N + y] = __float2half(tmp);
}
