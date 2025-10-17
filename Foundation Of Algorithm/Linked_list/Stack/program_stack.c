#include <assert.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

#define INITIAL_STACK_SIZE 10

typedef int data_t;

typedef struct {
  // TODO: implement the struct
  data_t top;
  data_t capacity;
  data_t *array;
} mystack_t;

mystack_t *make_empty_stack();
void free_stack(mystack_t *s);
void push(mystack_t *s, data_t value);
data_t pop(mystack_t *s);

int main(int argc, char *argv[]) {

  mystack_t *s = make_empty_stack();
  char c;
  while ((c = getchar()) != EOF) {
    if (c == 'p') {
      printf("Popped %d from the stack\n", pop(s));
    } else if (isdigit(c)) {
      push(s, c - '0');
    }
  }
  free_stack(s);
}

// TODO: implement the functions

mystack_t *make_empty_stack() {
  mystack_t *s = (mystack_t *)malloc(sizeof(*s));
  assert(s != NULL);
  s->capacity = INITIAL_STACK_SIZE;
  s->top = 0;
  s->array = (data_t *)malloc(s->capacity * sizeof(data_t));
  assert(s->array != NULL);

  return s;
}

void free_stack(mystack_t *s) {
  assert(s != NULL);
  free(s->array);
  free(s);
}

void push(mystack_t *s, data_t value) {
  if (s->top == s->capacity) {
    s->capacity *= 2;
    data_t *new_array = realloc(s->array, s->capacity * sizeof(data_t));
    if (new_array == NULL) {
      fprintf(stderr, "Memory allocation failed\n");
      exit(1);
    }
    s->array = new_array;
  }
  s->array[s->top++] = value;
}

data_t pop(mystack_t *s) {
  if (s->top == 0) {
    fprintf(stderr, "Stack underflow\n");
    exit(1);
  }
  return s->array[--s->top];
}
