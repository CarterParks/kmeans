#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<math.h>
#include<float.h>
#include"kmeans.h"
#include<omp.h>

double distance(double *p1, double *p2){
  double sum = 0;
  for (int i = 0; i < COLS; i++)
    sum += pow(p1[i] - p2[i], 2);
  return sqrt(sum);
}


int *assign(double *data, double *centroids){
  int *clus = malloc(ROWS * sizeof *clus);

  # pragma omp parallel for
  for (int p = 0; p < ROWS; p++){
    double min = distance(data + p * COLS, centroids + 0 * COLS);
    for (int k = 1; k < K; k++){
      double d = distance(data + p * COLS, centroids + k * COLS);
      if(d < min){
        min = d;
        clus[p] = k;
      }
    }
  }

  return clus;
}


double *centroids(double *data, int *clusters){
  double *cent = malloc(K * COLS * sizeof (double));
  int count[K];
  memset(cent, 0, K * COLS * sizeof *cent);
  memset(count, 0, K * sizeof *count);

  // for (int p = 0; p < ROWS; p++) {
  //   int k = clusters[p];
  //   count[k] += 1;
  //   for (int c = 0; c < COLS; c++)
  //     cent[k * COLS + c] += data[p * COLS + c];
  // }
  
  # pragma omp parallel for
  for (int k = 0; k < K; k++){
    # pragma omp parallel for
    for (int p = 0; p < ROWS; p++){
      if(clusters[p] == k){
        count[k]++;
        # pragma omp parallel for
        for (int c = 0; c < COLS; c++)
            cent[k * COLS + c] += data[p * COLS + c];
      }
    }
  }
    

  # pragma omp parallel for
  for (int k = 0; k < K; k++)
    # pragma omp parallel for
    for (int c = 0; c < COLS; c++)
      cent[k * COLS + c] /= count[k];
  
  return cent;
}


double *initial_centroids(double *data){
  srand(1752);
  int step = ROWS / K;
  int point = rand() % step;

  double *cent = malloc(K * COLS * sizeof *cent);
  for (int i = 0; i < K; i++){
    omp_target_memcpy(cent + i * COLS, data + point * COLS, COLS * sizeof *data, 0,0,0,0);
    point = (point + step) % ROWS;
  }

  return cent;
}

int *kmeans(double *data){
  double *cent = initial_centroids(data);;
  int CLUS_SIZE = ROWS * sizeof (int);
  int *clus = malloc(CLUS_SIZE);
  int *n_clus = malloc(CLUS_SIZE);
  memset(n_clus, 0, CLUS_SIZE);
  
  int n = 0;
  while (1){
    omp_target_memcpy(clus, n_clus, CLUS_SIZE, 0, 0, 0, 0);
    n_clus = assign(data, cent);
    int m = memcmp(clus, n_clus, CLUS_SIZE);
    if (!m) break;
    cent = centroids(data, n_clus);
  }

  return n_clus;
}
