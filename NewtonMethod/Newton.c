#include<stdio.h>
#include<stdlib.h>
#include<math.h>
 
#define  MaxCount 1.0e+2
#define Threshold 1.0e-5

double  f(double x);
double df(double x);
 
int main(void){
	int CalCount=0;
	double IniVal;
	double NexVal;

	printf("初期値を入力してください。\n");
	scanf("%lf",&IniVal);
	
	while(1){
		CalCount++;
		NexVal = IniVal - f(IniVal)/df(IniVal);

		if(fabs(NexVal-IniVal) < Threshold){
			printf("解は %lfです。\n",NexVal);
			break;
		}
 
		IniVal=NexVal;
		if(CalCount == MaxCount){
			printf("収束しませんでした。\n");
			break;
		}
	}
return 0;
}

double f(double x)
{return x*sin(x) + log(x);}
 
double df(double x)
{return sin(x) + x*cos(x) + 1.0/x;}
