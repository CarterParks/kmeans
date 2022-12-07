#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<math.h>
#include<time.h>
#include "kmeans.h"

void main(int argc, char *argv[]){
  double *t = malloc(COLS * ROWS * sizeof *t);
  int fs = table(argv[1], t);

  int *cluster = kmeans(t);

  for (int i = 0; i < ROWS; i++) printf("%d\n", cluster[i]);
}
