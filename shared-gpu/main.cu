#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<math.h>
#include "kmeans.h"

int main(int argc, char *argv[]){
  double *data;
  cudaMallocManaged(&data, COLS * ROWS * sizeof *data);
  int fs = table(argv[1], data);
  int *cluster = kmeans(data);
  for (int i = 0; i < ROWS; i++) printf("%d\n", cluster[i]);
  return 0;
}
