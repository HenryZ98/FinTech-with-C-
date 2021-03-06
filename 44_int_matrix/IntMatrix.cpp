#include "IntMatrix.hpp"

IntMatrix::IntMatrix(): numRows(0), numColumns(0), rows(NULL) {}

IntMatrix::IntMatrix(int r, int c): numRows(r), numColumns(c), rows(new IntArray*[r]) {
    for(int i=0; i<numRows; i++) {
      rows[i] = new IntArray(numColumns);
    }
}

IntMatrix::IntMatrix(const IntMatrix & rhs) {
  numRows = rhs.numRows;
  numColumns = rhs.numColumns;
  rows = new IntArray*[numRows];
  for(int i=0; i<numRows; i++) {
    rows[i] = new IntArray(numColumns);
    *rows[i] = *rhs.rows[i];
  }
}

IntMatrix::~IntMatrix() {
  for(int i=0; i<numRows; i++) {
    delete rows[i];
  }
  delete[] rows;
}

IntMatrix & IntMatrix::operator=(const IntMatrix & rhs) {
  if(this != &rhs) {
    for(int i=0; i<numRows; i++) {
      delete rows[i];
    }
    delete[] rows;
    numRows = rhs.numRows;
    numColumns = rhs.numColumns;
    IntArray **temp = new IntArray*[rhs.numRows];
    for(int i=0; i<rhs.numRows; i++){
      temp[i] = new IntArray(numColumns);
      *temp[i] = *rhs.rows[i];
    }
    rows = temp;
  }
  return *this;
}

int IntMatrix::getRows() const {
  return numRows;
}

int IntMatrix::getColumns() const {
  return numColumns;
}

const IntArray & IntMatrix::operator[](int index) const {
  assert(0 <= index && index < numRows);
  return *rows[index];
}

IntArray & IntMatrix::operator[](int index) {
  assert(0 <= index && index < numRows);
  return *rows[index];
}

bool IntMatrix::operator==(const IntMatrix & rhs) const {
  if(numRows != rhs.numRows || numColumns != rhs.numColumns) {
    return false;
  }
  for(int i=0; i<numRows; i++) {
    if(*rows[i] != *rhs.rows[i]) {
      return false;
    }
  }
  return true;
}

IntMatrix IntMatrix::operator+(const IntMatrix & rhs) const {
  assert(numRows == rhs.numRows);
  assert(numColumns == rhs.numColumns);
  IntMatrix s(numRows, numColumns);
  for(int i=0; i<numRows; i++) {
    IntArray &z = *s.rows[i];
    IntArray &x = *rows[i];
    IntArray &y = *rhs.rows[i];
    for(int j=0; j<numColumns; j++) {
      z[j] = x[j] + y[j];
    }
  }
  return s;
}

std::ostream & operator<<(std::ostream & s, const IntMatrix & rhs) {
  if(rhs.getRows() == 0) {
    s<<"[]";
    return s;
  }
  s<<"[ ";
  int i=0;
  for(i=0; i<rhs.getRows()-1; i++) {
    s<<rhs[i]<<",\n";
  }
  s<<rhs[i]<<" ]";
  return s;
}
