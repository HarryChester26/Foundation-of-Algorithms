#include "treeops.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

tree_t *make_empty_tree(int func(void *, void *)) {
  tree_t *tree;
  tree = (tree_t *)malloc(sizeof(*tree));
  assert(tree != NULL);

  tree->root = NULL;
  tree->cmp = func;

  return tree;
}

int is_empty_tree(tree_t *tree) {
  assert(tree != NULL);
  return tree->root == NULL;
}

static void *recursive_search_tree(node_t *, void *, int(void *, void *));

static void *recursive_search_tree(node_t *root, void *key,
                                   int cmp(void *, void *)) {
  int outcome = cmp(key, root->data);
  if (!root) {
    return NULL;
  }
  if ((outcome < 0)) {
    return recursive_search_tree(root->left, key, cmp);
  } else if (outcome > 0) {
    return recursive_search_tree(root->right, key, cmp);
  } else {
    return root->data;
  }
}

/* Returns a pointer to the tree node storing object "key",
   if it exists, otherwise returns a NULL pointer. */

void *search_tree(tree_t *tree, void *key) {
  assert(tree != NULL);
  return recursive_search_tree(tree->root, key, tree->cmp);
}

static node_t *recursive_insert(node_t *, node_t *, int(void *, void *));

static node_t *recursive_insert(node_t *root, node_t *new,
                                int cmp(void *, void *)) {
  if (!root) {
    return new;
  }
  if (cmp(new->data, root->data) < 0) {
    root->left = recursive_insert(root->left, new, cmp);
  } else {
    root->right = recursive_insert(root->right, new, cmp);
  }

  return root;
}

/* Returns a pointer to an altered tree that now includes
   the object "value" in its correct location. */

tree_t *insert_in_order(tree_t *tree, void *value) {
  node_t *new = (node_t *)malloc(sizeof(*new));
  assert(tree != NULL && new != NULL);

  new->data = value;
  new->left = new->right = NULL;

  tree->root = recursive_insert(tree->root, new, tree->cmp);
  return tree;
}

static void recursive_traverse(node_t *, void action(void *));

static void recursive_traverse(node_t *root, void action(void *)) {
  if (root) {
    action(root->data);
    recursive_traverse(root->left, action);
    recursive_traverse(root->right, action);
  }
}

/* Applies the "action" at every node in the tree, in
   the order determined by the cmp function. */

void traverse_tree(tree_t *tree, void action(void *)) {
  assert(tree != NULL);
  recursive_traverse(tree->root, action);
}

static void recursive_free_tree(node_t *);

static void recursive_free_tree(node_t *root) {
  if (root) {
    recursive_free_tree(root->left);
    recursive_free_tree(root->right);
    free(root);
  }
}

/* Release all memory space associated with the tree
   structure. */

void free_tree(tree_t *tree) {
  assert(tree != NULL);
  recursive_free_tree(tree->root);
  free(tree);
}
