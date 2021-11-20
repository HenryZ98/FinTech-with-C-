#include <stdio.h>
#include <stdlib.h>

void f(int x, int * p, int ** q) {
  x = x + 7;
  *p = **q - x;
  *q = p;
}

int main(void) {
  int a = 6;
  int b = 3;
  int c = 1;
  int * data[] = {&a, &b, &c};
  int ** q = &data[1];
  **q = 43;
  q[0] = q[1];
  printf("a = %d, b = %d, c = %d\n", a, b, c);
  for (int i = 0; i < 3; i++) {
    *data[i] = *data[i] + 11;
  }
  printf("a = %d, b = %d, c = %d\n", a, b, c);
  f(a, &b, &data[2]);
  *q[1] = *q[1] + 2;
  printf("a = %d, b = %d, c = %d\n", a, b, c);
  return EXIT_SUCCESS;
}
