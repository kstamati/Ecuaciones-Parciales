//
//  main.cpp
//  Elliptic
//
//  Created by Diego Berdeja on 07/10/2015.
//  Copyright (c) 2015 Diego Berdeja. All rights reserved.
//

#include <iostream>
#include <math.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <fstream>

#define LIMITE 2000
#define PI 3.14159265358979323846

using namespace std;

void Pedir(int* entero, float* flotante, string frase, int flag)
{
    cout << "Especifique el valor para " << frase << ": ";
    if (flag==1) {
        cin >> *entero;
    }
    else
    {
        cin >> *flotante;
    }
}

int main(int argc, const char * argv[]) {

    // Definimos las variables.
    int nx, ny, nt, nout, nx2, ny2;
    float xl, dx, x[LIMITE], yl, dy, y[LIMITE], h, t=0, wf, mu;
    int dummy;
    float fdummy;
    string token, filename="/Users/DiegoBerdeja/Desktop/";
    
    
    // Pedimos las variables.
    Pedir(&dummy, &xl, "la longitud en x", 0);
    Pedir(&dummy, &dx, "el paso en x", 0);
    Pedir(&dummy, &yl, "la longitud en y", 0);
    Pedir(&dummy, &dy, "el paso en y", 0);
    Pedir(&nout, &fdummy, "el numero de puntos evaluados que quiere", 1);
    Pedir(&dummy, &h, "el tamano de paso en t", 0);
    Pedir(&nt, &fdummy, "la resolucion que quiere para cada punto evaluado", 1);
    nx=ceil(xl/dx)+1;
    ny=ceil(yl/dy)+1;
    mu=PI/xl;
    nx2=ceil(nx/2);
    ny2=ceil(ny/2);
    
    
    // Inicializamos el archivo.
    cout << "Elija el nombre del archivo: ";
    cin >> token;
    filename=filename+token+".txt";
    FILE* fp=fopen(filename.c_str(), "w");
    fprintf(fp, "t,w(xl/2,yl/2,t)\n");
    
    
    // Inicializamos los vectores.
    float w[nx][ny];
    float wt[nx][ny];
    for (int ii=0; ii<nx; ii++) {
        for (int jj=0; jj<ny; jj++) {
            w[ii][jj]=1;
        }
    }
    for (int ii=0; ii<ny; ii++) {
        y[ii]=ii*dy;
    }
    for (int ii=0; ii<nx; ii++) {
        x[ii]=ii*dx;
    }
    
    // Iteramos y vamos imprimiendo los resultados en el archivo.
    // Iteramos sobre cada punto por evaluar.
    for (int i1=0; i1<nout; i1++) {
        // Iteramos sobre la resolucion.
        for (int i2=0; i2<nt; i2++) {
            // Iteramos sobre x.
            for (int ii=0; ii<nx; ii++) {
                // Iteramos sobre y.
                for (int jj=0; jj<ny; jj++) {
                    // Implementamos la condicion inicial.
                    if (ii==0) {
                        w[0][jj]=0;
                        wt[0][jj]=0;
                    }
                    else if (ii==(nx-1))
                    {
                        w[nx-1][jj]=0;
                        wt[nx-1][jj]=0;
                    }
                    else if (jj==0)
                    {
                        wt[ii][0]=(w[ii+1][jj]-2*w[ii][jj]+w[ii-1][jj])/powf(dx, 2)+2*(w[ii][1]-w[ii][0])/powf(dy,2);
                    }
                    else if (jj==(ny-1))
                    {
                        wf=w[ii][ny-2]+2*dy*mu*sin(mu*x[ii])*sinh(mu*y[ny-1]);
                        wt[ii][ny-1]=(w[ii+1][ny-1]-2*w[ii][ny-1]+w[ii-1][ny-1])/powf(dx,2)+(wf-2*w[ii][ny-1]+w[ii][ny-2])/powf(dy,2);
                    }
                    else
                    {
                        wt[ii][jj]=(w[ii+1][jj]-2*w[ii][jj]+w[ii-1][jj])/powf(dx,2)+(w[ii][jj+1]-2*w[ii][jj]+w[ii][jj-1])/powf(dy,2);
                    }
                }
            }
            t=t+h;
            for (int ii=0; ii<nx; ii++) {
                for (int jj=0; jj<ny; jj++) {
                    w[ii][jj]=w[ii][jj]+wt[ii][jj]*h;
                }
            }
        }
        fprintf(fp, "%5.2f,%7.4f\n", t, w[nx2][ny2]);
    }
    
    fprintf(fp, "\n\nSolucion real\n w(xl/2,yl/2) = %7.4f\n",sin(mu*x[nx2])*cosh(mu*y[ny2]));
    
    fclose(fp);
    return 0;
}
