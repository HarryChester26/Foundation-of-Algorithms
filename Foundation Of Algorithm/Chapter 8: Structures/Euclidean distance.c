#include <math.h>
#include <stdio.h>

typedef struct coordinate {
  double x;
  double y;
} vector_t;

double distance(vector_t p1, vector_t p2);

int main(int argc, char *argv[]) {
  vector_t p1, p2;
  printf("Enter two points: ");
  scanf("(%lf, %lf) (%lf, %lf)", &(p1.x), &(p1.y), &(p2.x), &(p2.y));
  double result = distance(p1, p2);
  printf("distance between (%.1lf, %.1lf) and (%.1lf, %.1lf) is %.1lf\n", p1.x,
         p1.y, p2.x, p2.y, result);
  return 0;
}

double distance(vector_t p1, vector_t p2) {
  return sqrt(pow(p2.x - p1.x, 2) + pow(p2.y - p1.y, 2));
}
