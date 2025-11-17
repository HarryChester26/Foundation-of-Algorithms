typedef int data_t;

int cmp(data_t *p1, data_t *p2) { return *p1 - *p2; }

void swap_data(data_t *p1, data_t *p2) {
  int temp = *p1;
  *p1 = *p2;
  *p2 = temp;
}

void copy_data(data_t *to, data_t *fr) { *to = *fr; }
