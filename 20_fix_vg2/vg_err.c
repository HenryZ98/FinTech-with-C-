#include <stdio.h>
#include <stdlib.h>


char ** readLines(size_t *np) {
  char * line = NULL;
  size_t sz = 0;
  char ** ans = NULL;
  while (getline(&line, &sz, stdin) >= 0) {
    ans = realloc(ans, (*np + 1) * sizeof(*ans));
    ans[*np] = line;
    line = NULL;
    (*np)++;
  }
  free(line);
  return ans;
}

int main(void) {
  size_t n = 0;
  char ** allstrings;
  
  allstrings = readLines(&n);
  
  for (size_t i = 0; i < (n / 2); i++) {
    size_t j = n - i - 1;
    char *temp = allstrings[i];
    allstrings[i] = allstrings[j];
    allstrings[j] = temp;
  }
  
  for (size_t i = 0; i < n; i++) {
    printf("%s", allstrings[i]);
  }
  
  for (size_t x = 0; x < n; x++) {
    free(allstrings[x]);
  }
  
  free(allstrings);
  return EXIT_SUCCESS;
}
