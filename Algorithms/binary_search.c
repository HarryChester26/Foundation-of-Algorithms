#include <stdio.h>

// Define constants for search result status
#define BS_FOUND 1
#define BS_NOT_FOUND -1

// Function prototype for binary search
int bst_recursive(int A[], int start, int end, int key, int *location);
int bst_iterative(int A[], int n, int key, int *location);

int main(int argc, char *argv[]) {
  // Sorted array to search in
  int A[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
  int n = sizeof(A) / sizeof(A[0]); // Calculate number of elements
  int location;                     // Variable to store index of found element

  // Search for key 10 in array A
  int res = bst_recursive(A, 0, n - 1, 10, &location);

  // Print result based on search outcome
  if (res == BS_FOUND) {
    printf("Element found at index: %d\n", location);
  } else {
    printf("Element not found\n");
  }

  return 0;
}

int bst_iterative(int A[], int n, int key, int *location) {
  int start = 0, end = n - 1;
  while (start <= end) {
    int mid = (start + end) / 2;

    if (A[mid] > key) {
      end = mid - 1;
    } else if (A[mid] < key) {
      start = mid + 1;
    } else {
      *location = mid;
      return BS_FOUND;
    }
  }
  return BS_NOT_FOUND;
}

int bst_recursive(int A[], int start, int end, int key, int *location) {
  if (start > end)
    return BS_NOT_FOUND;

  int mid = (start + end) / 2;

  if (A[mid] > key) {
    return bst_recursive(A, start, mid - 1, key, location);
  } else if (A[mid] < key) {
    return bst_recursive(A, mid + 1, end, key, location);
  } else {
    *location = mid;
    return BS_FOUND;
  }
}
