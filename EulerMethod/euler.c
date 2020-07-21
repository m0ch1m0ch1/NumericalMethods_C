/********************
	Euler_Method.c
*********************/

#include <stdio.h>
#define dt	0.001
#define t_end	10.00

double func_x (double time,double x, double y);
double func_y (double time,double x, double y);
void Graph(void);

int main()
{
	double  time =  0.00;	//時間
	double     x =  4;	//初期値
	double     y =  2;	//
	double     t1,t2;
	FILE *Output;

	Output = fopen("Output.dat","w");
	fprintf(Output, "  Time  \t  x  \t  y  \n");
	fprintf(Output, "  %lf  \t  %lf  \t  %lf  \n", time, x, y);

	while(1){
		t1=func_x(time, x, y);
		t2=func_y(time, x, y);
		x = x + t1 * dt; //dx/dt
		y = y + t2 * dt; //dy/dt
		time = time + dt;

		if ( time >= t_end){ break; }
		fprintf(Output,"  %lf  \t  %lf  \t  %lf  \n", time, x, y);
	}
	fclose(Output);
	Graph();//
	return 0;
}

//---
double func_x(double time,double x, double y)
{return x - x * y; }

//---
double func_y(double time,double x, double y)
{return x * y - y; }

void Graph(void){
	FILE     *gp;
	gp = popen("gnuplot","w");
	fprintf(gp,"set term png\n");
	fprintf(gp,"set output \"Graph.png\"\n");
	fprintf(gp,"plot");
	fprintf(gp,"\"Output.dat\" using 1:2 title \"x\" with l,");
	fprintf(gp,"\"Output.dat\" using 1:3 title \"y\" with l\n");
	fflush(gp);
	pclose(gp);
}
