#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

double h;
double a;
double b;

double func(double x)
{
  return (1/x);
}

double factorial(double value)
{
  double result = 1;
  for (int i = 1; i < value; i++)
    result *= (i + 1);
  return result;
}

double interpolation(double *x, double *y, int ctr, double X)
{
  double result = y[0];
  double ys[ctr];

  for (int i = 0; i < ctr; i++)
    ys[i] = y[i];
  for (int i = ctr - 1, j = 0; i > 0; i--, j++) {
    for (int k = 0; k < i; k++) {
      ys[k] = ys[k + 1] - ys[k];
    }

    double q = (X - x[0]) / h;
    double tmp = q;

    for (int k = 1; k <= j; k++)
      tmp *= (q - k);

    q = tmp;
    result+= ys[0] / factorial(j + 1) * q;
  }
  printf("P(x) = %f\t", result);
  return result;
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

int main(int argc, char** argv)
{
  assert(!(argc < 4));
  a = atof(argv[1]);
  b = atof(argv[2]);
  h = atof(argv[3]);
  int ctr = ((b - a) / h) + 1;

  double* xVal = (double *)malloc(sizeof(double) * ctr);
  double* yVal = (double *)malloc(sizeof(double) * ctr);
  createPrintTable(xVal, yVal,  ctr);


  printf("\n");
  printf("ctr = %d\n\n", ctr);

  double x = xVal[0];
  int flg = 0;
  for (int i = 0; i < 2*ctr - 1; i++) {
    double x = a + h / 2 * i;
    if (i % 2 == 0)
      printf("Tabl: ");
    printf("x = %lf \t", x);

    interpolation(xVal, yVal, ctr, x);

    printf("f(x) = %lf\n", func(x));
  }

  return 0;
}
