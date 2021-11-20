#include "parse.hpp"

#include <exception>
#include <fstream>
#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <string>
#include <vector>
// any other headers you need

class invalid_input : public std::exception {
  // override what() here
public:
  const char* what() const throw() {
    return "Invalid input";
  }
};

item_t * parseLine(const std::string & line) {
  // write me
  item_t* it = new item_t();
  size_t pos = 0;
  std::string name;
  std::vector<std::string> values;
  
  size_t m = line.find(':');
  name = line.substr(pos, m);
  it->first = name;

  size_t k = line.find(": ");
  if(k == std::string::npos) {
    values.push_back(line.substr(m+1, line.size()));
    values.push_back(" ");
  }
  else{
    size_t d = line.find(",");
    if(d == std::string::npos) {
      values.push_back(line.substr(m+1, d-1));
      values.push_back("");
    }
    else{
      values.push_back(line.substr(m+1, d-3));
      values.push_back(line.substr(d+1, line.size()));
    }
  }
  it->second = values;
  
  return it;  
}

int main(int argc, char **argv) {
  if(argc != 2) {
    perror("Wrong number of input");
    return EXIT_FAILURE;
  }

  std::ifstream f(argv[1]);
  if(!f.is_open()) {
    perror("Could not open file");
    return EXIT_FAILURE;
  }
  
  std::string line;
  std::vector<item_t*> item;
  while(getline(f, line)) {
    try {
      if(line.find(':') == line.npos) {
	throw invalid_input();
      }
    }
    catch(invalid_input & ii) {
      std::cerr << ii.what() << std::endl;
      continue;
    }
    item_t * it = parseLine(line);
    item.push_back(it);
  }

  for(size_t i=0; i<item.size(); i++) {
    std::cout << "key = " << item[i]->first << std::endl;
    std::cout << "  values =";
    if(item[i]->second[1] == " " || item[i]->second[1] == "") {
      std::cout << item[i]->second[0] << item[i]->second[1] << std::endl;
    }
    else{
      std::cout << item[i]->second[0] << ';' << item[i]->second[1] << std::endl;
    }
  }
  
  for(size_t i=0; i<item.size(); i++) {
    delete item[i];
  }
  
  return EXIT_SUCCESS;
}
