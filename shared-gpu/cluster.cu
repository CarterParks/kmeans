#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <float.h>
#include "kmeans.h"
#include <time.h>

__global__ void assign(int *clus, double *data, double *cent){
  int p = blockIdx.x;
  double min;
  for (int k = 0; k < K; k++){
    double sum = 0;
    for (int i = 0; i < COLS; i++){
      double p1 = data[p * COLS + i];
      double p2 = cent[k * COLS + i];
      sum += pow(p1 - p2, 2);
    }
    double s = sqrt(sum);
    if (s < min || k == 0){
      min = s;
      clus[p] = k;
    }
  }
}

__global__ void centroids(double *data, int *clus, double *cent){
  int k = blockIdx.x;
  int c = threadIdx.x;
  int n = 0;
  for (int p = 0; p < ROWS; p++)
    if (clus[p] == k){
      cent[k * COLS + c] += data[p * COLS + c];
      n++;
    }
  cent[k * COLS + c] /= n;
}

int *kmeans(double *data){
  double *cent;
  cudaMallocManaged(&cent, K * COLS * sizeof (double));

  int *clus;
  cudaMallocManaged(&clus, ROWS * sizeof (int));

  int *clus_p;
  cudaMallocManaged(&clus_p, ROWS * sizeof (int));

  // initialize centroids
  int step = ROWS / K;
  int point = rand() % step;

  for (int i = 0; i < K; i++){
    memcpy(cent + i * COLS, data + point * COLS, COLS * sizeof *data);
    point = (point + step) % ROWS;
  }

  while (1) {
    assign<<<ROWS,1>>>(clus, data, cent);
    cudaDeviceSynchronize();

    if (!memcmp(clus_p, clus, ROWS * sizeof (int))) break;
    cudaMemcpy(clus_p, clus, ROWS * sizeof (int), cudaMemcpyHostToHost);

    // calculate centroids
    centroids<<<K, COLS>>>(data, clus, cent);
    cudaDeviceSynchronize();
  }

  return clus;
}
