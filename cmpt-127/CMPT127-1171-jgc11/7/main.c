#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "list.h"

int main( int argc, char* argv[] )
{
  list_t* list = list_create();
  if (list->head != NULL || list->tail != NULL) {
    puts("list head and tail should be NULL when list is empty");
    return 1;
  }
  list_print(list);

  for( int i=5; i<10; i++ )
    list_append( list, i );
  for( int i=4; i>=0; i-- )
    list_prepend( list, i );
  int counter = 0;
  for (element_t* index = list->head; index->next;index=index->next) {
    if (index->val != counter) {
      printf("value at index %d should be %d\n", counter, counter);
      return 1;
    }
    counter++;
  }

  list_print( list );

  int index = 2;
  element_t* el = list_index( list, index );

  if( el == NULL )
    {
      printf( "index %d not found\n", index );
      return 1; // fail
    }
  int index2 = -2;
  element_t* el2 = list_index(list, index2);
  if (el2!=NULL) {
    puts("el2 should be null");
    return 1;
  }

  printf( "value at index %d is %d\n", index, el->val );
  if (el->val != 2) {
    puts("value at index 2 should be 2");
    return 1;
  }
  int index3 = 15;
  element_t* el3 = list_index(list, index3);
  if (el3 != NULL) {
    puts("el3 should be null");
    return 1;
  }
  element_t* el4 = element_create(10);
  list->tail->next = el4;
  list->tail = el4;
  list_print(list);
  free(el4);
  list_print(list);
  list_t* list2 = list_create();
  list_print(list2);
  list_prepend(list2, 5);
  list_append(list2, 6);
  list_print(list2);
  list_destroy(list2);
  list_t* list3 = list_create();
  if (list3->head != NULL) {
    puts("New list head should be NULL");
    return 1;
  }
  element_t* test3 = list_index(list3, 3);
  if (test3 != NULL) {
    puts("Attempting to find index in empty list should return null");
    return 1;
  }
  /*element_t* test4 = element_create(6);
  if (test4->next != NULL) {
    puts("Next pointer in element_create should be NULL");
    return 1;
  }
  free(test4);*/
  list_prepend(list3, 3);
  if (list3->tail == NULL) {
    puts("Tail should point to prepended value");
    return 1;
  }
  list_append(list3, 4);
  list_append(list3, 5);
  list_print(list3);
  list_destroy(list3);
  element_t* test5 = element_create(4);
  if (test5->next != NULL) {
    puts("Next pointer in element_create should be NULL");
    return 1;
  }
  //

  //list_print(list3);

  return 0; // tests pass
}
