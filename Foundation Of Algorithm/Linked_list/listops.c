#include <assert.h>
#include <stdlib.h>
#include <string.h>

#include "listops.h"

list_t *make_empty_list(size_t data_size,
                        int (*cmp)(const void *, const void *)) {
  list_t *list;
  list = (list_t *)malloc(sizeof(*list));
  // Check that memory allocation worked
  assert(list != NULL);

  list->head = list->foot = NULL;
  list->data_size = data_size;
  list->cmp = cmp;
  return list;
}

int is_empty_list(list_t *list) {
  assert(list != NULL);
  return list->head == NULL;
}

void free_list(list_t *list) {
  node_t *curr, *prev;
  assert(list != NULL);
  curr = list->head;
  while (curr) {
    prev = curr;
    curr = curr->next;
    free(prev);
    free(prev->data);
  }
  free(list);
}

list_t *insert_at_head(list_t *list, const void *value) {
  if (!list || !value) {
    return NULL;
  }
  node_t *new = (node_t *)malloc(sizeof(*new));
  assert(new != NULL);
  new->data = malloc(list->data_size);
  new->next = NULL;
  if (!new->data) {
    free(new);
    return NULL;
  }

  memcpy(new->data, value, list->data_size);
  new->next = list->head;
  list->head = new;
  if (list->foot == NULL) {
    list->foot = new;
  }

  return list;
}

list_t *insert_at_foot(list_t *list, const void *value) {
  if (!list || !value) {
    return NULL;
  }
  node_t *new = (node_t *)malloc(sizeof(*new));
  assert(new != NULL);
  new->data = malloc(list->data_size);
  new->next = NULL;
  if (!new->data) {
    free(new);
    return NULL;
  }

  memcpy(new->data, value, list->data_size);
  if (list->foot == NULL) {
    list->head = list->foot = new;
  } else {
    list->foot->next = new;
    list->foot = new;
  }

  return list;
}

list_t *insert_in_order(list_t *list, const void *value) {
  if (!list || !value) {
    return NULL;
  }
  node_t *new = (node_t *)malloc(sizeof(*new));
  assert(new != NULL);
  new->data = malloc(list->data_size);
  new->next = NULL;
  if (new->data == NULL) {
    free(new);
    return NULL;
  }

  memcpy(new->data, value, list->data_size);

  if (list->head == NULL || list->cmp(&(list->head->data), &value) > 0) {
    new->next = list->head;
    list->head = new;
    if (list->foot == NULL) {
      list->foot = new;
    }
    return list;
  }

  node_t *prev = NULL;
  node_t *cur = list->head;

  while (cur != NULL && list->cmp(&(cur->data), &value) < 0) {
    prev = cur;
    cur = cur->next;
  }

  new->next = cur;
  prev->next = new;

  if (new->next == NULL) {
    list->foot = new;
  }

  return list;
}

void *get_head(list_t *list) {
  assert(list != NULL && list->head != NULL);
  return list->head->data;
}

// Remove the head node from the list and return the modified list
list_t *get_tail(list_t *list) {
  node_t *oldhead;
  assert(list != NULL && list->head != NULL);
  oldhead = list->head;
  list->head = list->head->next;
  if (list->head == NULL) {
    list->foot = NULL;
  }
  free(oldhead);
  return list;
}

int n;
type_t *tptr;
/* determine how big the array needs to be today */
n = ...;
/* and ask for the right amount of space */
tptr = (type_t *)malloc(n * sizeof(*tptr));
assert(tptr);
/* then use tptr[0..n-1] as an array in the usual manner */
/* and give it back when finished */
free(tptr);
tptr = NULL;
