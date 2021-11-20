#include <stdio.h>
#include <stdlib.h>

int * myFn(int * p, int ** q) {
  p++;
  printf("*p = %d\n", *p);
  *p += 2;
  **q -= 4;
  (*q)++;
  printf("**q = %d\n", **q);
  return p;
}

int main(void) {
  int data[] = {6, 93, 87, 4};
  int * p = &data[1];
  int * x = &data[2];
  int ** ptrs[] = {&p, &x};
  for (int i = 0; i < 2; i++) {
    printf("%d\n", **ptrs[i]);
  }
  int * r = myFn(p, ptrs[1]);
  printf("*r = %d\n", *r);
  **ptrs[0] += 100;
  **ptrs[1] += 1000;
  for (int i = 0; i < 4; i++) {
    printf("%d\n", data[i]);
  }
  return EXIT_SUCCESS;
}
