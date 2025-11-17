/* Building pq based on max_heap */
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#define INITIAL_MEM 1

typedef int data_t;

typedef struct {
  data_t data;
  int prior;
} node_t;

typedef struct {
  node_t *queue;
  int size;
  int max_cap;
} pq_t;

pq_t *pq_create_empty(void);
int is_pq_empty(pq_t *pq);
pq_t *pq_insert(pq_t *pq, data_t value, int priority);
int pq_max_priority(pq_t *pq);
void sift_down(pq_t *pq, int parent);
node_t delete_max(pq_t *pq);

int main(int argc, char *agrv[]) { return 0; }

pq_t *pq_create_empty(void) {
  pq_t *pq = malloc(sizeof(pq_t));
  assert(pq != NULL);
  pq->queue = NULL;
  pq->size = pq->max_cap = 0;
  return pq;
}

int is_empty_pq(pq_t *pq) {
  assert(pq != NULL);
  return pq->size == 0;
}

int cmp(node_t *t1, node_t *t2) {
  if (t1->prior > t2->prior)
    return 1;
  else if (t1->prior < t2->prior)
    return -1;
  else
    return 0;
}

void swap_data(node_t *t1, node_t *t2) {
  node_t temp = *t1;
  *t1 = *t2;
  *t2 = temp;
}

pq_t *pq_insert(pq_t *pq, data_t value, int priority) {
  assert(pq != NULL);
  if (pq->size == pq->max_cap) {
    pq->max_cap = pq->max_cap == 0 ? INITIAL_MEM : pq->max_cap * 2;
    node_t *new_queue = realloc(pq->queue, pq->max_cap * sizeof(node_t));
    assert(new_queue != NULL);
    pq->queue = new_queue;
  }
  pq->queue[pq->size].data = value;
  pq->queue[pq->size].prior = priority;
  int i = pq->size++;
  while (i > 0) {
    int parent = (i - 1) / 2;
    if (cmp(&pq->queue[parent], &pq->queue[i]) < 0) {
      swap_data(&pq->queue[parent], &pq->queue[i]);
      i = parent;
    } else {
      break;
    }
  }

  return pq;
}

void sift_down(pq_t *pq, int parent) {
  int child = 2 * parent + 1;
  if (child < pq->size) {
    if (child + 1 < pq->size &&
        cmp(&pq->queue[child], &pq->queue[child + 1]) < 0) {
      child = child + 1;
    }
    if (cmp(&pq->queue[parent], &pq->queue[child]) < 0) {
      swap_data(&pq->queue[parent], &pq->queue[child]);
      sift_down(pq, child);
    }
  }
}

int pq_max_priority(pq_t *pq) {
  assert(pq != NULL && pq->size > 0);
  return pq->queue[0].prior;
}

node_t delete_max(pq_t *pq) {
  assert(pq != NULL);

  node_t old_max = pq->queue[0];
  swap_data(&pq->queue[0], &pq->queue[--pq->size]);
  sift_down(pq, 0);
  return old_max;
}
