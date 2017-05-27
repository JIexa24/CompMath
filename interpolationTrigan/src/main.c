#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>

double h;
double a;
double b;
int cnt;
double e = 0.1;

const double PI = 3.14159265358979323846;
double *xVal = NULL, *yVal = NULL;

double func(double x)
{
  return -2 * cos(x) * cos(x);
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
  printf("\n\nh = %lf\n", h);

}

double interpolate(double x, double *xVal, double *yVal)
{
  int i       = 0;
  int j       = 1;
  double ret  = 0;
  double tmpret = 0;
  double bn = 0;
  double an = 0;
  double aZero = 0;
  for (i = 0; i < cnt; i++) {
    aZero= aZero + yVal[i];
  }

  aZero = aZero /(cnt);
  tmpret = aZero;
  do {
    bn = 0;
    an = 0;
    ret = tmpret;
    for (i = 0; i < cnt; i++) {
      an = an + yVal[i]*cos(j*xVal[i]);
    }
    an = 2*an / cnt;
    for (i = 0; i < cnt; i++) {
      bn = bn + yVal[i]*sin(j*xVal[i]);
    }
    bn = 2*bn / cnt;
    tmpret = tmpret + an*cos(j*x) + bn*sin(j*x);
    ++j;
  //  printf("\n%lf %lf %d %lf %lf\n", tmpret, ret, j,((tmpret >= ret)?(tmpret -ret) : (ret - tmpret)), e);
   //if (((tmpret >= ret)?(tmpret -ret) : (ret - tmpret)) <= e & tmpret <= 1) break;
} while (j < 3);
  return tmpret;
}

int main(int argc, char** argv)
{
  assert(!(argc < 4));

  a = atof(argv[1]);
  b = atof(argv[2]);
  h = atof(argv[3]);
  
  double eps1 = 0;
  double eps2 = 0;

  cnt = ((b - a) / h);

  xVal = (double*) malloc(sizeof(double) * cnt);
  yVal = (double*) malloc(sizeof(double) * cnt);
  createPrintTable(xVal, yVal,  cnt);

  for (int i = 0; i < 2*cnt - 1; i++) {
    double x = a + h / 2 * i;
    printf("x = %.2lf\t", x);
    printf("T(x) = %lf\t", eps1 = interpolate(x, xVal, yVal));
    printf("func(x) = %lf \n",func(x));
    eps1 = func(x) - eps1;
    eps2 += eps1;
  }
  eps2 /= (2 * cnt - 1);
  printf("\n\n%lf\n", eps2);
	return 0;
}
