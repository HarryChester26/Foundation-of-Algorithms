#include <stdio.h>

#include "arrayops.h"

void int_swap(int *p1, int *p2) {
  int temp = *p1;
  *p1 = *p2;
  *p2 = temp;
};

void sort_int_array(int A[], int n) {
  for (int i = 1; i < n; i++) {
    for (int j = i - 1; j >= 0 && A[j] > A[j + 1]; j--) {
      int_swap(A + j, A + j + 1);
    }
  }
}

int read_int_array(int A[], int maxvals) {
  int n = 0, excess = 0, next;

  printf("Enter as many as %d values, ^D to end\n", maxvals);
  while (scanf("%d", &next) == 1) {
    if (n == maxvals) {
      excess += 1;
    } else {
      A[n] = next;
      n += 1;
    }
  }

  printf("%d values read into array", n);
  if (excess) {
    printf(", %d excess values discarded", excess);
  }
  printf("\n");
  return n;
}

/* print the elements of an array on one line
 * (insertionsort.c, Figure 7.4 PPSAA) */
void print_int_array(int A[], int n) {
  for (int i = 0; i < n; i++) {
    printf(" %3d", A[i]);
  }
  printf("\n");
}
