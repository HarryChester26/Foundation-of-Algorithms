typedef struct node node_t;

struct node {
  void *data;
  node_t *next;
};

typedef struct {
  node_t *head;
  node_t *foot;
} list_t;

list_t *make_empty_list(void);

int is_empty_list(list_t *list);

void free_list(list_t *list);

list_t *insert_at_head(list_t *list, void *value);

list_t *insert_at_foot(list_t *list, void *value);

list_t *delete_foot(list_t *list);

void *get_head(list_t *list);

list_t *get_tail(list_t *list);

list_t *delete_node(list_t *list, void *value, int (*cmp)(void *, void *));

void print_list(list_t *list, void (*action)(void *));

void reverse_list(list_t *list);

void print_ints(void *p);

list_t *insert_in_order(list_t *list, void *value, int (*cmp)(void *, void *));

int compare_node(void *, void *);
