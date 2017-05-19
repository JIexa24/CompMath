#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <assert.h>

double a = 0.6; //начало интервала
double b = 1.21; //конец
double h = 0.2; //длина интервала

double *xVal = NULL;
double *yVal = NULL;

double func(double x)
{
    return sqrt(x);
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
  printf("\n\nh = %.2lf", h);

}
double eitken(int n, int m, double x)
{
    if (m == n)
        return yVal[n];
    return ((x - xVal[n]) * eitken(n + 1, m, x) -
            (x - xVal[m]) * eitken(n, m - 1, x)) /
            (xVal[m] - xVal[n]);
}

int main(int argc, char** argv)
{
  assert(!(argc < 4));
  a = atof(argv[1]);
  b = atof(argv[2]);
  h = atof(argv[3]);
  int ctr = ((b - a) / h) + 1;

  xVal = (double *)malloc(sizeof(double) * ctr);
  yVal = (double *)malloc(sizeof(double) * ctr);
  createPrintTable(xVal, yVal,  ctr);

  printf("\n");
  printf("%d\n", ctr);
  for (int i = 0; i < ctr * 2 - 1; i++) {
    double x = a + h / 2 * i;
    if (i % 2 == 0)
      printf("Tabl: ");
    printf("x = %.2lf\t", x);
    double answ = eitken(0, ctr - 1, x);
    printf("p(x) = %.2lf\t f(x) = %.2lf\n", answ, func(x));
  }
  return 0;
}
