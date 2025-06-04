/**
 * In the naive implementation, the grid has 2 dim, and the block also have two dim
 */
template<
	const uint BM,
	const uint BN, 
	const uint BK
>
__global__ void v1(uint M, uint N, uint K, float *a, float *b, float *c)
{
	int tx = threadIdx.x, ty = threadIdx.y;
	int x = tx + blockIdx.x * BM;
	int y = ty + blockIdx.y * BN; // in y dim the step is BN, aka blockDim.y.
	
	float tmp = 0.0f;
	for(int i = 0; i < K; i ++)
		tmp += (a[x * K + i]) * (b[i * N + y]);
	c[x * N + y] = (tmp);
}

void run_v1(uint M, uint N, uint K, float *a, float *b, float *c)
{
    constexpr int BM = 16, BN = 16, BK = 8;
	dim3 grid_dim = {M / BM, N / BN, 1};
    dim3 block_dim = {BM, BN, 1};
}