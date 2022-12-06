#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<math.h>

#define COLUMNS 10
#define ROWS 42305
#define MAX_PRECISION 25

int table(char *, float *, int, int, int);

void main(int argc, char *argv[]){
  float *t = malloc(COLUMNS * ROWS * sizeof *t);
  int fs = table(argv[1], t, COLUMNS, ROWS, MAX_PRECISION);

  for (int i = 0; i < COLUMNS*5;i++){
    printf("%f, ", t[i]);
    if ((i + 1) % COLUMNS == 0) printf("\n");
  }
}
