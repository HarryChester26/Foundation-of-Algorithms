/*
Ex 10.04: Search a Linked List Scaffold
Kacie Beckett May 2025
*/
#include "listops.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#define TRUE 1
#define FALSE 0
int is_list_element(list_t *list, data_t value);

int main(int argc, char *argv[]) {
  list_t *list = make_empty_list();

  insert_at_head(list, 1);
  insert_at_head(list, 2);
  insert_at_head(list, 10);
  insert_at_head(list, 20);
  int num_to_check;

  if (scanf("%d", &num_to_check) != 1) {
    printf("You should input a number to check\n");
    exit(EXIT_FAILURE);
  }

  if (is_list_element(list, num_to_check) == TRUE) {
    printf("%d is in the list.\n", num_to_check);
  } else {
    printf("%d is not in the list.\n", num_to_check);
  }
  free(list);
  return 0;
}

/*
Implement your function here
*/
int is_list_element(list_t *list, data_t value) {
  assert(list != NULL);
  node_t *cur = list->head;
  while (cur) {
    if (cur->data == value) {
      return TRUE;
    }
    cur = cur->next;
  }
  return FALSE;
}
