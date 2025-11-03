#include <stdio.h>
#include <string.h>

#define ALPHABET_SIZE 256

void build_shift_table(char *pattern, int pat_len, int *shift);
int bmh_search(char *text, char *pattern);

int main(int argc, char *argv[]) {
  char text[] = "HERE IS A SAMPLE EXAMPLE";
  char pattern[] = "EXAMPLE";

  int index = bmh_search(text, pattern);

  if (index != -1) {
    printf("Pattern found at index: %d\n", index);
  } else {
    printf("Pattern not found\n");
  }

  return 0;
}

void build_shift_table(char *pattern, int pat_len, int *shift) {
  for (int i = 0; i < ALPHABET_SIZE; i++) {
    shift[i] = pat_len; // Default shift value
  }

  for (int i = 0; i < pat_len - 1; i++) {
    shift[(unsigned char)pattern[i]] = pat_len - i - 1;
  }
}

int bmh_search(char *text, char *pattern) {
  int t_len = strlen(text);
  int p_len = strlen(pattern);
  int shift[ALPHABET_SIZE];

  build_shift_table(pattern, p_len, shift);

  int i = 0;
  while (i <= t_len - p_len) {
    int j = p_len - 1;
    while (j >= 0 && text[i + j] == pattern[j]) {
      j = j - 1;
    }

    if (j <= 0) {
      return i; // Pattern found at index i
    }

    i += shift[(unsigned char)text[i + p_len - 1]];
  }

  return -1; // Pattern not found
}
