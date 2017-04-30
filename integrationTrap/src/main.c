#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <inttypes.h>

double func(double x)
{
  return x;
}

int main(int argc, char **argv)
{

  double a = atof(argv[1]);
  double b = atof(argv[2]);
  int n = 10;
  printf("Integration: [%f, %f], n = %d\n", a, b, n);
  double h = (b - a) / n;
  double s = 0.0;

  for (int i = 0; i < n; i++)
  {
      s +=((func(a + h * (i)) + func(a + h * (i + 1))) / 2) * h;
  }

  printf("a = %lf\n", a);
  printf("b = %lf\n", b);
  printf("st = %lf\n", h);
  printf("S = %lf\n", s);
  return 0;
}
