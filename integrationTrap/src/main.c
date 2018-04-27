#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <inttypes.h>
#include <assert.h>

double s = 1;

double func(double x)
{
  return x*x;
}

int main(int argc, char **argv)
{
  //assert(!(argc < 5));
  double a = atof(argv[1]);
  double b = atof(argv[2]);
  int n = atoi(argv[3]);
  double eps = atof(argv[4]);
  double h = 0.5;

  printf("h = %lf eps = %lf\n", h, eps);
  printf("\nIntegration: [%lf, %lf]\n", a, b);

  double tmph = h;
  h = h * 2;
  double tmps = s;
  int iter = 0;

  do {
    h = h / 2;
    tmps = s;
    s = 0;
    for (int i = 0; a + h*i <= b; i++) {
      s += ((func(a + h * (i)) + func(a + h * (i + 1))) / 2) * h;
    }
    iter++;
  } while ((s > tmps) ? (s - tmps) : (tmps - s)> eps);

  printf("a = %.12lf\n", a);
  printf("b = %.12lf\n", b);
  printf("st = %.12lf\n", h);
  printf("S = %.12lf\nit = %d\n", s, iter);

  printf("\nIntegration: [%lf, %lf]\n", a, b);
  iter = 0;
  h = tmph;
  h = h * 2;
  s = 1;
  tmps = 1;

  do {
    h = h / 2;
    tmps = s;
    s = 0;
    for (int i = 1; a + h*i <= b - h; i++) {
      double tmp = func(a + h*i);
      tmp = tmp * (i % 2 ? 4 : 2);
      s += tmp;
    }
    s = s + func(a) + func(b);
    s = s * h / 3;
    iter++;
  } while ((s > tmps) ? (s - tmps) : (tmps - s)> eps);

  printf("\na = %.12lf\n", a);
  printf("b = %.12lf\n", b);
  printf("st = %.12lf\n", h);
  printf("S = %.12lf\nit = %d\n", s, iter);
  return 0;
}
