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
} queue_t;

queue_t *make_empty_queue(void);
void free_queue(queue_t *q);
void enqueue(queue_t *q, data_t value);
data_t dequeue(queue_t *q);

int main(int argc, char *argv[]) {
  queue_t *q = make_empty_queue();
  char c;
  while ((c = getchar()) != EOF) {
    if (isdigit(c)) {
      enqueue(q, c - '0');
    } else if (c == 'd') {
      printf("Popped %d from the queue\n", dequeue(q));
    }
  }

  free_queue(q);
}

queue_t *make_empty_queue(void) {
  queue_t *myqueue = (queue_t *)malloc(sizeof(queue_t));
  assert(myqueue != NULL);

  myqueue->data = NULL;
  myqueue->size = 0;
  myqueue->maxcap = 0;

  return myqueue;
}

void free_queue(queue_t *q) {
  assert(q != NULL);
  free(q->data);
  q->data = NULL;
  free(q);
  q = NULL;
}

void enqueue(queue_t *q, data_t value) {
  assert(q != NULL);

  if (q->size == q->maxcap) {
    q->maxcap = q->maxcap == 0 ? INITIAL_MEM : q->maxcap * 2;
    data_t *new_data = realloc(q->data, q->maxcap * sizeof(data_t));
    assert(new_data != NULL);
    q->data = new_data;
  }

  q->data[q->size++] = value;
}

data_t dequeue(queue_t *q) {
  assert(q != NULL && q->size > 0);

  data_t old_data = q->data[0];
  for (int i = 0; i < q->size - 1; i++) {
    q->data[i] = q->data[i + 1];
  }
  q->size--;

  return old_data;
}
