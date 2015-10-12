#include <stdio.h>
#include <math.h>

#define rho 0.01
#define ten 40.0
#define max 100

int main()
{
    int i,k;
    double x[101][3];
    
    FILE *out;
    out  = fopen("eqstring.txt","w");
    
    for(i=0; i<81; i++)
    {
        x[i][0] = 0.00125*i;
    }
    for(i=81; i<101; i++)
    {
        x[i][0] = 0.1-0.005*(i-80);
    }
    for(i=1; i<100; i++)
    {
        x[i][1] = x[i][0]+0.5*(x[i+1][0]+x[i-1][0]-2.0*x[i][0]);
    }
    
    for(k=1; k<max; k++)
    {
        for(i=1; i<100; i++)
        {
            x[i][2] = 2.0*x[i][1]-x[i][0]+(x[i+1][1]+x[i-1][1]-2.0*x[i][1]);
        }
        for(i=0; i<101; i++)
        {
            x[i][0] = x[i][1];
            x[i][1] = x[i][2];
        }
        
        if((k%5) == 0)
        {
            for(i=0; i<101; i++)
            {
                fprintf(out, "%f\n",x[i][2]);
            }
            fprintf(out, "\n");       
        }
    }
    printf("data stored in eqstring.txt\n");
    fclose(out);
}