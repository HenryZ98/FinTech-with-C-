#include "corr.hpp"
#include <cstdio>
#include <cstdlib>
#include <string>
#include <fstream>
#include <cmath>
#include <vector>
#include <iomanip>

std::vector<std::string> split(std::string &line) {
  std::string delim = ",";
  std::vector<std::string> temp;
  size_t pos1 = 0;
  size_t pos2 = line.find(delim);
  while(pos2 != std::string::npos) {
    temp.push_back(line.substr(pos1, pos2-pos1));
    pos1 = pos2 + delim.size();
    pos2 = line.find(delim, pos1);
  }
  if(pos1 != line.length()) {
    temp.push_back(line.substr(pos1));
  }
  return temp;
}

Asset* get_Asset(std::istream &f) {
  std::string line;
  int n = 0; //count lines from 0
  int n_asset = 0; //count/idx for assets

  std::getline(f, line);
  if(line.size() == 0) {
    perror("Empty File");
    exit(EXIT_FAILURE);
  }
  std::vector<std::string> name = split(line);
  n_asset = name.size() - 1;
  Asset* A = new Asset[n_asset];
  
  for(int i=0; i<n_asset; i++) {
    A[i].name = name[i+1];
    A[i].num_asset = n_asset;
  }
  
  while(std::getline(f, line)) {
    std::vector<std::string> data = split(line);
    int d = data.size()+0;
    if(d != n_asset + 1) {
      perror("Wrong number of data");
      exit(EXIT_FAILURE);
    }
    if(n == 0) {
      for(int i=0; i<n_asset; i++) {
	if(data[i+1] == "null" || atof(data[i+1].c_str()) == 0.0) {
	  perror("Wrong first line");
	  exit(EXIT_FAILURE);
	}
      }
    }
    for(int i=0; i<n_asset; i++) {
      if(data[i+1] == "null" || atof(data[i+1].c_str()) == 0.0) {
	double last = A[i].price.back();
	A[i].price.push_back(last);
      }
      else {
	A[i].price.push_back(atof(data[i+1].c_str()));
      }
    }
    n++;
    data.clear();
    name.clear();
  }

  if(n <= 2) {
    perror("not enough data");
    exit(EXIT_FAILURE);
  }
  for(int i=0; i<n_asset; i++) {
    A[i].n = n;
  }
  return A;
}

void Asset::getROR() {
  for(int i=0; i<n-1; i++) {
    ror.push_back((price[i+1] - price[i])/price[i]);
  }
}

void Asset::getAVGSD() {
  double sum = 0.0;
  for(int i=0; i<n-1; i++) {
    sum += ror[i];
  }
  r_avg = sum/(double)(n-1);
  double variance = 0.0;
  for(int i=0; i<n-1; i++) {
    variance += (ror[i] - r_avg) * (ror[i] - r_avg);
  }
  r_sd = std::sqrt(variance/(n-2));
}

double covariance(Asset A, Asset B) {
  double sum = 0.0;
  for(int i=0; i<A.n-1; i++) {
    sum += (A.ror[i] - A.r_avg) * (B.ror[i] - B.r_avg);
  }
  double cov = sum / (double)(A.n - 1);
  return cov;
}

double correlation(Asset A, Asset B) {
  double cov = covariance(A, B);
  double cor = cov / (A.r_sd * B.r_sd);
  return cor;
}

int main(int argc, char **argv) {
  if(argc != 2) {
    std::cerr << "Only one argument";
    return EXIT_FAILURE;
  }
  std::ifstream f;
  f.open(argv[1]);
  if(!f.is_open()) {
    std::cerr << "Unable to open file";
    return EXIT_FAILURE;
  }
  
  Asset *A = get_Asset(f);
  int n = A[1].num_asset;
  for(int i=0; i<n; i++) {
    A[i].getROR();
  }
  for(int i=0; i<n; i++) {
    A[i].getAVGSD();
  }
  
  //create correlation matrix
  double **cor = new double*[n];
  for(int i=0; i<n; i++) {
    cor[i] = new double[n];
  }
  
  for(int i=0; i<n; i++) {
    for(int j=0; j<n; j++) {
      if(i == j) {
	cor[i][j] = 1.0000;
	  }
      else {
	cor[i][j] = correlation(A[i], A[j]);
      }
    }
  }
  
  //print name
  for(int i=0; i<n; i++) {
    std::cout << A[i].name << std::endl;
  }
  //print matrix
  int r = 0;
  int c = 0;
  std::cout.setf(std::ios::fixed);
  //print row 1
  std::cout << std::setprecision(4) << '[' << ' ' << cor[r][c];
  for(c=1; c<n; c++) {
    std::cout << ',';
    if(cor[r][c] >= 0) {
      std::cout << std::setprecision(4) << ' ' << cor[r][c];
    }
    else {
      std::cout << std::setprecision(4) << cor[r][c];
    }
  }
  std::cout << std::endl;
  //print row 2 to row n
  for(r=1; r<n; r++) {
    //first element
    std::cout << ' ';
    if(cor[r][0] >= 0) {
      std::cout << std::setprecision(4) << ' ' << cor[r][0];
    }
    else {
      std::cout << std::setprecision(4) << cor[r][0];
    }
    //rest of elements
    for(c=1; c<n; c++) {
      std::cout << ',';
      if(cor[r][c] >= 0) {
	std::cout << std::setprecision(4) << ' ' << cor[r][c];
      }
      else {
	std::cout << std::setprecision(4) << cor[r][c];
      }
    }
    //check if r is the last row
    if(r == n-1) {
      std::cout << ']';
      std::cout << std::endl;
    }
    else {
      std::cout << std::endl;
    }
  }
    
  for(int i=0; i<n; i++) {
    delete[] cor[i];
  }
  delete[] cor;
  
  delete[] A;
  return EXIT_SUCCESS;
}
