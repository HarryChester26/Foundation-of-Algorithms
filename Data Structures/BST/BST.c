#include "treeops.h"
#include <assert.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_WORDS 1000

int string_compare(void *, void *);
char *get_word(void);
void print_tree(void *);

int main(int argc, char *argv[]) {
  tree_t *tree = make_empty_tree(string_compare);
  char *one_word;
  while ((one_word = get_word()) != NULL) {
    insert_in_order(tree, one_word);
  }

  traverse_tree(tree, print_tree);

  printf("%d", tree_size(tree));

  return 0;
}

char *get_word(void) {
  char *one_word = (char *)malloc(sizeof(char));
  assert(one_word != NULL);
  int c;
  int n = 0, max_cap = 1;

  while ((c = getchar()) != EOF && !isalpha(c)) {
    /* first character is not alphabetical character */
  }

  if (c == EOF) {
    return NULL;
  }

  one_word[n++] = c;

  while ((c = getchar()) != EOF && isalpha(c)) {
    if (n == max_cap) {
      max_cap *= 2;
      char *new_word = realloc(one_word, max_cap * sizeof(char) + 1);
      assert(new_word != NULL);
    }

    one_word[n++] = c;
  }
  one_word[n] = '\0';

  return one_word;
}

int string_compare(void *a, void *b) {
  char *v1 = (char *)a;
  char *v2 = (char *)b;
  return strcmp(v1, v2);
}

void print_tree(void *node) {
  char *str = (char *)node;
  printf("%s ", str);
}
