#include <stdio.h>
#include <math.h>

#include "../inc/simpson.h"

double func(double x){
  return sqrt(x);
}

int main(void){

  int i;

  for (i = 1 ; i < 1.0E+06 ; i *= 2){
    printf("n = %8d \t", i );
    printf("Daikei  : %.15lf \t",  Daikei(i, 1.0 , 1.3));
    printf("Simpson : %.15lf \n", Simpson(i, 1.0 , 1.3));
  }
  return 0;
}
