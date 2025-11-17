#include "sortscaffold.c"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#define SIZE 10000

typedef int data_t;

static void merge(data_t A[], int mid, int n, data_t T[]);
static void recursive_merge(data_t A[], int n, data_t T[]);
void merge_sort(data_t A[], int n);

int main(int argc, char *argv[]) {
  int n = SIZE;
  if (argc > 1) {
    n = atoi(argv[1]);
  }
  int count = 0, c;
  int arr[n];
  while (count < n) {
    scanf("%d", &c);
    arr[count++] = c;
  }

  printf("Testing merge sort\n");
  merge_sort(arr, n);
  for (int i = 0; i < n; i++) {
    printf("%d ", arr[i]);
  }
}

static void merge(data_t A[], int mid, int n, data_t T[]) {
  int s1 = 0, s2 = mid, i = 0;
  for (int j = 0; j < mid; j++) {
    copy_data(T + j, A + j);
  }

  while (s1 < mid && s2 < n) {
    int outcome = cmp(T + s1, A + s2);
    if (outcome < 0) {
      copy_data(A + i, T + s1);
      s1 = s1 + 1;
    } else {
      copy_data(A + i, A + s2);
      s2 = s2 + 1;
    }
    i = i + 1;
  }
  while (s1 < mid) {
    copy_data(A + i, T + s1);
    s1 = s1 + 1;
    i = i + 1;
  }
}

static void recursive_merge(data_t A[], int n, data_t T[]) {
  if (n <= 1)
    return;

  int mid = n / 2;
  recursive_merge(A, mid, T);
  recursive_merge(A + mid, n - mid, T);
  merge(A, mid, n, T);
}

void merge_sort(data_t A[], int n) {
  data_t *T = malloc((n / 2) * sizeof(data_t));
  assert(T != NULL);
  recursive_merge(A, n, T);
  free(T);
}

// Worst case + average case: O(n log n) with extra memory O(n)

/*
static void merge(data_t A[], int mid, int n, data_t T[]) {
  int s1 = 0, s2 = mid, i = 0;
  for (int j = 0; j < mid; j++) {
    copy_data(T + j, A + j);
  }

  while (s1 < mid && s2 < n) {
    if (cmp(T + s1, A + s2) > 0) {
      copy_data(A + i, A + s2);
      s2 = s2 + 1;
    } else {
      copy_data(A + i, T + s1);
      s1 = s1 + 1;
    }
    i = i + 1;
  }

  while (s1 < mid) {
    copy_data(A + i, T + s1);
    s1 = s1 + 1;
    i = i + 1;
  }
}

static void recursive_merge(data_t A[], int n, data_t T[]) {
  if (n <= 1)
    return;

  int mid = n / 2;
  recursive_merge(A, mid, T);
  recursive_merge(A + mid, n - mid, T);
  merge(A, mid, n, T);
}

void merge_sort(data_t A[], int n) {
  data_t *T = malloc((n / 2) * sizeof(data_t));
  assert(T != NULL);
  recursive_merge(A, n, T);
  free(T);
}
*/
