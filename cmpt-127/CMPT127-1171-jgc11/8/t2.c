#include <stdio.h>
#include <stdlib.h>
#include "point_array.h"

/* ALL THESE FUNCTIONS REQUIRE A VALID POINT_ARRAY_T POINTER AS THEIR
   FIRST PARAMETER. THEY SHOULD FAIL ON ASSERTION IF THIS POINTER IS
   NULL */

/* TASK 1 */

// Safely initalize an empty array structure.
void point_array_init( point_array_t* pa ) {
  if (pa != NULL) {
    pa->len = 0;
    pa->reserved = 0;
    pa->points = NULL;
  } else {
    puts("pa is NULL");
  }
}

/* TASK 2 */

// Resets the array to be empty, freeing any memory allocated if
// necessary.
void point_array_reset( point_array_t* pa ) {
  if (pa!=NULL) {
    free(pa->points);
    pa->len = 0;
    pa->reserved = 0;
    pa->points = NULL;
  } else {
    puts("pa is NULL");
  }
}

/* TASK 3 */

// Append a point to the end of an array. If successful, return 0,
// else return 1;
int point_array_append( point_array_t* pa, point_t* p ) {
  if (pa!=NULL && pa->reserved == 0) {
    pa->points = (point_t*)realloc(pa->points, sizeof(point_t)*(pa->len+1));
    if (pa->points != NULL) {
      pa->points[pa->len] = *p;
      pa->len++;
      pa->reserved++;
      return 0;
    }
  } else if (pa!=NULL && pa->len < pa->reserved) {
    pa->points[pa->len] = *p;
    pa->len++;
    return 0;
  } else if (pa!=NULL && pa->len == pa->reserved) {
    pa->reserved = pa->reserved*2;
    pa->points = (point_t*)realloc(pa->points, sizeof(point_t)*(pa->reserved));
    pa->points[pa->len] = *p;
    pa->len++;
    return 0;
  }
  puts("error");
  return 1;
}

/* TASK 4 */

// Remove the point at index i from the array, reducing the size of
// the array by one. The order of points in the array may change.
int point_array_remove( point_array_t* pa, unsigned int i ) {
  if (pa && i >= 0 && i < pa->len && pa != NULL) {
    pa->points[i] = pa->points[pa->len-1];
    pa->len--;
    return 0;
  }
  puts("error");
  return 1;
}
