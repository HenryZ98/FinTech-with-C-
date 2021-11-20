#include <stdio.h>
#include <stdlib.h>

int * g(int * p, int ** q, int n) {
  int * temp = p;
  for (int i = 0; i < n / 2; i++) {
    *temp += *p - **q;
    (*q)++;
    temp--;
  }
  return temp;
}

int main(void) {
  int a[] = {0, 3, 6, 9, 12};
  int * p = a;
  p = g(&a[4], &p, 5);
  printf("a is {%d, %d, %d, %d, %d}\n", a[0], a[1], a[2], a[3], a[4]);
  printf("*p is %d\n", *p);
  return EXIT_SUCCESS;
}
