#include <stdio.h>
#include <math.h>

#define Sol 0.321485368419253

double Daikei(int n, double Xin, double Xen);
double Simpson(int n, double Xin, double Xen);

double func(double x){
  return sqrt(x);
}

int main(void){

  int i;

  for (i = 2 ; i < 2048 ; i = i * 2){
    printf("n = %5d (Result) \t Daikei : %.15lf \t Simpson : %.15lf \n", i, Daikei(i, 1.0, 1.3), Simpson(i, 1.0 , 1.3));
    printf("n = %5d (Errors) \t Daikei : %.11E \t Simpson : %.11E \n\n", i, fabs(Sol - Daikei(i, 1.0, 1.3)), fabs(Sol - Simpson(i, 1.0 , 1.3)));
  }
  return 0;
}

/* Function of Simpson's Rule and Daikei Method */

double Simpson(int n, double Xin, double Xen){

  double S, h, X;
  int i;

  S = 0;

  h = (Xen - Xin) / ( 2.0 * (double) n );

  for (i = 0; i < n ; i++){
    X = Xin + 2.0 * i * h ;
    S += ( func(X) + 4.0 * func( X + 1.0 * h ) + func( X + 2.0 * h ) ) * h / 3.0;
  }
  return S;
}

double Daikei(int n, double Xin, double Xen){

  double S, h, X;
  int i;

  S = 0;

  h = (Xen - Xin) / (double) n;

  for (i = 0 ; i < n ; i ++){
    X = Xin + i * h ;
    S += (func(X) + func (X + 1.0 * h)) * h / 2.0;
  }

  return S;
}
