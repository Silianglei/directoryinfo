#include <stdio.h>
#include <stdlib.h>
#include "headers.h"

void print_list(struct node *pointer) {
  if (pointer == NULL) {
    printf("[]\n");
  }
  else {
    printf("[");
    while(pointer != NULL){
      printf("%d", pointer->i);
      if (pointer -> next != NULL){
        printf(", ");
      }
      pointer = pointer->next;
    };
    printf("]");
  }
}

struct node * insert_front(struct node *pointer, int number){
  struct node *begin = malloc(sizeof(struct node));
  begin -> i = number;
  begin -> next = pointer;
  return begin;
}

struct node * free_list(struct node *pointer) {
  struct node *slider = pointer;
  while(slider != NULL) {
    printf("\nfreeing node: %d", pointer -> i);
    slider = slider->next;
    free(slider);
    pointer = slider;
  }
  return pointer;
}

struct node * remove_node(struct node *front, int data){
  if(front == NULL) return front;
  struct node * slider = front;
  struct node * slider_before = NULL;
  while(slider != NULL){
    if(slider->i == data){
      struct node * temp = slider;
      if(slider_before == NULL) front = front -> next;
      else slider_before->next = temp->next;
      free(temp);
      temp = NULL;
    }
    slider_before = slider;
    slider = slider -> next;
  }
  return front;
}
