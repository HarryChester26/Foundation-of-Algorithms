/* Recursive exhaustive evaluation of subset sum problem
   using a generate and test approach.
   Alistair Moffat, December 2012, Figure 9.4 PPSAA
*/
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

int subsetsum(int A[], int n, int k);

int main(int argc, char *argv[]) {
  /* simple data for testing */
  int A[] = {34,  38,  39,  43,  55,  66,  67,  84,  85,  91,
             101, 117, 128, 138, 165, 168, 169, 182, 184, 186,
             234, 238, 241, 276, 279, 288, 386, 387, 388, 389,
             413, 444, 487, 513, 534, 535, 616, 722, 786, 787};
  int n = 20, k = 1000;
  if (argc == 3) {
    n = atoi(argv[1]);
    k = atoi(argv[2]);
  }
  printf("n=%d, k=%d, subsetsum = %d\n", n, k, subsetsum(A, n, k));
  return 0;
}

/* PPSAA Figure 9.4: Does a subset of A sum to k? */
int subsetsum(int A[], int n, int k) {
  bool dp[n + 1][k + 1];

  for (int i = 0; i <= n; i++) {
    dp[i][0] = true;
  }

  for (int i = 1; i <= k; i++) {
    dp[0][i] = false;
  }

  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= k; j++) {
      if (A[i - 1] > j) {
        dp[i][j] = dp[i - 1][j];
      } else {
        dp[i][j] = dp[i - 1][j] || dp[i - 1][j - A[i - 1]];
      }
    }
  }

  return dp[n][k];
}
