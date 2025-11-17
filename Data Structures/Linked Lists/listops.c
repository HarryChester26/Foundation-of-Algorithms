#include "listops.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

list_t *make_empty_list(void) {
  list_t *new = malloc(sizeof(list_t));
  assert(new != NULL);
  new->head = new->foot = NULL;
  return new;
}

int is_empty_list(list_t *list) {
  assert(list != NULL);

  return list->head == NULL;
}

void free_list(list_t *list) {
  assert(list != NULL);
  node_t *curr = list->head;
  node_t *prev = NULL;
  while (curr) {
    prev = curr;
    curr = curr->next;
    free(prev);
  }
  free(list);
}

list_t *insert_at_head(list_t *list, void *value) {
  assert(list != NULL);

  node_t *new = malloc(sizeof(node_t));
  assert(new != NULL);
  new->data = value;
  new->next = list->head;
  list->head = new;
  if (list->foot == NULL) {
    list->foot = new;
  }
  return list;
}

list_t *insert_at_foot(list_t *list, void *value) {
  assert(list != NULL);

  node_t *new = malloc(sizeof(node_t));
  assert(new != NULL);
  new->data = value;
  new->next = NULL;

  if (list->foot == NULL) {
    list->head = list->foot = new;
  } else {
    list->foot->next = new;
    list->foot = new;
  }
  return list;
}

void *get_head(list_t *list) {
  assert(list != NULL && list->head != NULL);

  return list->head->data;
}

list_t *get_tail(list_t *list) {
  assert(list != NULL);
  node_t *oldhead = list->head;
  list->head = list->head->next;

  if (list->head == NULL) {
    list->foot = NULL;
  }
  free(oldhead);
  return list;
}

list_t *delete_node(list_t *list, void *value, int (*cmp)(void *, void *)) {
  assert(list != NULL);

  node_t *prev = NULL, *curr = list->head;
  while (curr && cmp(curr->data, value) != 0) {
    prev = curr;
    curr = curr->next;
  }
  if (prev == NULL) {
    node_t *oldhead = list->head;
    list->head = list->head->next;
    if (list->head == NULL) {
      list->foot = NULL;
    }
    free(oldhead);
    return list;
  }
  prev->next = curr->next;
  free(curr);
  return list;
}

/*
list_t *delete_node(list_t *list, void *value, int (*cmp)(void *, void *)) {
  assert(list != NULL);

  node_t *prev, *curr;
  prev = NULL;
  curr = list->head;
  while (curr && cmp(curr->data, value) != 0) {
    prev = curr;
    curr = curr->next;
  }
  if (curr == NULL)
    return list;

  if (prev == NULL) {
    node_t *oldhead = list->head;
    list->head = list->head->next;
    if (list->head == NULL) {
      list->foot = NULL;
    }
    free(oldhead);
    return list;
  }
  prev->next = curr->next;
  if (curr->next == NULL) {
    list->foot = prev;
  }
  free(curr);
  return list;
}
*/

void reverse_list(list_t *list) {
  assert(list != NULL);
  node_t *prev = NULL, *curr = list->head, *next;
  while (curr) {
    next = curr->next;
    curr->next = prev;
    prev = curr;
    curr = next;
  }
  list->foot = list->head;
  list->head = prev;
}

void print_list(list_t *list, void (*action)(void *)) {
  assert(list != NULL);
  node_t *curr = list->head;
  while (curr) {
    action(curr->data);
    curr = curr->next;
  }
}

list_t *insert_in_order(list_t *list, void *value, int (*cmp)(void *, void *)) {
  assert(list != NULL);

  node_t *new = malloc(sizeof(node_t));
  assert(new != NULL);
  new->data = value;
  new->next = NULL;

  node_t *prev = NULL, *curr = list->head;

  while (curr && cmp(curr->data, new->data) < 0) {
    prev = curr;
    curr = curr->next;
  }
  if (prev == NULL) {
    new->next = list->head;
    list->head = new;
    if (list->foot == NULL) {
      list->foot = new;
    }
    return list;
  }
  prev->next = new;
  new->next = curr;
  if (curr == NULL) {
    list->foot = new;
  }
  return list;
}

/*
list_t *insert_in_order(list_t *list, void *value, int (*cmp)(void *, void *)) {
  assert(list != NULL);
  node_t *prev = NULL, *curr = list->head;
  node_t *new = malloc(sizeof(node_t));
  assert(new != NULL);
  new->data = value;
  new->next = NULL;
  while (curr && cmp(curr->data, new->data) < 0) {
    prev = curr;
    curr = curr->next;
  }
  if (prev == NULL) {
    new->next = list->head;
    list->head = new;
    if (list->foot == NULL) {
      list->foot = new;
    }
    return list;
  }
  prev->next = new;
  new->next = curr;
  if (curr == NULL) {
    list->foot = new;
  }
  return list;
}
*/
