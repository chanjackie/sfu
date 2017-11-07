#include <stdio.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "intarr.h"

int main() {
  intarr_t* test = intarr_create(5);
  for (int n=0;n<test->len;n++) {
    intarr_push(test, n);
  }
//  intarr_push(test, 1);
  //intarr_push(test, 2);
  //intarr_push(test, 3);
  //intarr_push(test, 4);
  //intarr_push(test, 5);
  //intarr_push(test, 10);
  //intarr_push(test, 162);
  //intarr_push(test, 14);
  //printf("%d\n", intarr_save_binary(test, "testsave"));
  //intarr_save_json(test, "ayy.txt");
  //intarr_t* copy = intarr_load_json("ayy.txt");
  intarr_save_binary(test,"testsave");
  intarr_t* copy = intarr_load_binary("testsave");
  for (int n=0;n<copy->len;n++) {
    printf("%d ", copy->data[n]);
  }
  printf("\n");
  free(test);
  free(copy);
}
