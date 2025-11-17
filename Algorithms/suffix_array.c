#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define PATTERN_NOT_FOUND -1
#define PATTERN_FOUND 0

int suffix_cmp(const void *a, const void *b);
int find_pattern(char *suffix, char *pattern, int m);
int binary_search(char **suffix, char *pattern, int p_len, int start, int end);
char **create_suffix(char *text, int t_len);
void partition(char **suffix, int t_len, char pivot, int depth, int *first_fe,
               int *first_fq);
void tquicksort(char **suffix, int t_len, int depth);

int main(int argc, char *argv[]) {
  char *text = "she#sells#shells!";
  char *pattern = "lls";
  int t_len = strlen(text);
  int p_len = strlen(pattern);

  char **suffix = create_suffix(text, t_len);

  for (int i = 0; i < t_len; i++) {
    printf("%s\n", *(suffix + i));
  }

  if (!binary_search(suffix, pattern, p_len, 0, t_len - 1)) {
    printf("Pattern FOUND");
  } else {
    printf("Pattern NOT FOUND");
  }
}

int suffix_cmp(const void *a, const void *b) {
  return strcmp(*(char **)a, *(char **)b);
}

int find_pattern(char *suffix, char *pattern, int p_len) {
  for (int i = 0; i < p_len; i++) {
    if (suffix[i] == '\0' || suffix[i] < pattern[i])
      return -1;
    else if (suffix[i] > pattern[i])
      return 1;
  }

  return 0;
}

int binary_search(char **suffix, char *pattern, int p_len, int start, int end) {
  if (start > end)
    return PATTERN_NOT_FOUND;

  int mid = (start + end) / 2;

  if (find_pattern(suffix[mid], pattern, p_len) == 0) {
    return PATTERN_FOUND;
  } else if (find_pattern(suffix[mid], pattern, p_len) < 0) {
    return binary_search(suffix, pattern, p_len, mid + 1, end);
  } else {
    return binary_search(suffix, pattern, p_len, start, mid - 1);
  }
}

char **create_suffix(char *text, int t_len) {
  char **suffix = malloc((t_len) * sizeof(char *));
  assert(suffix != NULL);

  for (int i = 0; i < t_len; i++) {
    suffix[i] = text + i;
  }

  tquicksort(suffix, t_len, 0);

  return suffix;
}

void swap(char **a, char **b) {
  char *tmp = *a;
  *a = *b;
  *b = tmp;
}

void partition(char **suffix, int t_len, char pivot, int depth, int *first_fe,
               int *first_fg) {
  int next = 0, fe = 0, fg = t_len - 1;

  while (next <= fg) {
    char current = suffix[next][depth];

    if (current < pivot) {
      swap(&suffix[next], &suffix[fe]);
      next = next + 1;
      fe = fe + 1;
    } else if (current > pivot) {
      swap(&suffix[next], &suffix[fg]);
      fg = fg - 1;
    } else {
      next = next + 1;
    }
  }
  *first_fe = fe;
  *first_fg = fg;
}

void tquicksort(char **suffix, int t_len, int depth) {
  if (t_len <= 1)
    return;

  char pivot = suffix[rand() % t_len][depth];
  int fe, fg;
  partition(suffix, t_len, pivot, depth, &fe, &fg);
  tquicksort(suffix, fe, depth);
  if (pivot != '\0')
    tquicksort(suffix + fe, fg - fe + 1, depth + 1);
  tquicksort(suffix + fg + 1, t_len - fg - 1, depth);
}

/*
void partition(char **suffix, int t_len, char pivot, int depth, int *first_fe,
               int *first_fq) {

  int next = 0, fe = 0, fq = t_len - 1;

  while (next <= fq) {
    char current = suffix[next][depth];

    if (current < pivot) {
      swap(&suffix[next], &suffix[fe]);
      next++;
      fe++;
    } else if (current > pivot) {
      swap(&suffix[next], &suffix[fq]);
      fq--;
    } else {
      next++;
    }
  }

  *first_fe = fe;
  *first_fq = fq;
}

void tquicksort(char **suffix, int t_len, int depth) {
  if (t_len <= 1)
    return;

  // pivot on depth
  char pivot = suffix[rand() % t_len][depth];

  int fe, fq;
  partition(suffix, t_len, pivot, depth, &fe, &fq);

  // left region: characters < pivot
  tquicksort(suffix, fe, depth);

  // equal region: recurse deeper on next character
  if (pivot != '\0')
    tquicksort(suffix + fe, fq - fe + 1, depth + 1);

  // right region: characters > pivot
  tquicksort(suffix + fq + 1, t_len - (fq + 1), depth);
}
*/
