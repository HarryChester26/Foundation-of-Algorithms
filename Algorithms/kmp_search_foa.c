#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define PATTERN_NOT_FOUND -1

int *create_failure_table(char *pattern, int p_len);
int kmp_search(char *pattern, char *text, int *failure);

int main(int argc, char *argv[]) {
  char *text = "shellsellshells";
  char *pattern = "lls";
  int p_len = strlen(pattern);

  // Allocate memory for failure array
  int *failure = (int *)malloc(p_len * sizeof(int));
  if (failure == NULL) {
    fprintf(stderr, "Memory allocation failed\n");
    return 1;
  }

  // Build failure array
  failure = create_failure_table(pattern, p_len);

  // Perform KMP search
  int res = kmp_search(pattern, text, failure);

  printf("Failure table: ");
  for (int i = 0; i < p_len; i++) {
    printf("%d ", failure[i]);
  }
  printf("\n");

  if (res != PATTERN_NOT_FOUND) {
    printf("Pattern found at index: %d\n", res);
  } else {
    printf("Pattern not found\n");
  }

  free(failure); // Clean up
  return 0;
}

// O(m)
int *create_failure_table(char *pattern, int p_len) {
  int *failure = malloc(p_len * sizeof(int));
  assert(failure != NULL);
  if (p_len == 1) {
    failure[0] = -1;
    return failure;
  }
  failure[0] = -1;
  failure[1] = 0;
  int c = 0, i = 2;
  while (i < p_len) {
    if (pattern[c] == pattern[i - 1]) {
      c = c + 1;
      failure[i] = c;
      i = i + 1;
    } else if (c > 0) {
      c = failure[c];
    } else {
      failure[i] = 0;
      i = i + 1;
    }
  }
  return failure;
}

// Average + worst: O(n + m)
int kmp_search(char *pattern, char *text, int *failure) {
  int t_len = strlen(text);
  int p_len = strlen(pattern);
  int s = 0, i = 0;
  while (s <= t_len - p_len) {
    if (text[s + i] == pattern[i]) {
      i = i + 1;
      if (i == p_len) {
        return s;
      }
    } else {
      s = s + i - failure[i];
      i = fmax(failure[i], 0);
    }
  }
  return PATTERN_NOT_FOUND;
}

/*
int *create_failure_table(char *pattern, int p_len) {
  int *failure = malloc(p_len * sizeof(int));
  assert(failure != NULL);
  failure[0] = -1;

  if (p_len == 1) {
    return failure;
  }
  failure[1] = 0;
  int c = 0, i = 2;
  while (i < p_len) {
    if (pattern[c] == pattern[i - 1]) {
      c = c + 1;
      failure[i] = c;
      i = i + 1;
    } else if (c > 0) {
      c = failure[c];
    } else {
      failure[i] = 0;
      i = i + 1;
    }
  }
  return failure;
}

int kmp_search(char *pattern, char *text, int *failure) {
  int t_len = strlen(text);
  int p_len = strlen(pattern);
  int s = 0, i = 0;
  while (s <= t_len - p_len) {
    if (text[s + i] == pattern[i]) {
      i = i + 1;
      if (i == p_len)
        return s;
    } else {
      s = s + i - failure[i];
      i = fmax(failure[i], 0);
    }
  }
  return PATTERN_NOT_FOUND;
}
*/
