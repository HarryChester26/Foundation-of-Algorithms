
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

typedef int data_t; // Define a type alias for int

// Function declarations
int cmp(data_t *p1, data_t *p2);
void swap(data_t *p1, data_t *p2);
int choose_pivot(int A[], int n);
void partition(int A[], int n, data_t pivot, data_t *first_qe,
               data_t *first_gt);
void quicksort(int A[], int n);

int main(int argc, char *argv[]) {
  // Sample array to sort
  int arr[] = {0, 5, 3, 8, 6, 2, 7, 4, 1, 9};
  int n = sizeof(arr) / sizeof(arr[0]); // Calculate number of elements

  quicksort(arr, n); // Sort the array using quicksort

  // Print the sorted array
  for (int i = 0; i < n; i++) {
    printf("%d ", arr[i]);
  }

  return 0;
}

// Comparison function: returns negative if *p1 < *p2, positive if *p1 > *p2, 0
// if equal
int cmp(data_t *p1, data_t *p2) { return (*p1 - *p2); }

// Swap function: swaps the values pointed to by p1 and p2
void swap(data_t *p1, data_t *p2) {
  data_t temp = *p1;
  *p1 = *p2;
  *p2 = temp;
}

// Choose pivot function: selects a random element from the array as the pivot
int choose_pivot(int A[], int n) { return A[rand() % n]; }

// Partition function: divides the array into three parts:
// elements less than pivot, equal to pivot, and greater than pivot
void partition(int A[], int n, data_t pivot, data_t *first_qe,
               data_t *first_gt) {
  int next = 0, fe = 0, fg = n, outcome;

  while (next < fg) {
    // Compare current element with pivot
    if ((outcome = cmp(A + next, &pivot)) < 0) {
      // Element is less than pivot: move to front
      swap(A + next, A + fe);
      next++;
      fe++;
    } else if ((outcome = cmp(A + next, &pivot)) > 0) {
      // Element is greater than pivot: move to end
      fg--;
      swap(A + next, A + fg);
    } else {
      // Element is equal to pivot: leave in place
      next++;
    }
  }

  // Ensure partitioning is complete
  assert(next >= fg);
  *first_qe = fe; // Index of first element equal to pivot
  *first_gt = fg; // Index of first element greater than pivot
}

// Quicksort function: recursively sorts the array
void quicksort(int A[], int n) {
  data_t pivot, first_qe, first_gt;

  // Base case: array of size 0 or 1 is already sorted
  if (n <= 1) {
    return;
  }

  // Choose a pivot and partition the array
  pivot = choose_pivot(A, n);
  partition(A, n, pivot, &first_qe, &first_gt);

  // Recursively sort elements less than pivot
  quicksort(A, first_qe);

  // Recursively sort elements greater than pivot
  quicksort(A + first_gt, n - first_gt);
}
