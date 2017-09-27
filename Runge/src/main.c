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
  double h = atof(argv[3]);
  double eps = atof(argv[4]);
  double y0 = 1;
  double tmph = h;
  double h1 = h/2;
  int n1;
  int n = (b - a) / h + 1;
  int iter = 0;
  int flg = 0;
  double hEiler, hRunge2;
  n = (b - a) / h + 1;
  double tmpy = y0;
  double tmpy1 = y0;
  
  printf("x:Eiler func: [%.4lf, %.12lf]\n", a, y0);
  do {
  n = (b - a) / h + 1;
  tmpy = y0;
  tmpy1 = y0;
  iter = 0;
  for (int i = 1; i < n; i++) {
    tmpy = tmpy + h * func( a + h*(i-1), tmpy);
    printf("1:Eiler func: [%.4lf, %.12lf][%lf], iter = %d\n", a + h*i, tmpy, h, ++iter);
  }
  iter = 0;
    printf("-----------------------------------\n");
  h1 = h/2;
  n1 = (b - a) / h1 + 1;
  for (int i = 1; i < n1; i++) {
    tmpy1 = tmpy1 + h1 * func( a + h1*(i-1), tmpy1);
    printf("2:Eiler func: [%.4lf, %.12lf][%lf], iter = %d\n", a + h1*i, tmpy1, h1, ++iter);
  }
  iter = 0;
    printf("-----------------------------------\n");
      double a1 = tmpy;
      double a2 = tmpy1;
      double b1 = a1 - a2;

      if (b1 < 0) {
        b1 = -b1;
      }
      printf("3:Eiler func: [%.12lf]\n",b1);
    printf("-----------------------------------\n");
      h = h / 2;
      if (b1 <= eps) break;
  } while (1);
  hEiler = h1;
		/*---------------------*/
  
  h = tmph;
  n = (b - a) / h + 1;
  tmpy = y0;
  tmpy1 = y0;
  double tmp;
  
  printf("x:Runge2 func: [%.4lf, %.12lf]\n", a, y0);
  do {
  n = (b - a) / h + 1;
  tmpy = y0;
  tmpy1 = y0;
  iter = 0;
  for (int i = 1; i < n; i++) {
    tmp = tmpy + h * func( a + h*(i-1), tmpy);
    tmpy = tmpy + (h / 2) * (func( a + h*(i-1), tmpy) + func( a + h*i, tmp));
    printf("1:Runge2 func: [%.4lf, %.12lf][%lf], iter = %d\n", a + h*i, tmpy, h, ++iter);
  }
    printf("-----------------------------------\n");
      double a1 = tmp;
      double a2 = tmpy;
      double b1 = a1 - a2;

      if (b1 < 0) {
        b1 = -b1;
      }
      printf("3:Runge2 func: [%.12lf]\n",b1);
    printf("-----------------------------------\n");
      h = h / 2;
      if (b1 <= eps) break;
  } while (1);
  hRunge2 = h1;
  
		/*---------------------*/
  printf("\n\n");
  tmpy = y0;
  tmpy1 = y0;
  h = tmph;
  printf("x:Runge4 func: [%.4lf, %.12lf]\n", a, y0);
  do {
  n = (b - a) / h + 1;
  tmpy = y0;
  tmpy1 = y0;
  for (int i = 1; i < n; i++) {
    double k1 = func(a + h*(i-1), tmpy);
    double k2 = func(a + h*(i-1) + h / 2, tmpy + h / 2 * k1);
    double k3 = func(a + h*(i-1) + h / 2, tmpy + h / 2 * k2);
    double k4 = func(a + h*(i-1) + h, tmpy + h * k3);
    tmpy = tmpy + h / 6 * (k1 + 2 * k2 + 2 * k3 + k4);
    printf("1:Runge4 func: [%.4lf, %.12lf][%lf]\n", a + h*i, tmpy, h);
  }
    printf("-----------------------------------\n");
  h1 = h/2;
  n1 = (b - a) / h1 + 1;
  for (int i = 1; i < n1; i++) {
    double k11 = func(a + h1*(i-1), tmpy1);
    double k21 = func(a + h1*(i-1) + h1 / 2, tmpy1 + h1 / 2 * k11);
    double k31 = func(a + h1*(i-1) + h1 / 2, tmpy1+ h1 / 2 * k21);
    double k41 = func(a + h1*(i-1) + h1, tmpy1 + h1 * k31);
    tmpy1 = tmpy1 + h1 / 6 * (k11 + 2 * k21 + 2 * k31 + k41);
    printf("2:Runge4 func: [%.4lf, %.12lf][%lf]\n", a + h1*i, tmpy1, h1);
  }
    printf("-----------------------------------\n");
      double a1 = tmpy;
      double a2 = tmpy1;
      double b1 = a1 - a2;

      if (b1 < 0) {
        b1 = -b1;
      }
      printf("3:Runge4 func: [%12lf]\n",b1);
    printf("-----------------------------------\n");
      h = h / 2;
      if (b1 <= eps) break;
  } while (1);
  
  printf("--------------ANSWER---------------\n\n");
  
  iter = 0;
  tmpy1 = y0;
  n1 = (b - a) / hEiler + 1;
  printf("x:Eiler func: [%.4lf, %.12lf]\n", a, y0);
  for (int i = 1; i < n1; i++) {
    tmpy1 = tmpy1 + hEiler * func( a + hEiler*(i-1), tmpy1);
    printf("4:Eiler func: [%.4lf, %.12lf][%lf], iter = %d\n", a + hEiler*i, tmpy1, hEiler, ++iter);
  }
    printf("-----------------------------------\n\n");
  iter = 0;
  tmpy1 = y0;
  n1 = (b - a) /hRunge2 + 1;
  printf("x:Runge2 func: [%.4lf, %.12lf]\n", a, y0);
  for (int i = 1; i < n1; i++) {
    tmpy1 = tmpy1 + hRunge2 * func( a +hRunge2*(i-1), tmpy1);
    printf("4:Runge2 func: [%.4lf, %.12lf][%lf], iter = %d\n", a + hRunge2*i, tmpy1, hRunge2, ++iter);
  }
    printf("-----------------------------------\n\n");
  printf("x:Runge4 func: [%.4lf, %.12lf]\n", a, y0);
  tmpy1 = y0;
  n1 = (b - a) / h1 + 1;
  for (int i = 1; i < n1; i++) {
    double k11 = func(a + h1*(i-1), tmpy1);
    double k21 = func(a + h1*(i-1) + h1 / 2, tmpy1 + h1 / 2 * k11);
    double k31 = func(a + h1*(i-1) + h1 / 2, tmpy1+ h1 / 2 * k21);
    double k41 = func(a + h1*(i-1) + h1, tmpy1 + h1 * k31);
    tmpy1 = tmpy1 + h1 / 6 * (k11 + 2 * k21 + 2 * k31 + k41);
    printf("4:Runge4 func: [%.4lf, %.12lf][%lf]\n", a + h1*i, tmpy1, h1);
  }
  return 0;
}
