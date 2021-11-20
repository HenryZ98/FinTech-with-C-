#include <stdio.h>
#include <stdlib.h>

struct _point_t {
  double x;
  double y;
};
typedef struct _point_t point_t;

point_t * init_points(size_t sz) {
  point_t * answer = malloc(sizeof(point_t) * sz);
  for (size_t i = 0; i < sz; i++) { 
    answer[i].x = i;
    answer[i].y = i * i;
  }
  return answer;
}

float ** calculate(point_t * arr1, point_t * arr2, size_t size) {
  float ** answer = malloc(size * size * sizeof(float));
  for (size_t i = 0; i < size; i++) {
    answer[i] = malloc(size * sizeof(**answer));
    for (size_t j = 0; j < size; j++) {
      float sum = arr1[i].x + arr1[i].y + arr2[j].x + arr2[j].y;
      answer[i][j] = sum;
    }
  }
  return answer;
}

int main(int argc, char ** argv) {
  size_t size = strtoull(argv[1], NULL, 10);
  point_t * arr1 = init_points(size);
  point_t * arr2 = init_points(size);
  float ** results = calculate(arr1, arr2, size);
  for (size_t i = 0; i < size; i++) {
    for (size_t j = 0; j < size; j++) {
      printf("%2.2f ", results[i][j]);
    }
    printf("\n");
  }
  free(arr1);
  free(arr2);
  for (size_t i = 0; i < size; i++) {
    free(results[i]);
  }
  free(results);
  return EXIT_SUCCESS;
}
