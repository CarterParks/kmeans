#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<math.h>
#include<float.h>
#include"kmeans.h"
#include <time.h>

// distance between 2 points in COLS dimensions
double distance(double *p1, double *p2){
  double sum = 0;
  for (int i = 0; i < COLS; i++)
    sum += pow(p1[i] - p2[i], 2);
  return sqrt(sum);
}


int *assign(double *data, double *centroids){
  int *clus = malloc(ROWS * sizeof *clus);

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

  for (int p = 0; p < ROWS; p++) {
    int k = clusters[p];
    count[k] += 1;
    for (int c = 0; c < COLS; c++)
      cent[k * COLS + c] += data[p * COLS + c];
  }

  for (int k = 0; k < K; k++)
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
    memcpy(cent + i * COLS, data + point * COLS, COLS * sizeof *data);
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
  
  for (int i =0; i < K;i++){
    for(int j = 0; j < COLS; j++)
      fprintf(stderr, "%f, ", cent[i*COLS + j]);
    fprintf(stderr, "\n");
  }
  
  int n = 0;
  while (1){
    memcpy(clus, n_clus, CLUS_SIZE);
    n_clus = assign(data, cent);
    if (!memcmp(clus, n_clus, CLUS_SIZE)) break;
    fprintf(stderr, "iteration %d\r", n++);
    cent = centroids(data, n_clus);
  }

  fprintf(stderr, "iteration %d\n", n);
  
  return n_clus;
}
