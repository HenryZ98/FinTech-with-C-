#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "retirement.h"

/* function reads each line from a file between the specified dates,
   rorFromLine fcn ptr indicates how ror should be calculated 
   based on type of input data
ror_arr_t * readFile(FILE * f,
                     double start,
                     double end,
                     double (*rorFromLine)(char *, double *)) {
  // WRITE ME
}
*/
void free_eq(ror_arr_t *eq) {
  free(eq->date);
  free(eq->index);
  free(eq->div);
  free(eq);
}
void free_bd(bond_t *bd) {
  free(bd->date);
  free(bd->price);
  free(bd);
}
void free_ret(ret_portfolio_t *ret) {
  free(ret->date);
  free(ret->cum_invest);
  free(ret);
}

double *sep_eq(char *line) {
  
  char *s2 = strchr(line, ',');
  *s2 = '\0';
  s2++;
  char *s3 = strchr(s2, ',');
  *s3 = '\0';
  s3++;
  char *n = strchr(s3, '\n');
  if(n != NULL) {
    *n = '\0';
  }
  double *ans = malloc(3*sizeof(*ans));
  ans[0] = strtod(line, NULL);
  ans[1] = strtod(s2, NULL);
  ans[2] = strtod(s3, NULL);
  return ans;
}

double *sep_bd(char *line) {
  char *s2 = strchr(line, ',');
  *s2 = '\0';
  s2++;
  char *n = strchr(s2, '\n');
  if(n != NULL) {
    *n = '\0';
  }
  double *ans = malloc(2*sizeof(*ans));
  ans[0] = strtod(line, NULL);
  ans[1] = strtod(s2, NULL);
  return ans;
}

ror_arr_t * readEquity(FILE *f, double start, double end) {
  ror_arr_t *eq = malloc(sizeof(*eq));
  size_t n =(size_t) ((floor(end)-floor(start)-1)*12+(end-floor(end))*100+(floor(start)+0.12-start)*100+0.5);
  eq->date = malloc((n+1)*sizeof(*eq->date));
  eq->index = malloc((n+1)*sizeof(*eq->index));
  eq->div = malloc((n+1)*sizeof(*eq->div));
  eq->n = n;
  
  size_t sz;
  char *curr = NULL;
  double *ans = NULL;
  size_t i=0;
  while(getline(&curr, &sz, f) >= 0) {
    ans = sep_eq(curr);
    if(ans[0] >= start && ans[0] <= end) { //write eq
      eq->date[i] = ans[0];
      eq->index[i] = ans[1];
      eq->div[i] = ans[2];
      i++;
    }
    free(ans);
    ans = NULL;
    free(curr);
    curr = NULL;
  }
  free(curr);
  free(ans);
  return eq;
}

bond_t * readBond(FILE *f, double start, double end) {
  bond_t *bd = malloc(sizeof(*bd));
  size_t n =(size_t) ((floor(end)-floor(start)-1)*12+(end-floor(end))*100+(floor(start)+0.12-start)*100+0.5);
  bd->date = malloc((n+1)*sizeof(*bd->date));
  bd->price = malloc((n+1)*sizeof(*bd->price));
  bd->n = n;
  
  size_t sz;
  char *curr = NULL;
  double *ans = NULL;
  size_t i = 0;
  while(getline(&curr, &sz, f) >= 0) {    
    ans = sep_bd(curr);
    if(ans[0] >= start && ans[0] <= end) { //write bd
      bd->date[i] = ans[0];
      bd->price[i] = ans[1];
      i++;
    }
    free(ans);
    ans = NULL;
    free(curr);
    curr = NULL;
  }
  free(curr);
  curr = NULL;
  free(ans);
  return bd;
}


ret_portfolio_t *cal_eq(ret_portfolio_t *eq_bal, ror_arr_t *eq) {
  eq_bal->date[0] = eq->date[0];
  eq_bal->cum_invest[0] = 100;
  double dep = 100.00;
  double index_r;
  double div_r;
  for(size_t i=1; i<eq->n+1; i++) {
    eq_bal->date[i] = eq->date[i];
    index_r = eq->index[i]/eq->index[i-1]-1;
    div_r = (eq->div[i]/12)/eq->index[i];
    if(eq_bal->date[i] - floor(eq_bal->date[i]) - 0.01 < 1e-6) {
      dep *= 1.025;
    }
    eq_bal->cum_invest[i] = eq_bal->cum_invest[i-1] * (index_r + div_r + 1) + dep;
  }
  return eq_bal;
}

ret_portfolio_t *cal_bd(ret_portfolio_t *bd_bal, bond_t *bd) {
  bd_bal->date[0] = bd->date[0];
  bd_bal->cum_invest[0] = 100;
  double dep = 100.00;
  double price_r;
  for(size_t i=1; i<bd->n+1; i++) {
    bd_bal->date[i] = bd->date[i];
    price_r = (bd->price[i]/(double)12)/(double)100;
    if(bd_bal->date[i] - floor(bd_bal->date[i]) - 0.01 < 1e-6) {
       dep *= 1.025;
    }
    bd_bal->cum_invest[i] = bd_bal->cum_invest[i-1] * (price_r+1) + dep;
  }
  return bd_bal;
}

