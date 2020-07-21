#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>

#define Number           2  //要素数
#define t_END         2500  //試行時間

void   RungeKutta (double  a[Number]);

double funcx0     (double t,double x[Number]);
double funcx1     (double t,double x[Number]);
double funcx2     (double t,double x[Number]);

int main(){
	double  x[Number];
	clock_t start,end;
	start = clock();

	x[0]=2.5;
	x[1]=3.0;

	RungeKutta(x);

	end = clock();
	printf("  時間[計算式]  \t : \t %d \t 秒 \n",t_END);
	printf("  計算時間[PC]  \t : \t %lf \t m秒 \n",(double)(1000*(end-start))/CLOCKS_PER_SEC);
	printf("  計算結果表示  \t : \t Output.dat \n");
	printf("******************************Finish******************************\n");

	return 0;
}

void RungeKutta(double a[Number]){

	double da[Number],dca[Number][6];
	int    i,k,l,Flag;
	FILE   *fp1,*fp2;
	double Time;
	double Ra,checka,wa,wa2;
	double Va[Number],Vat[Number];
	double dta,t;
	double point,mod;

	point = Time = t = 0;
	dta=0.001;
	Flag=1;

	fp1 = fopen("Output1.dat","w");
	fp2 = fopen("Output2.dat","w");

	fprintf(fp1,"\t  Time  \t");
	for (l=0;l<Number;l++){fprintf(fp1,"  x[%d]  \t",l);}
	fprintf(fp1,"\n");
	fprintf(fp1,"\t %3.5lf \t",Time);
	for (l=0;l<Number;l++){fprintf(fp1," %lf \t",a[l]);}
	fprintf(fp1,"\n");

	fprintf(fp2,"\t  Time  \t");
	fprintf(fp2,"  適応誤差  \t");
	fprintf(fp2,"  適応σ  \t");
	fprintf(fp2,"  dt[x]  \t");
	fprintf(fp2,"  point  \t");
	fprintf(fp2,"\n");

	fprintf(fp2,"\t %3.5lf \t",Time);
	fprintf(fp2," %lf \t",0.0);
	fprintf(fp2," %lf \t",0.0);
	fprintf(fp2," %lf \t",dta);
	fprintf(fp2," %lf \t",0.0);
	fprintf(fp2,"\n");

	printf("******************************Start******************************\n");

	while(Flag==1){
		for(k=0;k<6;k++){
			if(k==0){
				t=Time;
				for (l=0;l<Number;l++){
					da[l] = a[l];
				}
			}
			else if(k==1){
				t=Time+dta/4;
				for (l=0;l<Number;l++){
					da[l] = a[l]+1.0*(dca[l][0])/4;
				}
			}
			else if(k==2){
				t=Time+dta*3/8;
				for (l=0;l<Number;l++){
					da[l] = a[l]+3.0*(dca[l][0])/32+9*(dca[l][1])/32;
				}
			}
			else if(k==3){
				t=Time+dta*12/13;
				for (l=0;l<Number;l++){
					da[l] = a[l]+1932*(dca[l][0])/2197-7200*(dca[l][1])/2197+
						7296*(dca[l][2])/2197;
				}
			}
			else if(k==4){
				t=Time+dta;
				for (l=0;l<Number;l++){
					da[l] = a[l]+439*(dca[l][0])/216-8*(dca[l][1])+
						3680*(dca[l][2])/513-845*(dca[l][3])/4104;
				}
			}
			else if(k==5){
				t=Time+dta/2;
				for (l=0;l<Number;l++){
					da[l] = a[l]-8*(dca[l][0])/27+2*(dca[l][1])-
						3544*(dca[l][2])/2565+1859*(dca[l][3])/4104-
						11*(dca[l][4])*11/40;
				}
			}
			dca[0][k]=dta*funcx0(t,da);
			dca[1][k]=dta*funcx1(t,da);
		}
		wa=0;
		wa2=0;
		for (l=0;l<Number;l++){
			Va[l]= a[l] + 25*dca[l][0]/216 + 1408*dca[l][2]/2565  +
				2197*dca[l][3]/4104  -   dca[l][4]/5;
			Vat[l]= a[l] + 16*dca[l][0]/135 + 6656*dca[l][2]/12825 +
				28561*dca[l][3]/56430 - 9*dca[l][4]/50 + 2*dca[l][5]/55;
			wa=wa+Va[l];
			wa2=wa2+Vat[l];
		}
		Ra= fabs(wa - wa2);
		checka=0.84*sqrt(sqrt(0.000001/Ra));

		if (Ra < 1.0E-6){
			Time=Time+dta;
			point=point+1;
			for(l=0;l<Number;l++){a[l]=Va[l];}
		}

		if(checka<0.1){dta=dta*0.1;}
		else if (checka>4.0){dta=dta*4.0;}
		else{dta=dta*0.84;}

		if (dta>1.0){dta=1.0;}

		mod=fmod(point,100);
		if((mod==0)&&(point!=0)){
			fprintf(fp1,"\t %3.5lf \t",Time);
			for (l=0;l<Number;l++){fprintf(fp1," %lf \t",a[l]);}
			fprintf(fp1,"\n");
		}
		fprintf(fp2,"\t %3.5lf \t",Time);
		fprintf(fp2," %lf \t",Ra);
		fprintf(fp2," %lf \t",checka);
		fprintf(fp2," %lf \t",dta);
		fprintf(fp2," %lf \t",point);
		fprintf(fp2,"\n");

		if(Time==t_END){
			Flag=0;
			fprintf(fp1,"\t %3.5lf \t",Time);
			for (l=0;l<Number;l++){
				fprintf(fp1," %lf \t",a[l]);
			}
			fprintf(fp1,"\n");
			fprintf(fp2,"\t %3.5lf \t",Time);
			fprintf(fp2," %lf \t",Ra);
			fprintf(fp2," %lf \t",checka);
			fprintf(fp2," %lf \t",dta);
			fprintf(fp2," %lf \t",point);
			fprintf(fp2,"\n");
		}
		else if (Time+dta>t_END){dta=t_END-Time;}
	}
	fclose(fp1);
	fclose(fp2);
}

double funcx0(double t,double x[Number])
{return x[0]*(0.007-0.009*x[1]); }

double funcx1(double t,double x[Number])
{return -x[1]*(0.0067-0.0078*x[0]);}


