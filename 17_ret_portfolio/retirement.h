#ifndef __RETIREMENT_H__
#define __RETIREMENT_H__

#include <stdlib.h>

struct ror_arr_tag {
  // WRITE ME
  double *date;
  double *index;
  double *div;
  size_t n;
};
typedef struct ror_arr_tag ror_arr_t;

struct bond_tag {
  double *date;
  double *price;
  size_t n;
};
typedef struct bond_tag bond_t;

// struct to hold array of dates and cumulative investments
// (hint: can be used for any investment strategy)
struct ret_portfolio_tag {
  double * date;
  double * cum_invest;
};
typedef struct ret_portfolio_tag ret_portfolio_t;

#endif
