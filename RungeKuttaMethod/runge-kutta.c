#include <stdio.h>
#include <math.h>
#include <time.h>

#define Number		 	4	 	//要素数
#define t_END		  100	 	//試行時間
#define dt		  	0.001	 	//固定刻み

void   RungeKutta (double  a[Number]);
double funcx0     (double t,double x[Number]);
double funcx1     (double t,double x[Number]);
double funcx2     (double t,double x[Number]);
double funcx3     (double t,double x[Number]);

int main(){
	double x[Number];
	clock_t start,end;
	start = clock();

	x[0]=1.0;
	x[1]=0.2;
	x[2]=0.0;
	x[3]=0.0;

	RungeKutta(x);

	end = clock();
	printf("  時間[計算式]  \t : \t %.16d \t 秒 \n",t_END);
	printf("  計算時間[PC]  \t : \t %.16lf \t m秒 \n",(double)(1000*(end-start))/CLOCKS_PER_SEC);
	printf("  計算結果表示  \t : \t Output.dat \n");
	printf("******************************Finish******************************\n");

	return 0;
}

void RungeKutta(double a[Number]){

	double da[Number],dca[Number][4];
	int    i,k,l,tend;
	FILE   *fp1;
	double time,mod;
	double t;

	time = t = 0;

	fp1=fopen("Output.dat","w");

	fprintf(fp1,"\t  Time  \t");
	for (l=0;l<Number;l++){fprintf(fp1,"  x[%d]  \t",l);}
	fprintf(fp1,"\n");

	fprintf(fp1,"\t %3.5lf \t",time);
	for (l=0;l<Number;l++){fprintf(fp1," %lf \t",a[l]);}
	fprintf(fp1,"\n");

	printf("******************************Start******************************\n");

	tend=(int)t_END/dt;
	for (i=0;i<tend;i++){
		for(k=0;k<4;k++){
			if(k==0)     {t=time;     for (l=0;l<Number;l++){da[l]=a[l];               }}
			else if(k==1){t=time+dt/2;for (l=0;l<Number;l++){da[l]=a[l]+(dca[l][0])/2; }}
			else if(k==2){t=time+dt/2;for (l=0;l<Number;l++){da[l]=a[l]+(dca[l][1])/2; }}
			else if(k==3){t=time+dt;  for (l=0;l<Number;l++){da[l]=a[l]+dca[l][2];     }}
			dca[0][k]=dt*funcx0(t,da);
			dca[1][k]=dt*funcx1(t,da);
			dca[2][k]=dt*funcx2(t,da);
			dca[3][k]=dt*funcx3(t,da);
    }

		for (l=0;l<Number;l++){
			a[l]=a[l]+(dca[l][0]+2*dca[l][1]+2*dca[l][2]+dca[l][3])/6;
		}

		time = (i+1)*dt;
		mod = fmod(time,1);

		if (mod == 0){
			fprintf(fp1,"\t %3.5lf \t",time);
			for (l=0;l<Number;l++){fprintf(fp1," %lf \t",a[l]);}
				fprintf(fp1,"\n");
		}
	}

	fclose(fp1);
}

double funcx0(double t,double x[Number])
{return 1.0 * x[2] - 1.0 * x[0] * x[1] ; }

double funcx1(double t,double x[Number])
{return - 1.0 * x[0] * x[1] + 1.0 * x[2] + 1.0 * x[2]; }

double funcx2(double t,double x[Number])
{return + 1.0 * x[0] * x[1] - 1.0 * x[2] - 1.0 * x[2]; }

double funcx3(double t,double x[Number])
{return 1.0 * x[2];}
