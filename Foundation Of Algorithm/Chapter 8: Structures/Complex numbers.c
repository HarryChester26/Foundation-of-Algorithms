/* Exercise 8.05: Complex numbers
 * Scaffold: Quynh-Chi Nguyen, Alistair Moffat, May 2010
 * (c) University of Melbourne */

#include <stdio.h>

// TODO: Define complex_t type here.
typedef struct complex {
  double real_part;
  double img_part;
} complex_t;

complex_t complex_add(complex_t, complex_t);
complex_t complex_mpy(complex_t, complex_t);
complex_t read_complex(void);
void print_complex(complex_t);

/* simple scaffolding to test functions */
int main(int argc, char *argv[]) {
  complex_t v1, v2;

  printf("Enter two complex numbers v1, v2: ");
  v1 = read_complex();
  v2 = read_complex();

  printf("v1 =                  ");
  print_complex(v1);
  printf("v2 =                  ");
  print_complex(v2);
  printf("complex_add(v1, v2) = ");
  print_complex(complex_add(v1, v2));
  printf("complex_mpy(v1, v2) = ");
  print_complex(complex_mpy(v1, v2));
  return 0;
}

complex_t complex_add(complex_t v1, complex_t v2) {
  // TODO: complete
  v1.real_part = v1.real_part + v2.real_part;
  v1.img_part = v1.img_part + v2.img_part;
  return v1;
}

complex_t complex_mpy(complex_t v1, complex_t v2) {
  // TODO: complete
  double real = v1.real_part * v2.real_part - v1.img_part * v2.img_part;
  double img = v1.real_part * v2.img_part + v1.img_part * v2.real_part;
  v1.real_part = real;
  v1.img_part = img;
  return v1;
}

complex_t read_complex(void) {
  // TODO: complete
  complex_t input;
  scanf("%lf+%lfi", &input.real_part, &input.img_part);
  return input;
}

void print_complex(complex_t v) {
  // TODO: complete
  printf("%6.2lf + %6.2lfi\n", v.real_part, v.img_part);
}
