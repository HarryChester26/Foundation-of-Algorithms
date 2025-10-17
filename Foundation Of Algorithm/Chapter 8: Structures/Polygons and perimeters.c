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
double perimeter(poly_t P);

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
  printf("Perimeter is %.4lf\n", perimeter(P));
  return 0;
}

double perimeter(poly_t P) {
  double result = 0;
  for (int i = 1; i < P.length; i++) {
    double temp = sqrt(pow(P.array[i][0] - P.array[i - 1][0], 2) +
                       pow(P.array[i][1] - P.array[i - 1][1], 2));
    result += temp;
  }
  result += sqrt(pow(P.array[P.length - 1][0] - P.array[0][0], 2) +
                 pow(P.array[P.length - 1][1] - P.array[0][1], 2));
  return result;
}
