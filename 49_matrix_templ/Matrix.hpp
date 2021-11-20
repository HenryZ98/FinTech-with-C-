#ifndef __T_MATRIX_HPP__
#define __T_MATRIX_HPP__

#include <assert.h>

#include <cstdlib>
#include <iostream>
#include <vector>

//YOUR CODE GOES HERE!
template<typename T>
class Matrix {
private:
  int numRows;
  int numColumns;
  std::vector<std::vector<T> > rows;

public:
  Matrix():numRows(0), numColumns(0) {}
  Matrix(int r, int c);
  Matrix(const Matrix<T> &rhs): numRows(rhs.numRows), numColumns(rhs.numColumns), rows(rhs.rows) {}
  Matrix<T> &operator=(const Matrix<T> & rhs);
  int getRows() const;
  int getColumns() const;
  const std::vector<T> & operator[](int index) const;
  std::vector<T> & operator[](int index);
  bool operator==(const Matrix<T> & rhs) const;
  Matrix<T> operator+(const Matrix<T> & rhs) const;
};

template<typename T>
std::ostream & operator<<(std::ostream & s, const Matrix<T> & rhs);

template <typename T>
Matrix<T>::Matrix(int r, int c) : numRows(r), numColumns(c), rows(r) {
  for(int i=0; i<numRows; i++){
    std::vector<T> temp(numColumns);
    rows[i] = temp;
  }
}

template<typename T>
Matrix<T> & Matrix<T>::operator=(const Matrix<T> & rhs) {
  if(this != &rhs){
    numRows = rhs.numRows;
    numColumns = rhs.numColumns;
    rows = rhs.rows;
  }
  return *this;
}

template <typename T>
int Matrix<T>::getRows() const {
  return numRows;
}

template <typename T>
int Matrix<T>::getColumns() const {
  return numColumns;
}

template <typename T>
const std::vector<T> & Matrix<T>::operator[](int index) const {
  assert(index>=0);
  assert(index<numRows);
  return rows[index];
}

template <typename T>
std::vector<T> & Matrix<T>::operator[](int index) {
  assert(index>=0);
  assert(index<numRows);
  return rows[index];
}

template <typename T>
bool Matrix<T>::operator==(const Matrix<T> & rhs) const {
  if(numRows!=rhs.numRows || numColumns!=rhs.numColumns){
    return false;
  }
  if(rows != rhs.rows){ 
      return false;
  }
  return true;
}

template <typename T>  
Matrix<T> Matrix<T>::operator+(const Matrix<T> & rhs) const {
  assert(numRows == rhs.numRows);
  assert(numColumns == rhs.numColumns);
  Matrix<T> s(numRows,numColumns);
  for(int i=0;i<numRows;i++){
    for(int j=0;j<numColumns;j++){
      s.rows[i][j] = rows[i][j] + rhs.rows[i][j];
    }
  }
  return s;
}

template <typename T>
std::ostream & operator<<(std::ostream & s, const Matrix<T> & rhs) {
  if(rhs.getRows()==0){
    s<<"[  ]";
    return s;
  } 
  s<<"[ ";
  int i=0;
  for(i=0;i<rhs.getRows()-1;i++){
    s<<"{";
    int j=0;
    for(j=0;j<rhs.getColumns()-1;j++){
      s<<(rhs[i])[j]<<", ";  
    }
    s<<(rhs[i])[j]<<"},"<<std::endl;  
  }
  int j=0;
  s<<"{";
  for(j=0;j<rhs.getColumns()-1;j++){
    s<<(rhs[i])[j]<<", ";  
  }
  s<<(rhs[i])[j]<<"}"<<" ]";
  return s;
}

#endif
