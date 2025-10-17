#include <math.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct coordinate {
  double x;
  double y;
} vector_t;

typedef struct Polygon {
  int length;
  double array[100][2];
} poly_t;

double PolyArea(poly_t P);

int main(int argc, char *argv[]) {
  vector_t p;
  poly_t P;
  int index = 0;
  printf("Enter (3-100) points counter-clockwise:\n");
  while (scanf("%lf,%lf", &p.x, &p.y) != EOF) {
    P.array[index][0] = p.x;
    P.array[index][1] = p.y;
    index++;
  }
  P.length = index;

  printf("Area is %.4lf\n", PolyArea(P));
  return 0;
}

double PolyArea(poly_t P) {
  double area = 0;
  int j = P.length - 1;
  for (int i = 0; i < P.length; i++) {
    area += P.array[j][0] * P.array[i][1] - P.array[i][0] * P.array[j][1];
    j = i;
  }
  return fabs(area) / 2;
}
