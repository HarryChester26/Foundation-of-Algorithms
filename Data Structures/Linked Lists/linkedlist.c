#include "listops.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
  list_t *list = make_empty_list();

  int n;
  printf("Enter 10 integers:\n");
  for (int i = 0; i < 10; i++) {
    scanf("%d", &n);
    insert_at_foot(list, &n);
  }
  print_list(list, print_ints);
  free_list(list);

  list_t *list_alt = make_empty_list();
  printf("Enter the same 10 integers again:\n");
  for (int i = 0; i < 10; i++) {
    scanf("%d", &n);
    insert_in_order(list_alt, &n, compare_node);
  }

  print_list(list_alt, print_ints);

  return 0;
}
