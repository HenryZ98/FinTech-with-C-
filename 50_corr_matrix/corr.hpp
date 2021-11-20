#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <vector>

class Asset {
public:
  std::string name;
  std::vector<double> price;
  std::vector<double> ror;
  double r_avg;
  double r_sd;
  int n; //num of data
  int num_asset;
public:
  Asset() {}
  void getROR();
  void getAVGSD();
  friend Asset * get_Asset(std::istream &f);
  ~Asset() {}
};


double covariance(Asset A, Asset B);
double correlation(Asset A, Asset B);
