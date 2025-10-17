#include <stdio.h>

#define MAXVAL 1000

typedef struct student_info {
  int student_id;
  int student_mark;
} student_t;

typedef struct student_list {
  student_t students[1000];
  int size;
} student_list_t;

int read_student_info(student_list_t list) {
  int order = 0, excess = 0, id, mark;
  printf("Enter as many as %d \"studnum mark\" pairs, ^D to end\n", MAXVAL);
  while ((scanf("%d  %d", &id, &mark)) == 2) {
    if (order == MAXVAL) {
      excess += 1;
    } else {
      list.students[order].student_id = id;
      list.students[order].student_mark = mark;
      order += 1;
    }
  }
  printf("%d pairs read into arrays", order);
  if (excess) {
    printf(", %d excess values discarded", excess);
  }
  printf("\n");
  return order;
}

void sort_student(student_list_t list, int n) {
  for (int i = 0; i < n; i++) {
    for (int j = i - 1; j >= 0 && list.students[j].student_id >
                                      list.students[j + 1].student_id;
         j--) {
      int temp = list.students[j].student_mark;
      list.students[j].student_mark = list.students[j + 1].student_mark;
      list.students[j + 1].student_mark = temp;
    }
  }
}

int main(int argc, char *argv[]) {
  student_list_t list;
  int stu_num = read_student_info(list);
  sort_student(list, stu_num);
  printf("studnum  mark\n");
  for (int i = 0; i < stu_num; i++) {
    printf("%d%5d\n", list.students[i].student_id,
           list.students[i].student_mark);
  }

  return 0;
}
