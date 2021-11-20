#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

void abs_cmp(double a, double b, double pct) {
    if(b <= a + pct && b >= a - pct) {
        printf("equal");
    }
    else {
      if(b > a) {
        printf("less");
      }
      else {
        printf("greater");
      }
    }
    return;
}

void pct1_cmp(double a, double b, double pct) {
    if(b >= a - a * pct/100 && b <= a + a * pct/100) {
        printf("equal");
    }
    else {
      if(b > a) {
        printf("less");
      }
      else {
        printf("greater");
      }
    }
    return;
}

void pct2_cmp(double a, double b, double pct) {
    if(a >= b - b * pct/100 && a <= b + b * pct/100) {
        printf("equal");
    }
    else {
      if(a < b) {
        printf("less");
      }
      else {
        printf("greater");
      }
    }
    return;
}


int compare(double a, double b, const char * type, double pct) {
  int x;
  int y;
  int z;
  x = strcmp(type, "abs");
  if(x == 0) {
    abs_cmp(a, b, pct);
    return EXIT_SUCCESS;
  }
  y = strcmp(type, "pct1");
  if(y == 0) {
    pct1_cmp(a, b, pct);
    return EXIT_SUCCESS;
  }
  z = strcmp(type, "pct2");
  if(z == 0) {
    pct2_cmp(a, b, pct);
    return EXIT_SUCCESS;
  }
  if(x != 0 &&  y != 0 && z != 0) {
    perror("Wrong type");
    return EXIT_FAILURE;
  }
  
  return 0;
}



int main(int argc, char *argv[]) {
  if(argc != 5) {
    perror("Not enough arguments");
    return EXIT_FAILURE;
  }
  
  char *a = argv[1];
  char *b = argv[2];
  char *c = argv[4];
  for(int i=0; i<strlen(a); i++) {
    if(isdigit(a[i]) == 0 && a[i] != '.') {
      perror("Wrong number1");
      return EXIT_FAILURE;
    }
  }
  for(int i=0; i<strlen(b); i++) {
    if(isdigit(b[i]) == 0 && b[i] != '.') {
      perror("Wrong number2");
      return EXIT_FAILURE;
    }
  }
  for(int i=0; i<strlen(c); i++) {
    if(isdigit(c[i]) == 0 && c[i] != '.') {
      perror("Wrong percent");
      return EXIT_FAILURE;
    }
  }

  double num1;
  double num2;
  double pct;
  num1 = strtod(argv[1], NULL);
  num2 = strtod(argv[2], NULL);
  pct = strtod(argv[4], NULL);
  
  
  const char *type;
  type = argv[3];
  
 
  return compare(num1, num2, type, pct);;
}
