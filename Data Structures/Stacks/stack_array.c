#include <assert.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

#define INITIAL_MEM 1

typedef int data_t;

typedef struct {
  data_t *data;
  data_t size;
  data_t maxcap;
} mystack_t;

mystack_t *make_empty_stack(void);
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

mystack_t *make_empty_stack(void) {
  mystack_t *new = malloc(sizeof(mystack_t));
  assert(new != NULL);

  new->data = NULL;
  new->size = 0;
  new->maxcap = 0;
  return new;
}

void free_stack(mystack_t *s) {
  assert(s != NULL);
  free(s->data);
  s->data = NULL;
  free(s);
  s = NULL;
}

void push(mystack_t *s, data_t value) {
  if (s->size == s->maxcap) {
    s->maxcap = s->maxcap == 0 ? INITIAL_MEM : s->maxcap * 2;
    data_t *new_data = realloc(s->data, s->maxcap * sizeof(data_t));
    assert(new_data != NULL);
    s->data = new_data;
  }

  s->data[s->size++] = value;
}

data_t pop(mystack_t *s) {
  assert(s != NULL && s->size > 0);
  return s->data[--s->size];
}
