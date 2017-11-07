#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "list.h"
#include "t8.h"

int main( int argc, char* argv[] )
{
  list_t* list = list_create();
  if (list->head != NULL || list->tail != NULL) {
    puts("list head and tail should be NULL when list is empty");
    return 1;
  }
  list_print(list);
  for (int i=0;i<1000;i++) {
    list_append(list, rand()%1000);
  }
  list_print(list);
  list_sort(list);
  list_print(list);

  return 0; // tests pass
}
