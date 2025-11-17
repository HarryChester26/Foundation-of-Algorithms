#include "treeops.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

tree_t *make_empty_tree(int (*func)(void *, void *)) {
  tree_t *new_tree = malloc(sizeof(tree_t));
  assert(new_tree != NULL);

  new_tree->root = NULL;
  new_tree->cmp = func;
  return new_tree;
}

int is_empty_tree(tree_t *tree) {
  assert(tree != NULL);
  return tree->root == NULL;
}

static void *recursive_search(tnode_t *root, void *key,
                              int (*cmp)(void *, void *)) {
  if (root == NULL)
    return NULL;

  int outcome = cmp(root->data, key);
  if (outcome > 0) {
    return recursive_search(root->left, key, cmp);
  } else if (outcome < 0) {
    return recursive_search(root->right, key, cmp);
  } else {
    return root->data;
  }
}

void *search_tree(tree_t *tree, void *key) {
  assert(tree != NULL);
  return recursive_search(tree->root, key, tree->cmp);
}

static tnode_t *recursive_insert(tnode_t *root, tnode_t *new,
                                 int (*cmp)(void *, void *)) {
  if (root == NULL)
    return new;
  int outcome = cmp(root->data, new->data);
  if (outcome > 0) {
    root->left = recursive_insert(root->left, new, cmp);
  } else {
    root->right = recursive_insert(root->right, new, cmp);
  }
  return root;
}

// CHECK
static tnode_t *iterative_insert(tnode_t *root, tnode_t *new,
                                 int (*cmp)(void *, void *)) {
  if (root == NULL)
    return new;

  tnode_t *parent = NULL;
  tnode_t *curr = root;
  while (curr) {
    parent = curr;
    int outcome = cmp(curr->data, new->data);
    if (outcome > 0) {
      curr = curr->left;
    } else {
      curr = curr->right;
    }
  }

  int outcome = cmp(parent->data, new->data);
  if (outcome > 0) {
    parent->left = new;
  } else {
    parent->right = new;
  }
  return root;
}

tree_t *insert_in_order(tree_t *tree, void *value) {
  assert(tree != NULL);
  tnode_t *new = malloc(sizeof(tnode_t));
  assert(new != NULL);
  new->data = value;
  new->left = new->right = NULL;

  tree->root = recursive_insert(tree->root, new, tree->cmp);
  return tree;
}

static void recursive_traverse(tnode_t *root, void (*action)(void *)) {
  if (root) {
    recursive_traverse(root->left, action);
    action(root->data);
    recursive_traverse(root->right, action);
  }
}

void traverse_tree(tree_t *tree, void (*action)(void *)) {
  assert(tree != NULL);
  recursive_traverse(tree->root, action);
}

static void recursive_free(tnode_t *root) {
  if (root) {
    recursive_free(root->left);
    recursive_free(root->right);
    free(root->data);
    free(root);
  }
}

void free_tree(tree_t *tree) {
  assert(tree != NULL);
  recursive_free(tree->root);
}

static int recursive_size(tnode_t *root) {
  if (root == NULL)
    return 0;

  int sum = 1;
  sum += recursive_size(root->left);
  sum += recursive_size(root->right);
  return sum;
}

int tree_size(tree_t *tree) {
  assert(tree != NULL);
  return recursive_size(tree->root);
}

static int recursive_depth(tnode_t *root, int depth) {
  if (root == NULL)
    return 0;
  int total = depth;
  total += recursive_depth(root->left, depth + 1);
  total += recursive_depth(root->right, depth + 1);
  return total;
}

double avg_depth(tree_t *tree) {
  assert(tree != NULL);
  int total_size = tree_size(tree);
  if (total_size == 0)
    return 0;
  int total_depth = recursive_depth(tree->root, 1);
  return (double)total_depth / total_size;
}

static int recursive_check_bst(tnode_t *root, void *min, void *max,
                               int (*cmp)(void *, void *)) {
  if (root == NULL)
    return 1;

  if (!recursive_check_bst(root->left, min, root->data, cmp)) {
    return 0;
  }
  if (!recursive_check_bst(root->right, root->data, max, cmp)) {
    return 0;
  }
  if (min != NULL && cmp(root->data, min) < 0) {
    return 0;
  }
  if (max != NULL && cmp(root->data, max) > 0) {
    return 0;
  }
  return 1;
}

int is_bst(tree_t *tree) {
  assert(tree != NULL);
  return recursive_check_bst(tree->root, NULL, NULL, tree->cmp);
}

// CHECK
static tnode_t *recursive_find_smallest(tnode_t *root) {
  if (root == NULL)
    return NULL;
  while (root->left)
    root = root->left;
  return root;
}

void *get_tree_head(tree_t *tree) {
  assert(tree != NULL);
  tnode_t *smallest = recursive_find_smallest(tree->root);
  if (smallest == NULL)
    return NULL;
  return smallest->data;
}

static tnode_t *recursive_delete_smallest(tnode_t *root) {
  if (root == NULL)
    return NULL;

  tnode_t *prev, *curr;
  prev = NULL;
  curr = root;
  while (curr->left) {
    prev = curr;
    curr = curr->left;
  }
  if (prev == NULL) {
    tnode_t *new_node = curr->right;
    free(curr);
    return new_node;
  }
  prev->left = curr->right;
  free(curr);
  return root;
}

tree_t *get_tree_tail(tree_t *tree) {
  assert(tree != NULL);
  tree->root = recursive_delete_smallest(tree->root);
  return tree;
}

static int recursive_count_leaves(tnode_t *root) {
  if (root == NULL)
    return 0;
  if (root->left == NULL && root->right == NULL)
    return 1;
  return recursive_count_leaves(root->left) +
         recursive_count_leaves(root->right);
}

int count_leaves(tree_t *tree) { return recursive_count_leaves(tree->root); }

static int recursive_count_internal(tnode_t *root) {
  if (root == NULL)
    return 0;
  if (root->left == NULL && root->right == NULL)
    return 0;
  return 1 + recursive_count_internal(root->left) +
         recursive_count_internal(root->right);
}

int count_internal(tree_t *tree) {
  assert(tree != NULL);
  return recursive_count_internal(tree->root);
}

static int recursive_height(tnode_t *root) {
  if (root == NULL)
    return -1;
  int lh = recursive_height(root->left);
  int rh = recursive_height(root->right);
  return 1 + (lh > rh ? lh : rh);
}

int height(tree_t *tree) { return recursive_height(tree->root); }
