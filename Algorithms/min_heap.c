#include "sortscaffold.c"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#define SIZE 10000

void swap(int *p1, int *p2);
void build_min_heap(int A[], int n);
void sift_down(int A[], int parent, int n);
void heap_sort(int A[], int n);
int insert_heap(int A[], int n, int value);
int extract_minimum(int A[], int n);

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

  printf("Testing heap sort\n");
  heap_sort(arr, n);

  for (int i = 0; i < n; i++) {
    printf("%d ", arr[i]);
  }
}

void build_min_heap(int A[], int n) { // O(n)
  for (int i = n / 2 - 1; i >= 0; i--) {
    sift_down(A, i, n);
  }
}

void sift_down(int A[], int parent, int n) { // O(log n)
  int child = 2 * parent + 1;
  if (child < n) {
    if (child + 1 < n && A[child] > A[child + 1]) {
      child = child + 1;
    }
    if (A[child] < A[parent]) {
      swap_data(A + child, A + parent);
      sift_down(A, child, n);
    }
  }
}

void heap_sort(int A[], int n) { // O(n log n)
  build_min_heap(A, n);
  for (int i = n - 1; i > 0; i--) {
    swap_data(A + i, A);
    sift_down(A, 0, i);
  }
}

int insert_heap(int A[], int n, int value) { // O(log n)
  int i = n;
  A[n++] = value;
  while (i > 0) {
    int parent = (i - 1) / 2;
    int outcome = cmp(A + i, A + parent);
    if (outcome < 0) {
      swap_data(A + i, A + parent);
      i = parent;
    } else {
      break;
    }
  }
  return n;
}

int extract_minimum(int A[], int n) { // O(log n)
  assert(n > 0);
  int res = A[0];
  swap_data(A, A + n - 1);
  sift_down(A, 0, n - 1);
  return res;
}

int peek_minimum(int A[], int n) { // O(1)
  assert(n > 0);
  return A[0];
}
