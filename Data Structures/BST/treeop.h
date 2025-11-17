typedef struct node tree_t;

typedef int data_t;

struct node {
  data_t data;
  tree_t *left;
  tree_t *right;
};

data_t *search_tree(tree_t *tree, data_t *key);
tree_t *insert_in_order(tree_t *tree, data_t *value);
void traverse_tree(tree_t *tree, void action(void *));
void free_tree(tree_t *tree);
int tree_size(tree_t *tree);
double avg_depth(tree_t *tree);
int is_bst(tree_t *tree);
void *get_min(tree_t *tree);
tree_t *remove_min(tree_t *tree);
int count_leaves(tree_t *tree);
int count_internal(tree_t *tree);
int height(tree_t *tree);
int count_range(tree_t *tree, data_t L, data_t R);
int count_at_depth(tree_t *tree, int k);
int count_greater(tree_t *tree, data_t x);
