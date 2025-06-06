/**
 * In the naive implementation, the grid has 2 dim, and the block also have two dim
 */
template<
	const uint BM,
	const uint BN, 
	const uint BK
>
__global__ void v3(uint M, uint N, uint K, float *a, float *b, float *c)
{
	int tx = threadIdx.x;
	int x = tx / BN + blockIdx.x * BM;
	int y = tx % BN + blockIdx.y * BN; // in y dim the step is BN, aka blockDim.y.
	
	float tmp = 0.0f;
	__shared__ float as[BM * BK];
	__shared__ float bs[BK * BN];
	
	// thread number is BM * BN
	for(int i = 0; i < K; i ++)
	{

	}

	c[x * N + y] = (tmp);
}

void run_v3(uint M, uint N, uint K, float *a, float *b, float *c)
{
    constexpr int BM = 16, BN = 16, BK = 8;
	dim3 grid_dim = {M / BM, N / BN, 1};
    dim3 block_dim = {BM * BN, 1};

	v3<BM, BN, BK><<<grid_dim, block_dim>>>(M, N, K, a, b, c);
}