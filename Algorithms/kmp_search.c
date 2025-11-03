
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define PATTERN_NOT_FOUND -1

// Function prototypes
void compute_failure_array(char *pattern, int p_len, int *failure);
int kmp_search(char *text, char *pattern, int *failure);

int main(int argc, char *argv[]) {
  char *text = "shellsellshells";
  char *pattern = "slls";
  int p_len = strlen(pattern);

  // Allocate memory for failure array
  int *failure = (int *)malloc(p_len * sizeof(int));
  if (failure == NULL) {
    fprintf(stderr, "Memory allocation failed\n");
    return 1;
  }

  // Build failure array
  compute_failure_array(pattern, p_len, failure);

  // Perform KMP search
  int res = kmp_search(text, pattern, failure);

  if (res != PATTERN_NOT_FOUND) {
    printf("Pattern found at index: %d\n", res);
  } else {
    printf("Pattern not found\n");
  }

  free(failure); // Clean up
  return 0;
}

// Builds the failure array (prefix table)
void compute_failure_array(char *pattern, int p_len, int *failure) {
  int len = 0;    // Length of previous longest prefix suffix
  failure[0] = 0; // First value is always 0

  for (int i = 1; i < p_len; i++) {
    while (len > 0 && pattern[i] != pattern[len]) {
      len = failure[len - 1]; // Fall back in the prefix table
    }
    if (pattern[i] == pattern[len]) {
      len++;
    }
    failure[i] = len;
  }
}

// Performs KMP search using the failure array
int kmp_search(char *text, char *pattern, int *failure) {
  int t_len = strlen(text);
  int p_len = strlen(pattern);
  int i = 0, j = 0;

  while (i < t_len) {
    if (text[i] == pattern[j]) {
      i++;
      j++;
    } else {
      if (j != 0) {
        j = failure[j - 1]; // Use failure array to skip comparisons
      } else {
        i++;
      }
    }

    if (j == p_len) {
      return i - j; // Return starting index of match
    }
  }

  return PATTERN_NOT_FOUND; // No match found
}
