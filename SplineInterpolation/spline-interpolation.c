#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#define N 11 //---Interporation Number

int main(void){

	int i,k,j;
	int count;
	double  New_x;
	double  New_y;
	double	x[N], y[N];
	double	dx[N];
	double	c1[N], c2[N+1], c3[N], c4[N];
	double	Matrix[N+1][N+1];
	double	Y[N+1];
	double	sigma;

	x[0]  = +  0.0;
	x[1]  = +  1.0;
	x[2]  = +  2.0;
	x[3]  = +  3.0;
	x[4]  = +  4.0;
	x[5]  = +  5.0;
	x[6]  = +  6.0;
	x[7]  = +  7.0;
	x[8]  = +  8.0;
	x[9]  = +  9.0;
	x[10] = + 10.0;

	y[0]  = + 11.0;
	y[1]  = + 12.0;
	y[2]  = + 10.0;
	y[3]  = + 13.0;
	y[4]  = + 16.0;
	y[5]  = + 12.0;
	y[6]  = +  9.0;
	y[7]  = + 10.0;
	y[8]  = +  7.0;
	y[9]  = +  5.0;
	y[10] = +  7.0;

	for (i=1;i<N;i++){
		dx[i] = + x[i] - x[i-1];
		c1[i] = + y[i-1];
	}

	Matrix[1][1] = 2.0 * dx[1]; //---alpha_1
	Matrix[1][2] = 1.0 * dx[1]; //---r_1
	Y[1] = 3 * ( y[1] - y[0]);  //---Y_1

	for (i=2;i<N;i++){
		Matrix[i][i] = 2.0 * (dx[i]+dx[i-1]);	//---alpha
		Matrix[i][i+1] = dx[i-1];		//---r
		Matrix[i][i-1] = dx[i];			//---B
		Y[i] = 3 * (dx[i-1] * (y[i]-y[i-1])/dx[i] + dx[i] * (y[i-1]-y[i-2])/dx[i-1]);
		//---Y
	}

	Matrix[N][N] = 2 * dx[N-1];	//---alpha_n+1
	Matrix[N][N-1] = dx[N-1];	//---B_n+1
	Y[N] = 3*(y[N-1]-y[N-2]);	//---Y_n+1

	//---Forward Elimination Process
	for (k=1;k<N;k++){
		for(i=k+1;i<=N;i++){
			Matrix[i][k]=0.0;
			for(j=k+1;j<=N;j++){
				Matrix[i][j] -= Matrix[k][j]*Matrix[i][k]/Matrix[k][k];
			}
			Y[i] -= Y[k]*Matrix[i][k]/Matrix[k][k];
		}
	}

	//---Backward Substitution Process
	for(k=N;k>=1;k--){
		sigma=0.0;
		for(j=k+1;j<=N;j++){
			sigma -= c2[j]*Matrix[k][j];
		}
		c2[k] = (Y[k] + sigma)/Matrix[k][k];
	}

	for(i=1;i<N;i++){
		c3[i] = (-2*c2[i]-c2[i+1]+ 3*(y[i]-y[i-1])/dx[i])/dx[i];
		c4[i] = (c2[i]+c2[i+1]-2*(y[i]-y[i-1])/dx[i])/(dx[i]*dx[i]);
	}

	New_x = x[0];
	count = 1;

	while(1){
		New_y = +c1[count]
			+c2[count] * pow((New_x - x[count-1]), 1)
			+c3[count] * pow((New_x - x[count-1]), 2)
			+c4[count] * pow((New_x - x[count-1]), 3);

		printf("\t %3.5lf \t%3.5lf\n",New_x,New_y);
		New_x += 0.1;
		if (New_x >= x[count]){ count++;}
		if (count == N){
			break;
		}
	}

	return 0;
}
