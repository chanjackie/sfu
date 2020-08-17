#include <stdio.h>
#include <stdlib.h>
#include "list.h"


 void list_sort( list_t* list ){
     if(list->head == list->tail){
         return;
     }

     int pivot = list->head->val;
     list->head = list->head->next;

     list_t* one = list_create();
     list_t* two = list_create();

     element_t* current = list->head;
     element_t* next;

     for (;current;current=next) {
         next = current->next;
         current->next = NULL;
         if(current->val <= pivot){
             list_append(one, current->val);
         }
         else{
             list_append(two, current->val);
         }
     }

     list->head = NULL;
     list->tail = NULL;

     list_sort(one);
     list_sort(two);

     if(one->head == NULL){

     } else if(list->head == NULL){
         *list = *one;
     } else{
         list->tail->next = first->head;
         list->tail = first->tail;
     }
     free(one);

     list_append(list, pivot);

     if(two->head == NULL){

     }
     else if(list->head == NULL){
         *list = *two;
     }
     else{
         list->tail->next = two->head;
         list->tail = two->tail;
     }
     free(two);
 }
