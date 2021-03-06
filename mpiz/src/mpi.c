#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void read_matrix(int n, double **matr, FILE *f); 
void print_matrix(int n, double **matr); 
void iteration(int n, double **matr);

int main()
{
  FILE *f ;
  f = fopen("matrix.txt", "r");
  
  int n;
  fscanf(f,"%d", &n);

  int i;

  double **mas = (double **)malloc(n*sizeof(double *));
  for(i = 0; i < n; i++) {
    mas[i] = (double *)malloc((n+1)*sizeof(double));
  }

  read_matrix(n, mas, f);
  print_matrix(n, mas);
    
  iteration(n, mas);

  fclose(f);
  return 0;
}

void read_matrix(int n, double **matr, FILE *f){
  int i, j;
  for(i = 0; i < n; i++){
    for(j = 0; j < n+1; j++){
      fscanf(f,"%lf", &matr[i][j]);
    }
  }
}

void print_matrix(int n, double **matr){
    int i, j;
  for(i = 0; i < n; i++){
    for(j = 0; j < n+1; j++){
      printf("%.5lf\t", matr[i][j]);
    }
    printf("\n");
  }
  printf("*************\n");
}

void iteration(int n, double **matr){
  int i, j, k = 0, f;
  double temp, sum = 0;
  double x[n];
  double t[n];
  double p[n];
  double tmp;
  float kf;
    
  
		// проверка на диагональное преобладание
  for (i = 0; i < n; i++ ) {
    for(j = 0; j < n; j++){
      sum += matr[i][j];
    }
    sum -= matr[i][i];
    if (matr[i][i] < sum){
      printf("ERROR in %d str", i);
      exit(1);
    }
    sum = 0;
  }

  print_matrix(n, matr);
  for (i = 0; i < n; i++ ) {
    temp = matr[i][i];
    for(j = 0; j < n + 1; j++){
      if(temp != 0)
        matr[i][j] /= temp;			
    }
  }
	
  for (i = 0; i < n; i++ ) {
    for(j = 0; j < n + 1; j++){
      matr[i][i] = 0;
      x[i] = 0;
      t[i] = 0;	
      p[i] = 0;	
    }
  }

  k = 0;
  f = 0;

  while(1){

  f = 0;

  for (i = 0; i < n; i++ ) {
    for(j = 0; j < n ; j++){
      t[i] = t[i] - matr[i][j] * x[j];
    }
  }
		
  for (i = 0; i < n; i++ ) {
    if(fabs(t[i] - x[i] + matr[i][n]) <= 0.001) {
      f++;
    }
    x[i] = t[i] + matr[i][n];
    t[i] = 0;
  }
  printf("\n******iter = %d*********\n", k);
  for(i = 0; i < n; i++) {
    printf("x%d = %.5lf\t", i+1, x[i]);
  }

  k++;  
  if (f == n) break;	
  }
	
  printf("\nSolution:\n");
  printf("******************\n");

  for(i = 0; i < n; i++)
    printf("x%d = %.5lf\t", i+1, x[i]);

  printf("\nCount iteration = %d",k);	
  printf("\n******************\n");		
		
}
