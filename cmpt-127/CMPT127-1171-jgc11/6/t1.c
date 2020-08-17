#include <stdio.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "intarr.h"

/* -------------------------------------------------------------- */
//
/* LAB 6 TASK 1 */

/*
  Save the entire array ia into a file called 'filename' in a binary
  file format that can be loaded by intarr_load_binary(). Returns
  zero on success, or a non-zero error code on failure. Arrays of
  length 0 should produce an output file containing an empty array.
*/
int intarr_save_binary( intarr_t* ia, const char* filename ) {
  FILE* new = fopen(filename, "w");
  if (ia!=NULL) {
    unsigned int* len = &ia->len;
    if (new == NULL) {
      puts("Failed to open file");
      return 1;
    }
    if (fwrite(len, sizeof(unsigned int), 1, new) != 1) {
      puts("Failed to write array length");
      return 2;
    }
    const size_t wlen = ia->len;
    if (fwrite(ia->data, sizeof(int), wlen, new) != wlen) {
      puts("Failed to write array data");
      return 3;
    }
    fclose(new);
    return 0;
  }
  return 4;
}

/*
  Load a new array from the file called 'filename', that was
  previously saved using intarr_save_binary(). Returns a pointer to a
  newly-allocated intarr_t on success, or NULL on failure.
*/
intarr_t* intarr_load_binary( const char* filename ) {
  unsigned int len[1];
  FILE* f = fopen(filename, "r");
  if (f==NULL) {
    puts("Failed to open array file for reading");
    return NULL;
  }
  if (fread(len, sizeof(unsigned int), 1, f) != 1) {
    puts("Failed to read array length");
    return NULL;
  }
  intarr_t* arr = intarr_create(len[0]);
  assert(arr);
  assert(arr->data);
  if (fread(arr->data, sizeof(int), len[0], f) != *len) {
    puts("Failed to read array data");
    return NULL;
  }
  fclose(f);
  return arr;
}
