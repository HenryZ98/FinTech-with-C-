#include <stdio.h>
#include <stdlib.h>

size_t findLargestKSum(int * array, size_t n_elem, size_t k) {
  // WRITE ME
  if(k > n_elem) {
    //for(int i=0; i<n_elem; i++) {
    //int large = array[0];
    //if(array[i] > large) {
    //	large = array[i];
    // }
    //}
    return (size_t)-1;
  }
  else {
    int large = 0;
    int idx = 0;
    for(int i=0; i<n_elem-k+1; i++) {
      int n = 0;
      for(int j=0; j<k; j++) {
	n += array[i+j];
      }
      if(n > large) {
	large = n;
	idx = i;
      }
    }
    return idx;
  }
}

int main(void) {
  int nums1[] = {5, 8, -1, 3, 9, 2, 4, 19, -3, 6, 9, 12, 11, -3, 5};
  size_t ind1 = findLargestKSum(nums1, 15, 3);
  printf("The index of the largest K sum is %zu\n", ind1);
  // MORE TESTS
  return EXIT_SUCCESS;
}
