/* Exercise 12.08 Median Quickselect
 * Alistair Moffat, October 2013
 * Maria Bulychev, August 2025
 * (c) University of Melbourne */

#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 1000

int quickselect(int A[], int n, int k);
void partition(int A[], int n, int pivot, int *first_fe, int *first_fg);
void int_swap(int *p1, int *p2);

int main(int argc, char *argv[]) {
  int A[MAX_SIZE], n = 0, x;

  printf("Enter as many as 1000 values, ^D to end\n");
  while (n < MAX_SIZE && scanf("%d", &x) == 1) {
    A[n++] = x;
  }

  if (n == 0) {
    printf("No numbers entered.\n");
    return 1;
  }

  double median;
  if (n % 2 == 1) { // even number of entries
    median = quickselect(A, n, n / 2);
  } else { // odd number of entries
    int m1 = quickselect(A, n, n / 2 - 1);
    int m2 = quickselect(A, n, n / 2);
    median = (m1 + m2) / 2.0;
  }

  printf("Median: %.2f\n", median);
  return 0;
}

/* exchange the values of the two variables indicated
 * by the arguments (insertionsort.c, Figure 7.4 PPSAA) */
void int_swap(int *p1, int *p2) {
  int tmp = *p1;
  *p1 = *p2;
  *p2 = tmp;
}

// O(n): average case and O(n^2): worst case

void partition(int A[], int n, int pivot, int *first_fe, int *first_fg) {
  int fe = 0, next = 0, fg = n - 1;
  while (next <= fg) {
    if (A[next] > pivot) {
      int_swap(A + next, A + fg);
      fg = fg - 1;
    } else if (A[next] < pivot) {
      int_swap(A + next, A + fe);
      fe = fe + 1;
      next = next + 1;
    } else {
      next = next + 1;
    }
  }
  *first_fe = fe;
  *first_fg = fg;
}

int quickselect(int A[], int n, int k) {
  if (n == 1)
    return A[0];

  int pivot = A[rand() % n];
  int fe, fg;

  partition(A, n, pivot, &fe, &fg);

  if (k < fe) {
    return quickselect(A, fe, k);
  } else if (k > fg) {
    return quickselect(A + fg + 1, n - fg - 1, k - fg - 1);
  } else {
    return A[k]; // should return pivot ??
  }
}
