#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct song_node {
  char name[100];
  char artist[100];
  struct song_node *next;
};

void print_list(struct song_node * head) {
  if (head == NULL) printf("EMPTY");
  while ( head != NULL) {
    printf("Artist: %s, Song: %s -> ", head->artist, head->name);
    head = head->next;
  }
  printf("\n");
}


struct song_node * insert_front(struct song_node * head, char songname[100], char songartist[100]) {
  struct song_node *new = (struct song_node*)malloc(sizeof(struct song_node));
  strcpy(new->name, songname);
  strcpy(new->artist, songartist);
  new->next = head;
  return new;
} 

struct song_node * insert_order(struct song_node * head, char songname[100], char songartist[100]) {
    
  struct song_node *current = head;
  if (! current) return insert_front(NULL, songname, songartist); //if head is null, insert in front
  if (strcmp(songartist, current->artist) < 0) return insert_front(head, songname, songartist); //if head is greater than value, insert in front
  if (strcmp(songartist, current->artist) == 0)
    if (strcmp(songname, current->name) <= 0)
      return insert_front(head, songname, songartist);
  while (current->next) {
    if (strcmp(current->next->artist, songartist) > 0) {
      current->next = insert_front(current->next, songname, songartist); //if the data has a place between two nodes
      return head;
    }
    else if (strcmp(current->next->artist, songartist) == 0) {
      while (current->next) {
	if (strcmp(current->next->name, songname) > 0) {
	  current->next = insert_front(current->next, songname, songartist); //if the data has a place between two nodes
	  return head;
	}
	current = current->next;
      }
      current->next = insert_front(current->next, songname, songartist);
      return head;
    }
    current = current->next;
  }
    
  current->next = insert_front(current->next, songname, songartist);
  return head;
  // if current doesn't have a next but it hasn't beeen sorted
}
/*
  struct node * free_list(struct node * head) {
  struct node * nxt;
  struct node * frst;
  while ( head != NULL) {
  nxt = head->next;
  free(head);
  head = nxt;
  }
  frst = NULL;
  return frst;
  }
*/

int main() {
  struct song_node * q = insert_front(NULL, "Trouble", "Taylor Swift");
  q = insert_order(q, "Single Lady", "Beyonce");
  q = insert_order(q, "Love Story", "Taylor Swift");
  q = insert_order(q, "Young Forever", "Taylor Swift");
  q = insert_order(q, "All Too Well", "Taylor Swift");
  
  print_list(q);
}
