#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <inttypes.h>
#include <assert.h>

double func(double x, double y)
{
  return exp(x);
}

int main(int argc, char **argv)
{
  assert(!(argc < 4));
  double a = atof(argv[1]);
  double b = atof(argv[2]);
  int h = atoi(argv[3]);
  double eps = atof(argv[4]);

  int n = (b - a) / h + 1;
  printf("n = %d\n", n);
  double* xVal = (double *)malloc(sizeof(double) * n);
  double* yVal = (double *)malloc(sizeof(double) * n);
  double* yVal1 = (double *)malloc(sizeof(double) * n);
  for (int i = 0; i < n; i++) {
    xVal[i] = a + h*i;
  }
  yVal[0] = 1;
  yVal1[0] = yVal[0];
  int iter = 0;
  int flg = 0;

  printf("Eiler func: [%lf, %lf], iter = -\n", xVal[0], yVal[0]);
  for (int i = 1; i < n; i++) {
    yVal[i] = yVal[i - 1] + h * func(xVal[i - 1], yVal[i - 1]);
  }
  for (int i = 1; i < n; i++) {
    printf("Eiler func: [%lf, %lf], iter = -\n", xVal[i], yVal[i]);
  }
  for (int i = 1; i < n; i++) {
    iter = 0;
    yVal1[i] = yVal[i - 1] + h * func(xVal[i - 1], yVal[i - 1]);

    do {
      if (iter > 0) {
        yVal1[i] = yVal[i];
      }
      yVal[i] = yVal[i - 1] + (h*((func(xVal[i - 1], yVal[i - 1]) + func(xVal[i], yVal1[i])) / 2));
      iter++;
      double a = yVal[i];
      double a1 = yVal1[i];
      double b = a - a1;

      if (b < 0) {
        b = -b;
      }
      if (b <= eps) break;
    } while (b > eps);
    printf("Eiler func: [%lf, %lf], iter = %d\n", xVal[i], yVal[i], iter);
  }

	//	for (int i = 0; i < n; i++) {
		//	printf("Eiler func: [%lf, %lf]\n", xVal[i], yVal[i]);
	//	}
		/*---------------------*/
  for (int i = 0; i < n-1; i++) {
    double k1 = func(xVal[i], yVal[i]);
    double k2 = func(xVal[i] + h / 2, yVal[i] + h / 2 * k1);
    double k3 = func(xVal[i] + h / 2, yVal[i] + h / 2 * k2);
    double k4 = func(xVal[i] + h, yVal[i] + h * k3);
    yVal[i + 1] = yVal[i] + h / 6 * (k1 + 2 * k2 + 2 * k3 + k4);
  }

  printf("\n\n");
  for (int i = 0; i < n; i++) {
    printf("Runge4 func: [%lf, %lf]\n", xVal[i], yVal[i]);
  }
  return 0;
}
