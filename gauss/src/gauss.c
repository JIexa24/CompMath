#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define N 20


void glavelem( int k, double mas[] [N + 1], int n, int otv[] );

int main( void )
{
  double mas[N] [N + 1];
  double x[N]; //Корни системы
  int otv[N]; //Отвечает за порядок корней
  int i, j, k, n;
  //Ввод данных
  //clrscr();
  do
  {
    printf( "Введите число уравнений системы: " );
    scanf( "%d", & n );
    if ( N < n )
      printf( "Слишком большое число уравнений. Повторите ввод\n" );
  }
  while ( N < n );
/*
  printf( "Введите систему:\n" );
  for ( i = 0; i < n; i++ )
    for ( j = 0; j < n + 1; j++ )
      scanf( "%lf", & mas[i] [j] );
  */
  FILE *f = fopen("matrix.txt", "r");
    for(i = 0; i < n; i++){
        for(j = 0; j < n+1; j++){
            fscanf(f,"%lf", &mas[i][j]);
        }
    }
  //Вывод введенной системы
  //clrscr();
  printf( "Система:\n" );
  for ( i = 0; i < n; i++ )
  {
    for ( j = 0; j < n + 1; j++ )
      printf( "%7.2f ", mas[i] [j] );
    printf( "\n" );
  }
  //Сначала все корни по порядку
  for ( i = 0; i < n + 1; i++ )
    otv[i] = i;
  //Прямой ход метода Гаусса
  for ( k = 0; k < n; k++ )
  { //На какой позиции должен стоять главный элемент
    glavelem( k, mas, n, otv ); //Установка главного элемента
    if ( fabs( mas[k] [k] ) < 0.0001 )
    {
      printf( "Система не имеет единственного решения\n" );
      return ( 0 );
    }
    printf("Обнуление столбца %d\n", k);
    printf("Деление строки %d на %lf\n", k, mas[k][k]);
    for ( j = n; j >= k; j-- )
      mas[k] [j] /= mas[k] [k];
    for ( i = k + 1; i < n; i++ ) {
    printf("Вычитание строки %d из %d\n", k, i);
      for ( j = n; j >= k; j-- ){
        printf("%.2lf - %.2lf * %.2lf = %.2lf\n",mas[i] [j] , mas[k] [j] , mas[i] [k], mas[i] [j] - mas[k] [j] * mas[i] [k]);
        mas[i] [j] -= mas[k] [j] * mas[i] [k];
      }
    }
  }

  printf( "Система:\n" );
  for ( i = 0; i < n; i++ )
  {
    for ( j = 0; j < n + 1; j++ )
      printf( "%7.2f ", mas[i] [j] );
    printf( "\n" );
  }
  //Обратный ход
  for ( i = 0; i < n; i++ )
    x[i] = mas[i] [n];
  for ( i = n - 2; i >= 0; i-- )
    for ( j = i + 1; j < n; j++ )
      x[i] -= x[j] * mas[i] [j];
  //Вывод результата
  printf( "Ответ:\n" );
  for ( i = 0; i < n; i++ )
    for ( j = 0; j < n; j++ )
      if ( i == otv[j] )
      { //Расставляем корни по порядку
        printf( "%f\n", x[j] );
        break;
      }
  return ( 0 );
}
//----------------------------------------------
//Описание  функции
//----------------------------------------------
void glavelem( int k, double mas[] [N + 1], int n, int otv[] )
{
  int i, j, i_max = k, j_max = k, f, e;
  double temp;
  //Ищем максимальный по модулю элемент
  for ( i = k; i < n; i++ )
    for ( j = k; j < n; j++ )
      if ( fabs( mas[i_max] [j_max] ) < fabs( mas[i] [j] ) )
      {
        i_max = i;
        j_max = j;
      }
  //Переставляем строки
  printf("установка главного элемента столбца %lf(%d) на строку %d\n",mas[i_max][j_max],i_max,k);
  for ( j = k; j < n + 1; j++ )
  {
    temp = mas[k] [j];
    mas[k] [j] = mas[i_max] [j];
    mas[i_max] [j] = temp;
  }
  printf( "Системаstr:\n" );
  for ( f = 0; f < n; f++ )
  {
    for ( e = 0; e < n + 1; e++ )
      printf( "%7.2f ", mas[f][e] );
    printf( "\n" );
  }

  //Учитываем изменение порядка корней
  i = otv[k];
  otv[k] = otv[j_max];
  otv[j_max] = i;
}
