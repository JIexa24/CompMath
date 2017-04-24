#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>

double h;
double a;
double b;
int cnt;

double func(double x)
{
  return x * x * x;
}

double interpolation(double *x,double *y, double X, int ctr)
{
  double res = 0;

  int c;
  double tmp = 1;
/*
  for (int i = 0; i < ctr; i++) {
    tmp = 1;
    for (int j = 0; j < ctr; j++) {
      if (!(i == j)) {
        tmp *= (X - x[j]) / (x[i] - x[j]);
      }
    }
    res += tmp * func(X);
    if (i < 4)
    printf("L%d(x) = %.6lf\t", i , res);
    //printf("\n");
  }*/
  int ind = 0;
  for (int i = 0; i < ctr - 1; i++) {
    if (X < x[i + 1] && X >= x[i])
      ind = i;
  }
  if (X == x[ctr - 1])ind = ctr - 1;
  int cti = 0;
  int ctj = 0;
  for (int i = ind; cti < 3 && ind < ctr  - 2; i++) {
    tmp = 1;
    for (int j = ind; ctj < 3 && ind < ctr - 2; j++) {
      if (!(i == j)) {
        tmp *= (X - x[j]) / (x[i] - x[j]);
      }ctj++;
    }
    res += tmp * func(X);

    printf("L%d(x) = %.6lf\t", cti , res);
    //printf("\n");
    cti++;ctj = 0;
  }
  return res;
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

int main(int argc, char** argv) {
  assert(!(argc < 4));

  a = atof(argv[1]);
  b = atof(argv[2]);
  h = atof(argv[3]);

  int ctr = ((b - a) / h) + 1;
  cnt = ctr - 1;

  double* xVal = (double *)malloc(sizeof(double) * ctr);
  double* yVal = (double *)malloc(sizeof(double) * ctr);

  createPrintTable(xVal, yVal,  ctr);


  printf("\n");
  printf("ctr = %d\n\n", ctr);
  printf("cnt = %d\n\n", cnt);
  printf("\n");

  double x = xVal[0] - h/2;
  int flg = 0;
  for (int i = 0; i < ctr,x < xVal[ctr - 1]; i++) {
    x += h/2;
    flg = 0;
   /* for (int j = 0; j < ctr; j++) {
      if (xVal[j] == x) {
        flg = 1;
         break;
      }
    }
    if (flg) {
      continue;
    }*/
    printf("\n\nx = %.2lf\t", x);
    interpolation(xVal,yVal, x, ctr);
    printf("f(x) = %.2lf\n", func(x));
  }

  return 0;
}


