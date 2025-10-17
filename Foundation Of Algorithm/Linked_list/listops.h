#include <stdlib.h>
typedef struct node node_t;

typedef int data_t;

struct node {
  void *data;
  node_t *next;
};

typedef struct {
  node_t *head;
  node_t *foot;
  size_t data_size;
  int (*cmp)(const void *, const void *);
} list_t;

list_t *make_empty_list(size_t data_size,
                        int (*cmp)(const void *, const void *));

int is_empty_list(list_t *list);

void free_list(list_t *list);

list_t *insert_at_head(list_t *list, const void *value);

list_t *insert_at_foot(list_t *list, const void *value);

void *get_head(list_t *list);

list_t *get_tail(list_t *list);

list_t *insert_in_order(list_t *list, const void *value);
