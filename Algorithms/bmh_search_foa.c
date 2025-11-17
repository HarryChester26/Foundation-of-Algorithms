#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PATTERN_LENGTH 256
#define PATTERN_NOT_FOUND -1

int *create_shift_table(char *pattern, int p_len);
int bmh_search(char *pattern, char *text, int *shift);

int main(int argc, char *argv[]) {
  char *text = "shellsellshells";
  char *pattern = "lls";
  int p_len = strlen(pattern);

  // Allocate memory for failure array

  // Build failure array
  int *shift = create_shift_table(pattern, p_len);

  // Perform KMP search
  int res = bmh_search(pattern, text, shift);

  printf("Shift table: ");
  for (int i = 0; i < MAX_PATTERN_LENGTH; i++) {
    printf("%d ", shift[i]);
  }
  printf("\n");

  if (res != PATTERN_NOT_FOUND) {
    printf("Pattern found at index: %d\n", res);
  } else {
    printf("Pattern not found\n");
  }

  free(shift); // Clean up
  return 0;
}

// O(m)
int *create_shift_table(char *pattern, int p_len) {
  int *shift = malloc(MAX_PATTERN_LENGTH * sizeof(int));
  assert(shift != 0);
  for (int i = 0; i <= MAX_PATTERN_LENGTH; i++) {
    shift[i] = p_len;
  }
  for (int i = 0; i < p_len - 1; i++) {
    shift[(unsigned char)pattern[i]] = p_len - i - 1;
  }
  return shift;
}

// Average: O(n), worst: O(n * m)
int bmh_search(char *pattern, char *text, int *shift) {
  int p_len = strlen(pattern);
  int t_len = strlen(text);
  int s = 0, i = p_len - 1;
  while (s <= t_len - p_len) {
    if (text[s + i] == pattern[i]) {
      i = i - 1;
      if (i < 0) {
        return s;
      }
    } else {
      s = s + shift[(unsigned char)text[s + p_len - 1]];
      i = p_len - 1;
    }
  }
  return PATTERN_NOT_FOUND;
}

/*
int *create_shift_table(char *pattern, int p_len) {
  int *shift = malloc(MAX_PATTERN_LENGTH * sizeof(int));
  assert(shift != NULL);

  for (int i = 0; i <= MAX_PATTERN_LENGTH; i++) {
    shift[i] = p_len;
  }

  for (int i = 0; i < p_len - 1; i++) {
    shift[(unsigned char)pattern[i]] = p_len - i - 1;
  }
  return shift;
}

int bmh_search(char *pattern, char *text, int *shift) {
  int t_len = strlen(text);
  int p_len = strlen(pattern);
  int s = 0, i = p_len - 1;
  while (s <= t_len - p_len) {
    if (text[s + i] == pattern[i]) {
      i = i - 1;
      if (i < 0)
        return s;
    } else {
      s = s + shift[(unsigned char)text[s + p_len - 1]];
      i = p_len - 1;
    }
  }
  return PATTERN_NOT_FOUND;
}
*/
