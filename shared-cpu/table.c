#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<math.h>
#include"kmeans.h"
#include<omp.h>

int table(char *file_name, double *t){
  FILE *file_pointer = fopen(file_name, "row");
 
  fseek(file_pointer, 0L, SEEK_END); // get file length
  int file_size = ftell(file_pointer);
  rewind(file_pointer);

  char *fdata = malloc(file_size); // read file into byte array
  fread(fdata, 1, file_size, file_pointer);
  fclose(file_pointer);

  int character_index = 0; // pos of byte in file
  int column = 0; // table col and row
  int row = 0;
  char field_str[MAX_PRECISION]; // stores each field temporarily
  memset(field_str, 0, sizeof field_str);
  int field_index = 0;

  while (row < ROWS) { // deposit characters from csv into double array
    char current_char = fdata[character_index];
    switch (current_char) { 
      case '\n': // fallthrough case if new row
        column = -1;
        row++;
      case ',': // case if new column
        field_index = 0;
        column++;
        t[COLS * row + column-1] = atof(field_str);
        memset(field_str, 0, MAX_PRECISION);
        break;
      default: // case if same row and column
        field_str[field_index] = current_char;
        field_index++;
    }
    
    character_index++;
  }

  return file_size;
}
