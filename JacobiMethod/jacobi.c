#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#define N 3 //---
#define E 1.0E-10

int main(){
		
	double A[N][N] = { 3, 0.01, 0.1, 0.01, 2, 0.01, 0.1, 0.01, 1} ;
	double c[N][N];
	double x[N][N];
	double P[N][N];
	double PT[N][N];
	int i,j,k;	//---for_
	int absMax_i, absMax_j;
	double Max;
	double s;
	double cos_phi, sin_phi;
	double sqrt_sa;

	for (i = 0; i < N ; i++ ){
		for (j = 0; j < N ; j++ ){
			x[i][j] = 0;
			if ( i == j ){
				x[i][j] = 1;			
			}
		}	
	}

while(1){
	//---Algo_1
	Max = 0;
	for (i = 0; i < N ; i++ ){
		for (j = 0; j < N ; j++ ){
			if ( i == j ){ continue;}
			if (fabs(A[i][j]) > Max){
				Max = fabs(A[i][j]);
				absMax_i = i;
				absMax_j = j;
			}
		}	
	}

	if ( Max < E ){
		break;
	}
		
	//---Algo_2
	s = (A[absMax_i][absMax_i] - A[absMax_j][absMax_j])/2.0;

	sqrt_sa = sqrt( s * s + A[absMax_i][absMax_j] * A[absMax_i][absMax_j]);

	if (A[absMax_i][absMax_i] >= A[absMax_j][absMax_j]){
		cos_phi = sqrt ( (1.0 + s / sqrt_sa) / 2.0);
		sin_phi = + A[absMax_i][absMax_j] / ( 2.0 * sqrt_sa * cos_phi);
	}
	else {
		cos_phi = sqrt ( (1.0 - s / sqrt_sa) / 2.0);
		sin_phi = - A[absMax_i][absMax_j] / ( 2.0 * sqrt_sa * cos_phi);
	}

	//---Algo_3
	for (i = 0; i < N ; i++ ){
		for (j = 0; j < N ; j++ ){
			if ( i == j ){ 
				 P[i][j] = 1.0;					
				PT[i][j] = 1.0;		
			}	
			else {
				 P[i][j] = 0.0;
				PT[i][j] = 0.0;
			}	
		}
	}

	P[absMax_i][absMax_i] = + cos_phi;
	P[absMax_i][absMax_j] = - sin_phi;
	P[absMax_j][absMax_i] = + sin_phi;
	P[absMax_j][absMax_j] = + cos_phi;
	
	PT[absMax_i][absMax_i] = + cos_phi;
	PT[absMax_j][absMax_i] = - sin_phi;
	PT[absMax_i][absMax_j] = + sin_phi;
	PT[absMax_j][absMax_j] = + cos_phi;
	
	for(i=0;i<N;i++) {
                for(j=0;j<N;j++) {
			c[i][j] = 0.0;
                        for(k=0;k<N;k++) {
                                c[i][j] += x[i][k]*P[k][j];
                        }
                }
        }

	for(i=0;i<N;i++) {
                for(j=0;j<N;j++) {
			x[i][j] = c[i][j];
                }
        }

	for(i=0;i<N;i++) {
                for(j=0;j<N;j++) {
			c[i][j] = 0.0;
                        for(k=0;k<N;k++) {
                                c[i][j] += PT[i][k]*A[k][j];
                        }
                }
        }
	for (i = 0; i < N ; i++ ){
		for (j = 0; j < N ; j++ ){
			A[i][j] = 0;
		}
	}
	for(i=0;i<N;i++) {
                for(j=0;j<N;j++) {
                        for(k=0;k<N;k++) {
                                A[i][j] += c[i][k]*P[k][j];
                        }
                }
        }
}
	for(i=0;i<N;i++) {
                for(j=0;j<N;j++) {
			printf("%.16lf\t",x[i][j]);
                }
		printf("\n");
        }
	for(i=0;i<N;i++) {
                for(j=0;j<N;j++) {
			printf("%.16lf\t",A[i][j]);
                }
		printf("\n");
        }
	return 0;
}
