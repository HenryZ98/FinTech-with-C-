#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void free_arr(char **arr1, size_t i, char **arr2, size_t j) {
  for(size_t a=0; a<i; a++) {
    free(arr1[a]);
  }
  for(size_t b=0; b<j; b++) {
    free(arr2[b]);
  }
  free(arr1);
  free(arr2);
}
  
void arr_cmp(char **arr1, size_t i, char **arr2, size_t j) {
  size_t count = 0;
  if(i >= j) {
    count = i - j;
    for(size_t a=0; a<j; a++) {
      if(strcmp(arr1[a], arr2[a]) != 0) {
	  count++;
	}
    }
  }
  else {
    count = j - i;
    for(size_t b=0; b<i; b++) {
      if(strcmp(arr1[b], arr2[b]) != 0) {
	  count++;
	}
    }
  }
  printf("%ld\n", count);
  free_arr(arr1, i, arr2, j);	
}


void file_cmp(FILE *f1, FILE *f2) {
  char *line1 = NULL;
  size_t sz1 = 0; //allocated by getline
  char **arr1 = NULL;
  size_t i = 0;
  
  char *line2 = NULL;
  size_t sz2 = 0;
  char **arr2 = NULL;
  size_t j = 0;
  
  while(getline(&line1, &sz1, f1) >= 0) {
    arr1 = realloc(arr1, (i+1)*sizeof(*arr1));
    arr1[i] = line1;
    line1 = NULL;
    i++;
  }
  free(line1); //free the buffer allocated after EOF

  while(getline(&line2, &sz2, f2) >= 0) {
    arr2 = realloc(arr2, (j+1)*sizeof(*arr2));
    arr2[j] = line2;
    line2 = NULL;
    j++;
  }
  free(line2);
  
  //free_arr(arr1, i, arr2, j);
  //printf("%s\n", arr1[0]);
  //printf("%ld, %ld", i, j);
  
  arr_cmp(arr1, i, arr2, j);
}




int main(int argc, char *argv[]) {
  if(argc != 3) {
    perror("Not enough inputs.");
    return EXIT_FAILURE;
  }
  FILE *f1 = fopen(argv[1], "r");
  if(f1 == NULL) {
    perror("Could not open file");
    return EXIT_FAILURE;
  }
  FILE *f2 = fopen(argv[2], "r");
  if(f2 == NULL) {
    perror("Could not open file");
    return EXIT_FAILURE;
  }
  
  file_cmp(f1, f2);
  
  fclose(f1);
  fclose(f2);
  
  return EXIT_SUCCESS;
}
