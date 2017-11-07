/*#include <stdio.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "intarr.h"

int main() {
  intarr_t* test = intarr_create(5);
  test->data[0] = 5;
  printf("%d\n", test->data[0]);
  //intarr_destroy(test);
  printf("%u\n", test->len);
  printf("%d\n", test->data[0]);
  intarr_set(test, 3, 10);
  printf("%d\n", test->data[3]);
  int* i = malloc(sizeof(int));
  intarr_get(test, 3, i);
  printf("%d\n", *i);
  intarr_t* testcopy = intarr_copy(test);
  printf("%d\n", testcopy->data[3]);
  printf("%u\n", testcopy->len);
  intarr_set(test,1,3);
  intarr_set(test,2,6);
  intarr_set(test,4,2);
  for (int i=0;i<test->len;i++) {
    printf("%d ", test->data[i]);
  }
  printf("\n");
  intarr_sort(test);
  for (int i=0;i<test->len;i++) {
    printf("%d ", test->data[i]);
  }
  printf("\n");
  intarr_find(test, 10, i);
  printf("%d\n", *i);
  intarr_push(test, 20);
  intarr_push(test, 15);
  intarr_push(test, 14);
  intarr_push(test, 42);
  intarr_push(test, 17);
  intarr_push(test, 94);
  intarr_push(test, 1);
  intarr_push(test, -4);
  for (int i=0;i<test->len;i++) {
    printf("%d ", test->data[i]);
  }
  printf("\n");
  intarr_sort(test);
  for (int i=0;i<test->len;i++) {
    printf("%d ", test->data[i]);
  }
  printf("\n");
  intarr_pop(test, i);
  printf("%d\n", *i);
  for (int n=0;n<test->len;n++) {
    printf("%d ", test->data[n]);
  }
  printf("\n");
  for (int n=test->len;n>0;n--) {
    intarr_pop(test,i);
    printf("%u ", test->len);
  }
  printf("\n");
  printf("%d\n", test->data[0]);
  intarr_pop(test,i);
  intarr_resize(test, 15);
  for (int n=0;n<15;n++) {
    printf("%d ", test->data[n]);
  }
  printf("\n");
  intarr_t* copy = intarr_copy_subarray(test, 3, 9);
  for (int n=0;n<copy->len;n++) {
    printf("%d ", copy->data[n]);
  }
  printf("\n");
  free(copy);
  free(test);
  free(i);
}*/

#include <stdint.h> // for uint8_t
#include <stdlib.h> // for malloc()
#include <string.h> // for memset()
#include <stdio.h>
#include <math.h>
#include <assert.h>

#include "intarr.h"

void print_intarr(intarr_t* ia)
{
  if (ia != NULL )
  {
    printf("Printing intarr of length %d:\n", ia->len);
    for( unsigned i=0; i<ia->len; i++ )
      printf( "%d ", ia->data[i] );
    puts( "(end)" );
  }
  return;
}

int main( int argc, char* argv[] )
{
  printf("Creating test_ia\n");
  intarr_t* test_ia = intarr_create( 15 );
  if ( test_ia ==  NULL ) {
    printf("test_ia ==  NULL\n");
    return 1;
  }

  printf("Populating test_ia\n");
  // Put data in the array
  for( unsigned i=0; i<test_ia->len; i++ )
    test_ia->data[i] = rand() %20;

  printf("Printing test_ia\n");
  print_intarr( test_ia );

  intarr_resize(test_ia,20);


  return 0;
}
