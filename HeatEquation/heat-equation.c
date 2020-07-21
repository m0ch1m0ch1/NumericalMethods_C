#include <stdio.h>

int main(void){

        int i,j;
        double T[11][1001];
        double x;
        double dt = 0.001;
        double dx = 0.1;

        FILE *output;
        output=fopen("Output.dat","w");

        for( i = 0 ; i <= 10 ; i++) {
                x = dx * (double) i;
                T[i][0]= x * (1.0 - x);
        }

        for( j = 0 ; j <= 1000 ; j++) {
                T[0][j]  = 0.0;
                T[10][j] = 0.0;
        }

        for( j = 0 ; j < 1000 ; j++) {
                for( i = 1 ; i < 10 ; i++) {
                        T[i][j+1] = T[i][j] + dt * (T[i+1][j] + T[i-1][j] - 2.0 * T[i][j]) / (dx * dx);
                }
        }


        fprintf(output,"Time/X\t");
        for( i = 0 ; i <= 10 ; i++) {
                  fprintf(output,"X_%.3lf\t", dx * (double) i);
        }
        fprintf(output,"\n");

        for( j = 0 ; j <= 1000 ; j++) {
                if(j % 10 == 0){
                        fprintf(output,"Time_%lf\t",(double) j * dt);
                        for( i = 0 ; i <= 10 ; i++) {
                                fprintf(output,"%lf\t",T[i][j]);
                        }
                        fprintf(output,"\n");
                }
        }

        fclose(output);

        return 0;
}
