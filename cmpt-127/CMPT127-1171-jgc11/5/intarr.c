#include <stdio.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "intarr.h"

intarr_t* intarr_create(unsigned int len) {
  intarr_t* newarr = malloc(sizeof(intarr_t));
  newarr->data = malloc(sizeof(int) * len);
  newarr->len = len;
  if (newarr == NULL) {
    return NULL;
  }
  return newarr;
}

void intarr_destroy(intarr_t* ia) {
  if (ia != NULL) {
    if (ia->data != NULL) {
      free(ia->data);
    }
    free(ia);
  }
}

intarr_result_t intarr_set( intarr_t* ia,
			    unsigned int index,
			    int val ) {
            if (index >= ia->len) {
              return INTARR_BADINDEX;
            }
            if (ia!=NULL) {
              ia->data[index] = val;
              return INTARR_OK;
            } else {
              return INTARR_BADARRAY;
            }
          }
intarr_result_t intarr_get( const intarr_t* ia, unsigned int index, int* i ) {
  if (index >= ia->len || i == NULL) {
    return INTARR_BADINDEX;
  } else if(ia!=NULL) {
    *i = ia->data[index];
    return INTARR_OK;
  } else {
    return INTARR_BADARRAY;
  }
}

intarr_t* intarr_copy( const intarr_t* ia ) {
  intarr_t* copy = malloc(sizeof(intarr_t));
  copy->data = malloc(sizeof(int)*ia->len);
  copy->len = ia->len;
  memcpy(copy->data,ia->data,sizeof(int)*ia->len);
  if (copy == NULL || ia == NULL) {
    return NULL;
  }
  return copy;
}

intarr_result_t intarr_sort( intarr_t* ia ) {
  if (ia!=NULL) {
    for (int i=0;i<ia->len;i++) {
      int min = ia->data[i];
      int minindex = i;
      for (int n=i;n<ia->len;n++) {
        if (ia->data[n]<min) {
          min = ia->data[n];
          minindex = n;
        }
      }
      int temp = ia->data[i];
      ia->data[i] = ia->data[minindex];
      ia->data[minindex] = temp;
    }
    return INTARR_OK;
  }
  return INTARR_BADARRAY;
}
/* LAB 5 TASK 5 */

// Find the first occurance of the target in the array, searching from
// index 0. If the target is found and i is non-null, set *i to the
// location index and return INTARR_OK. If target does not occur in
// the array, leave *i unmodified and return INTARR_NOTFOUND. If ia is
// null, return INTARR_BADARRAY.
intarr_result_t intarr_find( intarr_t* ia, int target, int* i ) {
  if (ia!=NULL) {
    for (int n=0;n<ia->len;n++) {
      if (ia->data[n] == target) {
        *i = n;
        return INTARR_OK;
      }
    }
    return INTARR_NOTFOUND;
  }
  return INTARR_BADARRAY;
}

/* LAB 5 TASK 6 */

// Append val to the end of ia (allocating space for it). If
// successful, return INTARR_OK, otherwise return
// INTARR_BADALLOC. If ia is null, return INTARR_BADARRAY.
intarr_result_t intarr_push( intarr_t* ia, int val ) {
  if (ia!=NULL) {
    int* copy = malloc(sizeof(int)*(ia->len+1));
    memcpy(copy,ia->data,sizeof(int)*(ia->len+1));
    copy[ia->len] = val;
    ia->data = malloc(sizeof(int)*(ia->len+1));
    memcpy(ia->data,copy,sizeof(int)*(ia->len+1));
    if (ia->data[ia->len] == val) {
      ia->len++;
      return INTARR_OK;
    } else {
      return INTARR_BADALLOC;
    }
  }
  return INTARR_BADARRAY;
}

