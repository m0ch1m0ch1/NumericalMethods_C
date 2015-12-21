
double func(double x);

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
