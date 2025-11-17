#include "sortscaffold.c"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#define SIZE 10000

typedef int data_t;

void build_max_heap(data_t A[], int n);
void sift_down(data_t A[], int parent, int n);
void heap_sort(data_t A[], int n);
int insert_heap(data_t A[], int n, data_t value);
data_t extract_maximum(data_t A[], int n);
data_t peek_maximum(data_t A[], int n);

int main(int argc, char *argv[]) {
  int arr[SIZE] = {9, 10, 3, 16, 36, 50, 40, 9, 1, 0};
  int n = 10;

  printf("Testing heap sort\n");
  heap_sort(arr, n);

  for (int i = 0; i < n; i++) {
    printf("%d ", arr[i]);
  }
}

void build_max_heap(data_t A[], int n) { // O(n)
  for (int i = n / 2 - 1; i >= 0; i--) {
    sift_down(A, i, n);
  }
}

void sift_down(data_t A[], int parent, int n) { // O(log n)
  int child = 2 * parent + 1;
  if (child < n) {
    if (child + 1 < n && A[child] < A[child + 1]) {
      child = child + 1;
    }
    if (A[child] > A[parent]) {
      swap_data(A + child, A + parent);
      sift_down(A, child, n);
    }
  }
}

void heap_sort(data_t A[], int n) {
  build_max_heap(A, n);
  for (int i = n - 1; i > 0; i--) { // O(n log n)
    swap_data(A + i, A);
    sift_down(A, 0, i);
  }
}

int insert_heap(data_t A[], int n, data_t value) { // O(log n)
  int i = n;
  A[n++] = value;
  // Shift up
  while (i > 0) {
    int parent = (i - 1) / 2;
    if (A[parent] < A[i]) {
      swap_data(A + parent, A + i);
      i = parent;
    } else {
      break;
    }
  }
  return n;
}

data_t extract_maximum(data_t A[], int n) { // O(log n)
  assert(n > 0);
  data_t res = A[0];
  swap_data(A + n - 1, A);
  sift_down(A, 0, n - 1);
  return res;
}

data_t peek_maximum(data_t A[], int n) { // O(1)
  assert(n > 0);
  return A[0];
}