// If the array is not empty, remove the value with the highest index
// from the array, and, if i is non-null, set *i to the removed value,
// then return INTARR_OK. If the array is empty, leave *i unmodified
// and return INTARR_BADINDEX. If ia is null, return INTARR_BADARRAY.
intarr_result_t intarr_pop( intarr_t* ia, int* i ) {
  if (ia!=NULL) {
    if (ia->len!=0) {
      int* copy = malloc(sizeof(int)*(ia->len-1));
      memcpy(copy,ia->data,sizeof(int)*(ia->len-1));
      if (i!=NULL) {
        *i = ia->data[ia->len-1];
        free(ia->data);
        ia->data = malloc(sizeof(int)*(ia->len-1));
        memcpy(ia->data,copy,sizeof(int)*(ia->len-1));
        ia->len--;
        return INTARR_OK;
      }
    }
    return INTARR_BADINDEX;
  }
  return INTARR_BADARRAY;
}

/* LAB 5 TASK 7 */

// Resize ia to contain newlen values. If newlen is less than the
// original array length, the end of the array is discarded. If newlen
// is greater than the original array length, intialize all the new
// integers to zero. If the allocation is successful, return
// INTARR_OK, otherwise return INTARR_BADALLOC. If ia is null, return
// INTARR_BADARRAY.
intarr_result_t intarr_resize( intarr_t* ia, unsigned int newlen ) {
  if (ia != NULL) {
    int* copy = malloc(sizeof(int)*newlen);
    for (int n=0;n<newlen;n++) {
      copy[n] = ia->data[n];
    }
    free(ia->data);
    ia->data = malloc(sizeof(int)*newlen);
    int extra = newlen-ia->len;
    for (int n=0;n<newlen;n++) {
      ia->data[n] = copy[n];
    }
    if (extra > 0) {
      for (int n=ia->len;n<newlen;n++) {
        ia->data[n] = 0;
      }
    }
    ia->len = newlen;
    if (ia->data!=NULL) {
      for(int w = 0;w<ia->len;w++) {
        printf("%d\n",ia->data[w]);
      }
    printf("%d %d\n", ia->data[50], ia->len);

      return INTARR_OK;
    }
    return INTARR_BADALLOC;
  }
  return INTARR_BADARRAY;
}

/* LAB 5 TASK 8 */

// Get a deep copy of a portion of ia from index first to index last
// inclusive. If successful, return a pointer to a newly-allocated
// intarr_t containing a copy of the specfied section. If an error
// occurs, i.e. ia is null, first or last are out of bounds, last <
// first, or memory allocation fails, return a null pointer.
intarr_t* intarr_copy_subarray( intarr_t* ia, unsigned int first, unsigned int last ) {
  if (ia!=NULL) {
    if (first < ia->len && last >= first && last < ia->len && first >= 0 && last >= 0) {
      unsigned int newlen = (last+1) - first;
      intarr_t* copy = intarr_create(newlen);
      int i=0;
      for (int n=first;n<last+1;n++) {
        copy->data[i] = ia->data[n];
        i++;
      }
      if (copy != NULL) {
        return copy;
      }
    }
    return NULL;
  }
  return NULL;
}


/* -------------------------------------------------------------- */

/* LAB 6 TASK 1 */

/*
  Save the entire array ia into a file called 'filename' in a binary
  file format that can be loaded by intarr_load_binary(). Returns
  zero on success, or a non-zero error code on failure. Arrays of
  length 0 should produce an output file containing an empty array.
*/
int intarr_save_binary( intarr_t* ia, const char* filename );

/*
  Load a new array from the file called 'filename', that was
  previously saved using intarr_save_binary(). Returns a pointer to a
  newly-allocated intarr_t on success, or NULL on failure.
*/
intarr_t* intarr_load_binary( const char* filename );


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
int intarr_save_json( intarr_t* ia, const char* filename );

/*
  Load a new array from the file called 'filename', that was
  previously saved using intarr_save(). The file may contain an array
  of length 0. Returns a pointer to a newly-allocated intarr_t on
  success (even if that array has length 0), or NULL on failure.
*/
intarr_t* intarr_load_json( const char* filename );





//
