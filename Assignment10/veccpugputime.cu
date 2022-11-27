#include <stdio.h>
#include <string.h>
#include "math.h"
#include "time.h"
#include <iostream>
#include <fstream>
#include <iomanip>
#include <stdlib.h>

void initWith(float num, float *a, int N)
{
    for (int i = 0; i < N; ++i)
    {
        a[i] = num;
    }
}

_global_ void addVectorsInto(float *result, float *a, float *b, int N)
{
    int start = blockIdx.x * blockDim.x + threadIdx.x;
    int stride = gridDim.x * blockDim.x;

    for (int i = start; i < N; i += stride)
    {
        result[i] = a[i] + b[i];
    }
}
void addVectors(float *result, float *a, float *b, int N)
{
    for (int i = 0; i < N; ++i)
    {
        result[i] = a[i] + b[i];
    }
}

int main()
{
    const int N = 2 << 20;
    size_t size = N * sizeof(float);

    float *ah;
    float *bh;
    float *ch;

    ah = (float *)malloc(size);
    bh = (float *)malloc(size);
    ch = (float *)malloc(size);

    float *a;
    float *b;
    float *c;

    cudaMallocManaged(&a, size);
    cudaMallocManaged(&b, size);
    cudaMallocManaged(&c, size);

    initWith(3, a, N);
    initWith(4, b, N);
    initWith(0, c, N);

    initWith(3, ah, N);
    initWith(4, bh, N);
    initWith(0, ch, N);

    cudaEvent_t start, stop;
    cudaEventCreate(&start);
    cudaEventCreate(&stop);
    cudaEventRecord(start, 0);

    addVectorsInto<<<100, 1024>>>(c, a, b, N);
    // cudaDeviceSynchronize();

    cudaEventRecord(stop, 0);
    cudaEventSynchronize(stop);
    float et;
    cudaEventElapsedTime(&et, start, stop);
    cudaEventDestroy(start);
    cudaEventDestroy(stop);

    clock_t begin = clock();
    addVectors(ch, ah, bh, N);
    clock_t end = clock();
    double time_spent = (double)1000 * (end - begin) / CLOCKS_PER_SEC;

    printf("GPU time= %f ms\n", et);

    printf("CPU time= %lf ms\n", time_spent);

    // checkElementsAre(7, c, N);

    free(ah);
    free(bh);
    free(ch);

    cudaFree(a);
    cudaFree(b);
    cudaFree(c);
}