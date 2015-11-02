/*---Gray-Scott Model---*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N 100 		//---Mesh
#define EndTime 1000

/********************************************************************
 2U + V -> 3U
      U -> P
        V : 原材料となる化学物質
        U : 中間生成物かつ自己触媒物質
        P : 最終生成物

 u/t = DuΔu + u^2v - (F+k)u
 v/t = DvΔv - u^2v + F(1-v)
         du : U の拡散率
         dv : V の拡散率
         F  : 原材料 V の外部からの供給率＆中間生成物 U の外部への流出率
         k  : 中間生成物 U の最終生成物 P への転換率（U の除去率）
*********************************************************************/

void Output(double u[N][N][2], double v[N][N][2],int k);

int main(){

	double ht;			//---dt
	double hx;			//---
	double hy;			//---
	double timer;			//---

	//---Parameter
	double u[N][N][2]={0.0};	//---u
	double delux, deluy;		//---@u/@x, @u/@y
	double v[N][N][2]={0.0};	//---v
	double delvx, delvy;		//---@v/@x, @v/@y
	double Du    = 0.00002;		//---Du
	double Dv    = 0.00001;		//---Dv
	double F     = 0.02500;		//---
	double kappa = 0.06000;		//---

	int i, j, k;
	int rotation, count;

        // Initial values
	ht    = 0.1;
	hx    = 1.0/(N-1);
	hy    = 1.0/(N-1);
	timer = 0.0;

	// Initial condition
	for (i=0; i<N; i++) {
		for (j=0; j<N; j++) {
			u[i][j][0] = 1.0;
			v[i][j][0] = 0.0;
		}
	}

	// Center
	u[N/2][N/2][0] = 0.25;
	v[N/2][N/2][0] = 1.0;

	// Gray-Scott Model Calculation
	for (k=0; k < EndTime * (int) (1.0 / ht); k++) {
	  	for(i=1; i<N-1; i++) {
  			u[N-1][i][0] = u[1][i][0];
  			  u[0][i][0] = u[N-2][i][0];
  			u[i][N-1][0] = u[i][1][0];
  			  u[i][0][0] = u[i][N-2][0];

  			v[N-1][i][0] = v[1][i][0];
  			  v[0][i][0] = v[N-2][i][0];
  			v[i][N-1][0] = v[i][1][0];
  			  v[i][0][0] = v[i][N-2][0];
  		}
		for (i=1; i<N-1; i++) {
    			for (j=1; j<N-1; j++) {
    				// Calculation U
    				delux = Du*(u[i+1][j][0] -2*u[i][j][0] +u[i-1][j][0])/(hx*hx);
						deluy = Du*(u[i][j+1][0] -2*u[i][j][0] +u[i][j-1][0])/(hy*hy);
						u[i][j][1] = u[i][j][0] +ht*
				 		(delux +deluy -u[i][j][0]*v[i][j][0]*v[i][j][0] +F*(1-u[i][j][0]));

						// Calcuration V
						delvx = Dv*(v[i+1][j][0] -2*v[i][j][0] +v[i-1][j][0])/(hx*hx);
						delvy = Dv*(v[i][j+1][0] -2*v[i][j][0] +v[i][j-1][0])/(hy*hy);
						v[i][j][1] = v[i][j][0] +ht*
				 		(delvx +delvy +u[i][j][0]*v[i][j][0]*v[i][j][0] -(F+kappa)*v[i][j][0]);
					}
    }

	  	// output Data
		if ((k % 1000) == 0) {
			Output(u,v,k);
			printf("time = %.4lf \n",timer);
		}

		// Renewal value
		for (i=1; i<N-1; i++) {
			for (j=1; j<N-1; j++) {
				u[i][j][0] = u[i][j][1];
				v[i][j][0] = v[i][j][1];
			}
		}
		timer = timer +ht;
  	}
	return 0;
}

void Output(double u[N][N][2], double v[N][N][2], int k){

	int i, j;
	FILE *Uout;
	FILE *Vout;
	char f1name[50], f2name[50];
	FILE *gp;

	//writing data

	sprintf(f1name,"GR/outUGR_%d.dat",k);
	sprintf(f2name,"GR/outVGR_%d.dat",k);
	Uout = fopen(f1name,"w");
	Vout = fopen(f2name,"w");
	for(i=1; i<N-1; i++) {
		for (j=1; j<N-1; j++) {
			fprintf(Uout,"%.5lf\t",u[i][j][1]);
			fprintf(Vout,"%.5lf\t",v[i][j][1]);
		}
		fprintf(Uout,"\n");
		fprintf(Vout,"\n");
	}
	fclose (Uout);
	fclose (Vout);

	gp=popen("gnuplot","w");
	fprintf(gp,"set terminal png\n");
	fprintf(gp,"set output \"./GR/Graph_UGR_%d.png\"\n",k);
	fprintf(gp,"set contour\n");
	fprintf(gp,"splot \"%s\" matrix w l\n",f1name);
	fprintf(gp,"\n");
	fprintf(gp,"set output \"./GR/Graph_VGR_%d.png\"\n",k);
 	fprintf(gp,"set contour\n");
	fprintf(gp,"splot \"%s\" matrix w l\n",f2name);
	fprintf(gp,"\n");
	fflush(gp);
	pclose(gp);
}
