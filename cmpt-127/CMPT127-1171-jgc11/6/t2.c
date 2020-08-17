#include <stdio.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "intarr.h"


/* LAB 6 TASK 2 */

/*
  Save the entire array ia into a file called 'filename' in a JSON
  text file array file format that can be loaded by
  intarr_load_json(). Returns zero on success, or a non-zero error
  code on failure. Arrays of length 0 should produce an output file
  containing an empty array.

  The JSON output should be human-readable.

  Examples:

  The following line is a valid JSON array:
  [ 100, 200, 300 ]

  The following lines are a valid JSON array:
  [
   100,
   200,
   300
  ]
*/
int intarr_save_json( intarr_t* ia, const char* filename ) {
  if (ia!=NULL) {
    FILE* f = fopen(filename, "w");
    if (f==NULL) {
      puts("Failed to open file for saving");
      return 1;
    }
    if (ia->len == 0) {
      fprintf(f, "[ ]");
      return 0;
    }
    fprintf(f, "[ ");
    int i = 0;
    for (int n=0;n<ia->len-1;n++) {
      i += fprintf(f, "%d, ", ia->data[n]);
    }
    i += fprintf(f, "%d ]", ia->data[ia->len-1]);
    fclose(f);
    return 0;
  }
  return 3;
}

/*
  Load a new array from the file called 'filename', that was
  previously saved using intarr_save(). The file may contain an array
  of length 0. Returns a pointer to a newly-allocated intarr_t on
  success (even if that array has length 0), or NULL on failure.
*/
intarr_t* intarr_load_json( const char* filename ) {
  FILE* f = fopen(filename, "r");
  if (f==NULL) {
    puts("Failed to open file for reading");
    return NULL;
  }
  fseek(f, 2, SEEK_SET);
  intarr_t* newarr = intarr_create(0);
  int save[1];
  int test;
  while ((test = fscanf(f, "%d, ", &save[0])) == 1) {
    intarr_push(newarr, save[0]);
  }
  return newarr;
}





//
