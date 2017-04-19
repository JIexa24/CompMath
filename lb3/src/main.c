#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>

double a, b, c = 0;
double e = 0.001;
double intrvl = 0.5;

double f(double x)
{
  return x * x - 4;
}

double f1(double x)
{
  return 2 * x;
}

void bisec()
{
  assert(f(a) * f(b) < 0);

  int i;
  for (i = 0; fabs(b - a) > e && f(c) != 0; i++) {
    c = (a + b) / 2;
    if (f(a) * f(c) < 0)
      b = c;
    else
      a = c;
  }
  printf("bisec steps: %d\n", i);
}

void hord()
{
  double tmp = 0;
  int i, flg = 0;
  for (i = 0; (fabs(c - tmp) > e || !flg) && f(c) != 0; i++) {
    flg++;
    tmp = c;
    c = a - f(a) * (b - a) / (f(b) - f(a));
    if (f(a) * f(c) < 0)
      b = c;
    else
      a = c;
  } 
  printf("hord steps: %d\n", i);
}

void newtoon()
{
  double tmp = a;
  int j;
  c = (-1) * (f(tmp) / f1(tmp)) + tmp;
  for (j = 0; f(c) != 0 && fabs(c - tmp) > e; j++) {
    tmp = c;
     c = tmp - (f(tmp) / f1(tmp));
  } 
  printf("newtoon steps: %d\n", j);
}

int main(int argc, char **argv)
{
  assert(!(argc < 3));
  FILE* dat = fopen("metod.txt", "r");
  int d[3];
  a = atoi(argv[1]);
  b = atoi(argv[2]);
  int i = 0;
  for (i = 0; i < 3; i++) {
    fscanf(dat, "%d", &d[i]);
  }

  int tmpa = a;
  int tmpb = b;
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
