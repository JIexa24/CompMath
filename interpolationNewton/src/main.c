#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

int h;
int a;
int b;

double func(double x)
{
  return (x * x * x + 1);
}

double factorial(double value)
{
  int result = 1;
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
  printf("P(x) = %.2f\t", result);
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
  printf("\n\nh = %d", h);

}

int main(int argc, char** argv) {
  assert(!(argc < 4));
  a = atoi(argv[1]);
  b = atoi(argv[2]);
  h = atoi(argv[3]);
  int ctr = ((b - a) / h) + 1;

  double* xVal = (double *)malloc(sizeof(double) * ctr);
  double* yVal = (double *)malloc(sizeof(double) * ctr);
  createPrintTable(xVal, yVal,  ctr);


  printf("\n");
  printf("ctr = %d\n\n", ctr);

  double x = xVal[0];
  int flg = 0;
  for (int i = xVal[0]; i < xVal[ctr - 1]; i++) {
    x += 1;
    flg = 0;
    for (int j = 0; j < ctr; j++) {
      if (xVal[j] == x) {
        flg = 1;
        break;
      }
    }
    if (flg) {
      continue;
    }
    printf("x = %.2lf ", x);

    interpolation(xVal, yVal, ctr, x);

    printf("f(x) = %.2lf\n", func(x));
  }

  return 0;
}


