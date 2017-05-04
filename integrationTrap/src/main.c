#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <inttypes.h>
#include <assert.h>

double func(double x)
{
  return -(x*x) + 4;
}

int main(int argc, char **argv)
{
  assert(!(argc < 4));
  double a = atof(argv[1]);
  double b = atof(argv[2]);
  int n = atoi(argv[3]);
  printf("Integration: [%f, %f], n = %d\n", a, b, n);
  double h = (b - a) / n;
  double s = 0.0;

  for (int i = 0; i < n; i++)
  {
      s +=((func(a + h * (i)) + func(a + h * (i + 1))) / 2) * h;
  }

  printf("a = %.12lf\n", a);
  printf("b = %.12lf\n", b);
  printf("st = %.12lf\n", h);
  printf("S = %.12lf\n", s);
  return 0;
}
