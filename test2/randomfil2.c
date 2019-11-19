#include <stdio.h>
#include <stdlib.h>
#include "linkedSongs.h"
#include <time.h>


int compare(struct node * song1, struct node * song2){
  if (strcmp(song1->artist, song2->artist) > 0){return 1;}
  else if (strcmp(song1->artist, song2->artist) < 0) {return -1;}
  else{
    return strcmp(song1->name,song2->name);
  }
}

void printNode(struct node * song){
  printf("%s by %s", song->name, song->artist);
}

struct node * insert_front(struct node *pointer, char *name, char *artist){
  struct node * begin = malloc(sizeof(struct node));
  strcpy(begin -> name, name);
  strcpy(begin -> artist, artist);
  begin -> next = pointer;
  return begin;
}

struct node * insert_order(struct node *pointer, char *name, char *artist){
  if (pointer == NULL) {return insert_front(pointer, name, artist);}

  struct node * prev = pointer;
  struct node * temp = pointer->next;
  struct node * toInsert = malloc(sizeof(struct node));
  strcpy(toInsert->name, name);
  strcpy(toInsert->artist, artist);
  if (compare(toInsert, prev) < 0) {
    toInsert->next = prev;
    return toInsert;
  }
  while(temp != NULL && compare(toInsert, temp) > 0) {
    temp = temp->next;
    prev = prev->next;
  }
  prev->next = toInsert;
  toInsert->next = temp;
  return pointer;
}

void print_list(struct node *pointer) {
  if (pointer == NULL) {
    printf("[]\n");
  }
  else {
    printf("[");
    while(pointer != NULL){
      printf("%s: %s", pointer->artist, pointer->name);
      if (pointer -> next != NULL){
        printf(", ");
      }
      pointer = pointer->next;
    };
    printf("]\n");
  }
}

struct node * find_node(struct node * pointer, char *name, char *artist){
  struct node * temp = pointer;
  struct node * toFind = malloc(sizeof(struct node));
  strcpy(toFind->name, name);
  strcpy(toFind->artist, artist);
  while(temp != NULL && compare(toFind, temp) != 0){
    temp = temp->next;
  }
  return temp;
}

struct node * find_artist(struct node * pointer, char *artist){
  struct node * temp = pointer;
  while(temp != NULL && strcmp(artist, temp->artist) != 0){
    temp = temp->next;
  }
  return temp;
}

struct node * randomNode(struct node *pointer){
  int size = 0;
  int a;
  struct node *temp = pointer;
  while(temp != NULL){
    temp = temp -> next;
    size++;
  }
  srand(time(0));
  a = rand() % size;
  while(a > 0){
    pointer = pointer->next;
    a--;
  }
  return pointer;
}

struct node * remove_node(struct node *front, char *name, char *artist) {
  if (front == NULL) {return front;}

  struct node *previous = front;
  struct node *current = front->next;
  if(strcmp(front->name, name) == 0 && strcmp(front->artist, artist) == 0) {
    free(front);
    front = NULL;
    return current;
  }

  while(current != NULL){
    if(strcmp(current->name, name) == 0 && strcmp(current->artist, artist) == 0) {
      previous->next = current->next;
      free(current);
      current = NULL;
      return front;
    }
    previous = current;
    current = current->next;
  }
  printf("Song not found\n");
  return front;
}

struct node * free_list(struct node *pointer) {
  struct node *slider = pointer;
  while(slider != NULL) {
    printf("freeing node: [%s: %s]\n", pointer->artist, pointer->name);
    slider = slider->next;
    free(slider);
    pointer = slider;
  }
  return pointer;
}
