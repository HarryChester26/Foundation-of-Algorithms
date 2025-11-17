typedef struct tnode tnode_t;

struct tnode {
  void *data;     /* ptr to stored structure */
  tnode_t *left;  /* left subtree of node */
  tnode_t *right; /* right subtree of node */
};

typedef struct {
  tnode_t *root;              /* root node of the tree */
  int (*cmp)(void *, void *); /* function pointer */
} tree_t;

/* prototypes for the functions in this library */
tree_t *make_empty_tree(int func(void *, void *));
int is_empty_tree(tree_t *tree);
void *search_tree(tree_t *tree, void *key);
tree_t *insert_in_order(tree_t *tree, void *value);
void traverse_tree(tree_t *tree, void action(void *));
void free_tree(tree_t *tree);
int tree_size(tree_t *tree);
double avg_depth(tree_t *tree);
int is_bst(tree_t *tree);
void tree_sort(void *arr[], int n);
void *get_tree_head(tree_t *tree);
tree_t *get_tree_tail(tree_t *tree);
int count_leaves(tree_t *tree);
int count_internal(tree_t *tree);
int height(tree_t *tree);
