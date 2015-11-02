#include <stdio.h>
#include <math.h>

/*解を算出し出力する関数*/
double answer(double a1,double b1, double c1){
  
	double x1, x2,d;
	d = b1 * b1 - 4 * a1 * c1;	/*判別式*/

	if ( d > 0.0 ){
		x1 = ( -b1 + sqrt(d)) / ( 2 * a1);
		x2 = ( -b1 - sqrt(d)) / ( 2 * a1);
		printf("二次方程式の解は実数解で、%lf, %lfです。\n", x1, x2);
	}
	else if ( d < 0.0 ){
		x1 = -b1 / ( 2 * a1 );
		x2 = sqrt(-d) / ( 2 * a1 );
		printf("二次方程式の解は虚数解で、%lf+%lfi, %lf-%lfiです。\n", x1, x2, x1, x2);
	}
	else{
		x1 = -b1 / ( 2 * a1 );
		printf("二次方程式の解は重解で、%lfです。\n", x1);
	}
}

int main(void){
	double a, b, c;
	a = 6;
	b = 4;
	c = 3;
	printf("二次関数の解を求めます。\n");
	answer(a,b,c);			/*解を算出し出力*/
}
