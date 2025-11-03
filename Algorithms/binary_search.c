
#include <stdio.h>

// Define constants for search result status
#define BS_FOUND 1
#define BS_NOT_FOUND -1

// Function prototype for binary search
int binary_search(int A[], int n, int low, int high, int key, int *location);

int main(int argc, char *argv[]) {
  // Sorted array to search in
  int A[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
  int n = sizeof(A) / sizeof(A[0]); // Calculate number of elements
  int location;                     // Variable to store index of found element

  // Search for key 10 in array A
  int res = binary_search(A, n, 0, n - 1, 10, &location);

  // Print result based on search outcome
  if (res == BS_FOUND) {
    printf("Element found at index: %d\n", location);
  } else {
    printf("Element not found\n");
  }

  return 0;
}

// Recursive binary search function
int binary_search(int A[], int n, int low, int high, int key, int *location) {
  // Base case: key not found
  if (low > high) {
    return BS_NOT_FOUND;
  }

  // Calculate middle index
  int mid = (low + high) / 2;

  // If middle element is greater than key, search left half
  if (A[mid] > key) {
    return binary_search(A, n, low, mid - 1, key, location);
  }
  // If middle element is less than key, search right half
  else if (A[mid] < key) {
    return binary_search(A, n, mid + 1, high, key, location);
  }
  // If middle element matches key, store location and return success
  else {
    *location = mid;
    return BS_FOUND;
  }
}
