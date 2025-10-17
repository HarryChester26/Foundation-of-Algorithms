#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *string_dupe(char *s);
char **string_set_dupe(
    char **S); //** denotes pointer to pointers (an array of pointers)
void string_set_free(char **S);

int main(int argc, char *argv[]) {
  char **copy = string_set_dupe(argv);
  if (copy == NULL) {
    fprintf(stderr, "Memory allocation failed\n");
    return 1;
  }

  printf("string is:\n");
  printf("%7s\n", argv[1]);
  char *str_copy = string_dupe(argv[1]);

  printf("duplicate is:\n");
  printf("%7s\n", str_copy);

  printf("string set is (1 per line):\n");
  for (int i = 1; copy[i] != NULL; i++) {
    printf("%7s\n", copy[i]);
  }
  printf("\n");

  printf("duplicated string set is:\n");
  for (int i = 1; copy[i] != NULL; i++) {
    printf("%7s\n", copy[i]);
  }

  string_set_free(copy);

  return 0;
}

char *string_dupe(char *s) {
  if (s == NULL)
    return NULL;

  size_t length = strlen(s) + 1;
  char *copy = (char *)malloc(length * sizeof(char));

  if (copy == NULL) {
    return NULL;
  }

  strcpy(copy, s);

  return copy;
}

char **string_set_dupe(char **S) {
  if (S == NULL)
    return NULL;

  int count = 0;
  while (S[count] != NULL) {
    count++;
  }

  // Interpret the memory returned by masloc as an array of char * (pointer to a
  // pointer to char)
  char **copy = (char **)malloc((count + 1) * sizeof(char *));
  if (copy == NULL)
    return NULL;

  for (int i = 0; i < count; i++) {
    copy[i] = string_dupe(S[i]);
    if (copy[i] == NULL) {
      for (int j = 0; j < i; j++)
        free(copy[j]);
      return NULL;
    }
  }

  copy[count] = NULL; // null terminate the array of strings

  return copy;
}

void string_set_free(char **S) {
  if (S == NULL)
    return;
  int i = 0;
  while (S[i] != NULL) {
    free(S[i]);
    i++;
  }
  free(S);
}
