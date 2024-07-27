#include <stdio.h>
#include <iostream>
#include <cuda_runtime.h>

__global__ void cuda_hello(void) { printf("Hello World from GPU!\n"); }

__global__ void add(int n, float *x, float *y) {
  int index = blockIdx.x * blockDim.x + threadIdx.x;
  int stride = blockDim.x * gridDim.x;
  for (int i = index; i < n; i += stride) y[i] = x[i] + y[i];
}

int main() {
  printf("Hello World from CPU!\n");

  int nDevices;
  cudaGetDeviceCount(&nDevices);
  for (int i = 0; i < nDevices; i++) {
    cudaDeviceProp prop;
    cudaGetDeviceProperties(&prop, i);
    printf("Device Number: %d\n", i);
    printf("  Device name: %s\n", prop.name);
    printf("  Number of SM: %d\n", prop.multiProcessorCount);
    printf("  Maximum threads per block: %d\n", prop.maxThreadsPerBlock);
    printf("  Maximum threads per sm: %d\n", prop.maxBlocksPerMultiProcessor);
    printf("  Memory Clock Rate (KHz): %d\n", prop.memoryClockRate);
    printf("  Memory Bus Width (bits): %d\n", prop.memoryBusWidth);
    printf("  Peak Memory Bandwidth (GB/s): %f\n\n", 2.0 * prop.memoryClockRate * (prop.memoryBusWidth / 8) / 1.0e6);
  }

  cuda_hello<<<1, 10>>>();
  cudaDeviceReset();

  // int N = 1 << 20;
  // float *x, *y;

  // // Allocate Unified Memory – accessible from CPU or GPU
  // cudaMallocManaged(&x, N * sizeof(float));
  // cudaMallocManaged(&y, N * sizeof(float));

  // // initialize x and y arrays on the host
  // for (int i = 0; i < N; i++) {
  //   x[i] = 1.0f;
  //   y[i] = 2.0f;
  // }

  // // Run kernel on 1M elements on the GPU
  // int blockSize = 256;
  // int numBlocks = (N + blockSize - 1) / blockSize;
  // add<<<numBlocks, blockSize>>>(N, x, y);

  // // Wait for GPU to finish before accessing on host
  // cudaDeviceSynchronize();

  // // Check for errors (all values should be 3.0f)
  // float maxError = 0.0f;
  // for (int i = 0; i < N; i++) maxError = fmax(maxError, fabs(y[i] - 3.0f));
  // std::cout << "Max error: " << maxError << std::endl;

  // // Free memory
  // cudaFree(x);
  // cudaFree(y);

  return 0;
}
