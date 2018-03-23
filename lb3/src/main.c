#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>

double a, b, c = 0;
double e = 0.01;

double f(double x)
{
  return sin(x);
}

double f1(double x)
{
  return cos(x);
}

void bisec()
{
  assert(f(a) * f(b) < 0);

  long int i;
  for (i = 0; fabs(b - a) > e; i++) {
    c = (a + b) / 2;
    if (f(a) * f(c) < 0)
      b = c;
    else
      a = c;
  }
  printf("bisec steps: %ld\n", i);
}

void hord()
{
  double tmp = 0;
  long int i;
  double flg = 0;
  for (i = 0; (fabs(c - tmp) > e || !flg); i++) {
    flg++;
    tmp = c;
    c = a - f(a) * (b - a) / (f(b) - f(a));
    if (f(a) * f(c) < 0)
      b = c;
    else
      a = c;
  }
  printf("hord steps: %ld\n", i);
}

void newtoon()
{
  double tmp = a;
  long int j;
  c = (-1) * (f(tmp) / f1(tmp)) + tmp;
  for (j = 0; f(c) != 0 && fabs(c - tmp) > e; j++) {
    tmp = c;
    c = tmp - (f(tmp) / f1(tmp));
  }
  printf("newtoon steps: %ld\n", j);
}

int main(int argc, char **argv)
{
  assert(!(argc < 3));
  FILE* dat = fopen("metod.txt", "r");
  int d[3];
  a = atof(argv[1]);
  b = atof(argv[2]);
  int i = 0;
  for (i = 0; i < 3; i++) {
    fscanf(dat, "%d", &d[i]);
  }

  double tmpa = a;
  double tmpb = b;
  if (d[0]) {
    bisec();
    printf("answ: %.2lf\n", c);
    c = 0;
    a = tmpa;
    b = tmpb;
  }

  if (d[1]) {
    hord();
    printf("answ: %.2lf\n", c);
    c = 0;
    a = tmpa;
    b = tmpb;
  }

  if (d[2]) {
    newtoon();
    printf("answ: %.2lf\n", c);
  }

    return 0;
}
