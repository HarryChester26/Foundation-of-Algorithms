#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 1000
typedef int data_t;

data_t find_kth_largest(data_t A[], int n, int k);

int main(void) {
  data_t A[MAX_SIZE];
  int n = 0;
  int k = -1;
  int temp;
  char c;

  printf("Enter as many as 1000 values, followed by a comma and k:\n");

  while (n < MAX_SIZE) {
    if (scanf("%d", &temp) == 1) {
      A[n++] = temp;
    } else {
      // Not an integer —> check if it's a comma
      if ((c = getchar()) == ',') {
        if (scanf("%d", &k) != 1) {
          printf("Invalid value for k.\n");
          return 1;
        }
        break;
      } else if (c == EOF) {
        break;
      }
    }
  }

  if (n == 0) {
    printf("No numbers entered.\n");
    return 1;
  }

  if (k < 1 || k > n) {
    printf("Invalid value for k.\n");
    return 1;
  }

  int result = find_kth_largest(A, n, k);
  printf("k-th largest element: %d\n", result);
  return 0;
}

/* find the k-th largest element using ... */
void int_swap(int *p1, int *p2) {
  int tmp = *p1;
  *p1 = *p2;
  *p2 = tmp;
}

static int partition(data_t A[], int left, int right) {
  int pivot = A[right];
  int i = left;
  for (int j = left; j < right; j++) {
    if (A[j] > pivot) {
      int_swap(A + j, A + i);
      i = i + 1;
    }
  }
  int_swap(A + i, A + right);
  return i;
}

int quickselect(int A[], int left, int right, int k) {
  if (left == right) {
    return A[left];
  }

  int pivot_index = partition(A, left, right);

  if (pivot_index == k - 1) {
    return A[k - 1];
  } else if (pivot_index > k - 1) {
    return quickselect(A, left, pivot_index - 1, k);
  } else {
    return quickselect(A, pivot_index + 1, right, k);
  }
}

data_t find_kth_largest(data_t A[], int n, int k) {
  return quickselect(A, 0, n - 1, k);
}

/* your code here */
