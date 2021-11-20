#include <iostream>
#include <cstdlib>
#include <vector>
#include <fstream>
#include <string>
#include <algorithm>

class MySort {
public:
  std::vector<std::string> readlines(std::istream &f, size_t * np);
  void print_sort(std::istream &f);
};

std::vector<std::string> MySort::readlines(std::istream &f, size_t * np) {
  std::string line;
  std::vector<std::string> lines;
  size_t n = 0;
  while(getline(f, line)) {
    lines.push_back(line);
    n++;
  }
  std::sort(lines.begin(), lines.end());
  *np = n;
  return lines;
}

void MySort::print_sort(std::istream &f) {
  size_t n = 0;
  std::vector<std::string> arr = MySort::readlines(f, &n);
  for(size_t i=0; i<n; i++) {
    std::cout << arr[i] << std::endl;
  }
}

int main(int argc, char **argv) {
  MySort sort;
  if(argc == 1) {
    sort.print_sort(std::cin);
  }
  else if(argc > 1) {
    for(int i=1; i<argc; i++) {
      std::ifstream input(argv[i]);
      if(!input.is_open()) {
	std::cerr << "Unable to open file";
	return EXIT_FAILURE;
      }
      sort.print_sort(input);
    }
  }
  return EXIT_SUCCESS;
}
