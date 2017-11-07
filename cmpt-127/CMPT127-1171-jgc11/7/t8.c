#include <stdio.h>
#include <stdlib.h>
#include "list.h"

list_t* merge(list_t* list1, list_t* list2, int len) {
  if (list1 && list2) {
    list_t* new = list_create();
    element_t* el1 = list1->head;
    element_t* el2 = list2->head;
    if (el1 && el2 && new) {
      for (int i=0;i<len;i++) {
        if (el1->val < el2->val) {
          if (new->head == NULL) {
            new->head = el1;
            new->tail = el1;
            el1 = el1->next;
          } else {
            new->tail->next = el1;
            new->tail = el1;
            el1 = el1->next;
          }
        } else {
          if (new->head == NULL) {
            new->head = el2;
            new->tail = el2;
            el2=el2->next;
          } else {
            new->tail->next = el2;
            new->tail = el2;
            el2=el2->next;
          }
        }
        if (el1 == NULL || el2 == NULL) {
          break;
        }
      }
      if (el1 == NULL) {
        for (;el2;el2=el2->next) {
          new->tail->next = el2;
          new->tail = el2;
        }
      }
      if (el2 == NULL) {
        for (;el1;el1=el1->next) {
          new->tail->next = el1;
          new->tail = el1;
        }
      }
      return new;
    }
  }
  return NULL;
}

void list_sort(list_t* list) {
  if (list && list->head && list->tail) {
    int len=0;
    for (element_t* count=list->head;count;count=count->next) {
      len++;
    }
    //printf("%d\n", len);
    if (len == 1) {
      return;
    }
    list_t* one = list_create();
    list_t* two = list_create();
    element_t* first = list->head;
    element_t* last = list->tail;
    element_t* mid = list->head;
    for (int i=0;i<len/2-1;i++) {
      mid = mid->next;
    }
    one->head = first;
    one->tail = mid;
    two->head = mid->next;
    two->tail = last;
    one->tail->next = NULL;
    two->tail->next = NULL;
    list_sort(one);
    list_sort(two);
    list_t* complete = merge(one,two, len);
    free(one);
    free(two);
    if (complete) {
      list->head = complete->head;
      list->tail = complete->tail;
      free(complete);
    }
  }
}
