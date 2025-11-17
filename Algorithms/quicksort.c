#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef int data_t;

int cmp(data_t *d1, data_t *d2);
void swap(data_t *t1, data_t *t2);
data_t choose_pivot(data_t A[], int n);
void partition(data_t A[], int n, data_t pivot, int *first_fe, int *first_fg);
void quick_sort(int A[], int n);

int main(int argc, char *argv[]) {
  int A[10] = {10, 3, 65, 2, 2, 99, 100, 106, 36, 95};
  quick_sort(A, 10);

  for (int i = 0; i < 10; i++) {
    printf("%d ", A[i]);
  }
}

int cmp(data_t *d1, data_t *d2) {
  if (*d1 < *d2)
    return -1;
  else if (*d1 > *d2)
    return 1;
  else
    return 0;
}

void swap(data_t *t1, data_t *t2) {
  int temp = *t1;
  *t1 = *t2;
  *t2 = temp;
}

data_t choose_pivot(data_t A[], int n) { return A[rand() % n]; }

void partition(data_t A[], int n, data_t pivot, int *first_fe,
               int *first_fg) { // O(n)
  int next = 0, fe = 0, fg = n - 1;
  while (next <= fg) {
    int outcome = cmp(A + next, &pivot);
    if (outcome > 0) {
      swap(A + next, A + fg);
      fg = fg - 1;
    } else if (outcome < 0) {
      swap(A + next, A + fe);
      next = next + 1;
      fe = fe + 1;
    } else {
      next = next + 1;
    }
  }
  *first_fe = fe;
  *first_fg = fg;
}

void quick_sort(data_t A[], int n) { // O(log n);
  if (n <= 1)
    return;

  data_t pivot = choose_pivot(A, n);
  int fe, fg;
  partition(A, n, pivot, &fe, &fg);
  quick_sort(A, fe);
  quick_sort(A + fg + 1, n - fg - 1);
}

// O(n log n): average, O(n^2): worst case

/*
int choose_pivot(data_t A[], int n) { return A[rand() % n]; }

void partition(data_t A[], int n, data_t pivot, int *first_fe, int *first_fg) {
  int fe = 0, next = 0, fg = n - 1;
  while (next <= fg) {
    if (cmp(A + next, &pivot) > 0) {
      swap(A + next, A + fg);
      fg = fg - 1;
    } else if (cmp(A + next, &pivot) < 0) {
      swap(A + next, A + fe);
      fe = fe + 1;
      next = next + 1;
    } else {
      next = next + 1;
    }
  }
  *first_fe = fe;
  *first_fg = fg;
}

void quick_sort(data_t A[], int n) {
  if (n <= 1)
    return;

  int pivot = choose_pivot(A, n);
  int fe, fg;
  partition(A, n, pivot, &fe, &fg);
  quick_sort(A, fe);
  quick_sort(A + fg + 1, n - fg - 1);
}
*/
