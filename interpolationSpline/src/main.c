#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>

double h;
double a;
double b;
int cnt;

double *xVal = NULL, *yVal = NULL;

double func(double x)
{
  return x*x - x;
}
double hcoff(int ind)
{
  return xVal[ind] - xVal[ind-1];
}
double ccoff(int ind)
{
  if (ind%3 == 0 | ind%3 == 2)
    return 0;

  double ret = 6 * ((func(xVal[ind+1]) - func(xVal[ind]))/(hcoff(ind+1)) -
               (func(xVal[ind]) - func(xVal[ind-1]))/(hcoff(ind)));
  ret = ret - hcoff(ind+1)*ccoff(ind+1);
  ret = ret - hcoff(ind)*ccoff(ind-1);
  ret = ret/(2*(hcoff(ind+1) + hcoff(ind)));
  return ret;
}
double dcoff(int ind)
{
  double ret = ccoff(ind) - ccoff(ind -1);
  ret = ret / hcoff(ind);
  return ret;
}
double bcoff(int ind)
{
  double ret = 0;
  ret = (func(xVal[ind]) - func(xVal[ind-1]))/(hcoff(ind));
  ret = ret + ((hcoff(ind)) * (2 * ccoff(ind) + ccoff(ind - 1))) / 6;
  return ret;
}
void createPrintTable(double *x, double *y, int ctr)
{
  printf("x\t");

  for (int i = 0; i < ctr; i++) {
    x[i] = i * h + a;
    printf("%.2lf\t", x[i]);
  }

  printf("\ny\t");

  for (int i = 0; i < ctr; i++) {
    y[i] = func(x[i]);
    printf("%.2lf\t", y[i]);
  }
  printf("\n\nh = %lf", h);

}

double interpolate(double x, double *xVal, double *yVal)
{
  int i       = 0;
  int ind     = 1;
  double ret  = 0;
  double hloc = 0;
  for (i = 0; i < cnt - 1; i++) {
    if (x >= xVal[i] & x <= xVal[i+1])
    {
      ind = i + 1;
      break;
    }
  }
//  printf("\nfirst ind %d %lf = %lf\n", ind, xVal[ind], x);
  hloc = xVal[ind] - xVal[ind - 1];
  ret = ret + func(xVal[ind]);
  ret = ret + bcoff(ind) * (x - xVal[ind]);
  ret = ret + ccoff(ind) * (x - xVal[ind]) * (x - xVal[ind]) / 2;
  ret = ret + dcoff(ind) * (x - xVal[ind]) * (x - xVal[ind]) * (x - xVal[ind]) / 6;
  return ret;
}

int main(int argc, char** argv)
{
  assert(!(argc < 4));

  a = atof(argv[1]);
  b = atof(argv[2]);
  h = atof(argv[3]);

  cnt = ((b - a) / h) + 1;
  xVal = (double*) malloc(sizeof(double) * cnt);
  yVal = (double*) malloc(sizeof(double) * cnt);
    createPrintTable(xVal, yVal,  cnt);
  printf("\n");

  for (int i = 0; i < 2*cnt - 1; i++) {
    double x = a + h / 2 * i;
    printf("x = %.2lf\t", x);
    printf("S(x) = %lf\t", interpolate(x, xVal, yVal));
    printf("func(x) = %lf\n", func(x));
  }
	return 0;
}
