#include "treeop.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

int cmp(data_t *d1, data_t *d2) {
  if (*d1 < *d2)
    return -1;
  else if (*d1 > *d2)
    return 1;
  else
    return 0;
}

data_t *search_tree(tree_t *tree, data_t *key) {
  if (tree == NULL)
    return NULL;

  int outcome = cmp(&tree->data, key);
  if (outcome > 0) {
    return search_tree(tree->left, key);
  } else if (outcome < 0) {
    return search_tree(tree->right, key);
  } else {
    return &tree->data;
  }
}

static tree_t *recursive_insert(tree_t *tree, tree_t *new) {
  if (tree == NULL)
    return new;

  int outcome = cmp(&tree->data, &new->data);
  if (outcome > 0) {
    tree->left = recursive_insert(tree->left, new);
  } else {
    tree->right = recursive_insert(tree->right, new);
  }
  return tree;
}

static tree_t *iterative_insert(tree_t *tree, tree_t *new) {
  if (tree == NULL)
    return new;

  tree_t *parent = NULL;
  tree_t *curr = tree;
  while (curr) {
    parent = curr;
    int outcome = cmp(&curr->data, &new->data);
    if (outcome > 0) {
      curr = curr->left;
    } else {
      curr = curr->right;
    }
  }
  int outcome = cmp(&parent->data, &new->data);
  if (outcome > 0) {
    parent->left = new;
  } else {
    parent->right = new;
  }
  return tree;
}

tree_t *insert_in_order(tree_t *tree, data_t *value) {
  tree_t *new = malloc(sizeof(tree_t));
  new->data = *value;
  new->left = new->right = NULL;

  tree = recursive_insert(tree, new);
  return tree;
}

void traverse_tree(tree_t *tree, void (*action)(void *)) {
  if (tree) {
    traverse_tree(tree->left, action);
    action(&tree->data);
    traverse_tree(tree->right, action);
  }
}

void free_tree(tree_t *tree) {
  if (tree) {
    free_tree(tree->left);
    free_tree(tree->right);
    free(tree);
  }
}

int tree_size(tree_t *tree) {
  if (tree == NULL)
    return 0;
  int sum = 1;
  sum += tree_size(tree->left);
  sum += tree_size(tree->right);
  return sum;
}

static int recursive_depth(tree_t *tree, int depth) {
  if (tree == NULL)
    return 0;
  int total = depth;
  total += recursive_depth(tree->left, depth + 1);
  total += recursive_depth(tree->right, depth + 1);
  return total;
}

double avg_depth(tree_t *tree) {
  int total_size = tree_size(tree);
  if (total_size == 0)
    return 0;
  int total_depth = recursive_depth(tree, 1);
  return (double)total_depth / total_size;
}

static int recursive_check_bst(tree_t *tree, data_t *min, data_t *max) {
  if (tree == NULL)
    return 1;

  if (min != NULL && cmp(&tree->data, min) < 0)
    return 0;
  if (max != NULL && cmp(&tree->data, max) > 0)
    return 0;
  return recursive_check_bst(tree->left, min, &tree->data) &&
         recursive_check_bst(tree->right, &tree->data, max);
}

int is_bst(tree_t *tree) { return recursive_check_bst(tree, NULL, NULL); }

void *get_min(tree_t *tree) {
  if (tree == NULL)
    return NULL;
  while (tree->left)
    tree = tree->left;
  return &tree->data;
}

tree_t *remove_min(tree_t *tree) {
  if (tree == NULL)
    return NULL;

  tree_t *parent = NULL;
  tree_t *curr = tree;
  while (curr->left) {
    parent = curr;
    curr = curr->left;
  }
  if (parent == NULL) {
    tree_t *new_root = tree->right;
    free(curr);
    return new_root;
  }
  parent->left = curr->right;
  free(curr);
  return tree;
}

int count_leaves(tree_t *tree) {
  if (tree == NULL)
    return 0;
  if (tree->left == NULL && tree->right == NULL)
    return 1;
  return count_leaves(tree->left) + count_leaves(tree->right);
}

int count_internal(tree_t *tree) {
  if (tree == NULL) {
    return 0;
  }
  if (tree->left == NULL && tree->right == NULL)
    return 0;
  return 1 + count_internal(tree->left) + count_internal(tree->right);
}

int height(tree_t *tree) {
  if (tree == NULL)
    return -1;
  int lh = height(tree->left);
  int rh = height(tree->right);
  return 1 + (lh > rh ? lh : rh);
}

int count_range(tree_t *tree, data_t L, data_t R) {
  if (tree == NULL)
    return 0;
  if (cmp(&tree->data, &L) < 0)
    return count_range(tree->right, L, R);
  if (cmp(&tree->data, &R) > 0)
    return count_range(tree->left, L, R);
  return 1 + count_range(tree->left, L, R) + count_range(tree->right, L, R);
}

int count_at_depth(tree_t *tree, int k) {
  if (tree == NULL)
    return 0;
  if (k == 0)
    return 1;
  return count_at_depth(tree->left, k - 1) + count_at_depth(tree->right, k - 1);
}

int count_greater(tree_t *tree, data_t x) {
  if (tree == NULL)
    return 0;
  if (cmp(&tree->data, &x) <= 0)
    return count_greater(tree->right, x);
  return 1 + count_greater(tree->left, x) + count_greater(tree->right, x);
}