ret_portfolio_t *cal_cycle(ret_portfolio_t *cycle_bal, ror_arr_t *eq, bond_t *bd) {
  cycle_bal->date[0] = eq->date[0];
  cycle_bal->cum_invest[0] =100;
  double dep = 100.00;
  double index_r;
  double div_r;
  double price_r;
  double pct = 1.00;
  for(size_t i=1; i<eq->n+1; i++) {
    cycle_bal->date[i] = eq->date[i];
    price_r = (bd->price[i]/(double)12)/(double)100;
    index_r = eq->index[i]/eq->index[i-1]-1;
    div_r = (eq->div[i]/12)/eq->index[i];
    if(cycle_bal->date[i] - floor(cycle_bal->date[i]) - 0.01 < 1e-6) {
       dep *= 1.025;
       pct -= 0.02;
    }
    cycle_bal->cum_invest[i] = cycle_bal->cum_invest[i-1]*(index_r+div_r+1)*pct + cycle_bal->cum_invest[i-1]*(price_r+1)*(1-pct) + dep;
  }
  return cycle_bal;
}


void write_output(size_t n, ret_portfolio_t *eq_bal, ret_portfolio_t *bd_bal, ret_portfolio_t *cycle_bal, FILE *f) {
  for(int i=0; i<n+1; i++) {
    fprintf(f, "%.2f, %.2f, %.2f, %.2f\n", eq_bal->date[i], eq_bal->cum_invest[i], bd_bal->cum_invest[i], cycle_bal->cum_invest[i]);
  }
}


int main(int argc, char **argv) {
  if(argc != 5) {
    perror("Wrong number of input");
    return EXIT_FAILURE;
  }
  
  FILE *equities = fopen(argv[1], "r");
  if(equities == NULL) {
    perror("Cannot open file1");
    return EXIT_FAILURE;
  }
  FILE *bonds = fopen(argv[2], "r");
  if(bonds == NULL) {
    perror("Cannot open file2");
    return EXIT_FAILURE;
  }

  if(strlen(argv[3]) != 7 || strlen(argv[4]) != 7) {
    perror("wrong strat or end");
    return EXIT_FAILURE;
  }
  
  double start = strtod(argv[3], '\0');
  double end = strtod(argv[4], '\0');
  if(start > end) {
    perror("start is bigger than end");
    return EXIT_FAILURE;
  }
  if(start - floor(start) < 0.00999999 || start - floor(start) > 0.12) {
    perror("wrong start month");
    return EXIT_FAILURE;
  }
  if(end - floor(end) < 0.0099999999 || end - floor(end) > 0.12) {
    perror("wrong end month");
    return EXIT_FAILURE;
  }
  

  
  ror_arr_t *eq;
  bond_t *bd;
  eq = readEquity(equities, start, end);
  bd = readBond(bonds, start, end);
  size_t n = eq->n;

  ret_portfolio_t *eq_bal = malloc(sizeof(*eq_bal));
  eq_bal->date = malloc((eq->n + 1)*sizeof(*eq_bal->date));
  eq_bal->cum_invest = malloc((eq->n + 1)*sizeof(*eq_bal->cum_invest));
  eq_bal = cal_eq(eq_bal, eq);

  ret_portfolio_t *bd_bal = malloc(sizeof(*bd_bal));
  bd_bal->date = malloc((bd->n + 1)*sizeof(*bd_bal->date));
  bd_bal->cum_invest = malloc((bd->n + 1)*sizeof(*bd_bal->cum_invest));
  bd_bal = cal_bd(bd_bal, bd);

  ret_portfolio_t *cycle_bal = malloc(sizeof(*cycle_bal));
  cycle_bal->date = malloc((eq->n + 1)*sizeof(*cycle_bal->date));
  cycle_bal->cum_invest = malloc((eq->n + 1)*sizeof(*cycle_bal->cum_invest));
  cycle_bal = cal_cycle(cycle_bal, eq, bd);

  FILE *output = fopen("portfolio.csv", "w");
  if(output == NULL) {
    perror("could not open output");
    return EXIT_FAILURE;
  }

  write_output(n, eq_bal, bd_bal, cycle_bal, output);
  
  free_eq(eq);
  free_bd(bd);
  free_ret(eq_bal);
  free_ret(bd_bal);
  free_ret(cycle_bal);

  if(fclose(equities) != 0) {
    perror("could not close eq");
    return EXIT_FAILURE;
  }
  if(fclose(bonds) != 0) {
    perror("could not close bd");
    return EXIT_FAILURE;
  }
  if(fclose(output) != 0) {
    perror("could not close output");
    return EXIT_FAILURE;
  }

  
  return EXIT_SUCCESS;
}
  
