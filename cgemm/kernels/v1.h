void v1(uint M, uint N, uint K, float *a, float *b, float *c)
{
    for(int i = 0; i < M; i ++)
    {
        for(int j = 0; j < N; j ++)
        {
            float sum = 0.0f;
            for(int k = 0; k < K; k ++)
            {
                sum += a[i * K + k] * b[k * N + j];
            }

            c[i * N + j] = sum;
        }
    }
}

void run_v1(uint M, uint N, uint K, float *a, float *b, float *c)
{
	v1(M, N, K, a, b, c);
}