#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>

double h;
double a;
double b;
double cnt;
double e = 0.1;

double *xVal = NULL, *yVal = NULL;

double func(double x)
{
  return sin(x);
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
  int j       = 1;
  double ret  = 0;
  double tmpret = 0;
  double b = 0;
  double a = 0;
  double aZero = 0;
  for (i = 0; i < cnt; i++) {
    aZero= aZero + yVal[i];
  }

  aZero = aZero /(cnt);
  tmpret = aZero;
  do {
    b = 0;
    a = 0;
    ret = tmpret;
    for (i = 0; i < cnt; i++) {
      a = a + yVal[i]*cos(j*xVal[i]);
    }
    a = 2*a / cnt;
    for (i = 0; i < cnt; i++) {
      b = b + yVal[i]*sin(j*xVal[i]);
    }
    b = 2*b / cnt;
    tmpret = tmpret + a*cos(j*x) + b*sin(j*x);
    ++j;
  //  printf("\n%lf %lf %d %lf %lf\n", tmpret, ret, j,((tmpret >= ret)?(tmpret -ret) : (ret - tmpret)), e);
   //if (((tmpret >= ret)?(tmpret -ret) : (ret - tmpret)) <= e & tmpret <= 1) break;
} while (j < cnt);
  return tmpret;
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
  printf("cnt = %lf", cnt);
  printf("\n");

  for (int i = 0; i < 2*cnt - 1; i++) {
    double x = a + h / 2 * i;
    printf("x = %.2lf\t", x);
    printf("T(x) = %lf\t", interpolate(x, xVal, yVal));
    printf("func(x) = %lf \n", func(x));
  }
	return 0;
}
