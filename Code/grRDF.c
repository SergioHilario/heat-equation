#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "grRDF.h"

#define U(i,j) gr->u[(j)*(gr->nx+1)+(i)]

/* ... Codi de les funcions de grRDF.h ... */
void grRDF_init (grRDF *gr, double dx, double dy, double dt, int nx, int ny, double (*h)(double x, double y)){
    //Assignem parametres
    gr->dx=dx;gr->dy=dy;gr->dt=dt;gr->nx=nx;gr->ny=ny;gr->mux=dt/(dx*dx);gr->muy=dt/(dy*dy);
    //Establim temps inicial (t0=0)
    gr->t=0;
    //Assignem memoria pel vector/matriu u
    gr->u=(double*)malloc((nx+1)*(ny+1)*sizeof(double));
    //Inicialitzem la malla amb la funcio h
    int i,j;
    for(i=0;i<=nx;i++){
        for(j=0;j<=ny;j++){
            U(i,j)=h(i*dx,j*dy);
        }
    }
}

void grRDF_pasCalExpl (grRDF *gr, double (*f)(double t, double x, double y), double (*g)(double t, double x, double y)){
    int i,j, nx=gr->nx, ny=gr->ny;
    double dt=gr->dt,dx=gr->dx,dy=gr->dy, mux=gr->mux, muy=gr->muy;
    //Actualitzem el temps
    gr->t+=gr->dt;
    double t=gr->t;
    //Guardem la graella antiga
    double UK[nx+1][ny+1];
    for(i=0;i<=nx;i++){
        for(j=0;j<=ny;j++){
            UK[i][j]=U(i,j);
        }
    }
    //Condicions de frontera y=0
    for(i=0;i<=nx;i++){
        U(i,0)=g(t,i*dx,0);
    }
    //Condicions de frontera y=Ly
    for(i=0;i<=nx;i++){
        U(i,ny)=g(t,i*dx,ny*dy);
    }
    //Condicions de frontera x=0
    for(j=0;j<=ny;j++){
        U(0,j)=g(t,0,j*dy);
    }
    //Condicions de frontera x=Lx
    for(j=0;j<=ny;j++){
        U(nx,j)=g(t,nx*dx,j*dy);
    }
    //Apliquem l'esquema (formula 3)
    for(i=1;i<nx;i++){
        for(j=1;j<ny;j++){
            U(i,j)=(1-2*mux-2*muy)*UK[i][j]+mux*(UK[i+1][j]+UK[i-1][j])+muy*(UK[i][j+1]+UK[i][j-1])+dt*f(t-dt,i*dx,j*dy);
        }
    }
}

int grRDF_pasCalCN (grRDF *gr, double w, double tol, int maxit,
      double (*f)(double t, double x, double y),
      double (*g)(double t, double x, double y)){

}

void grRDF_escriure (grRDF *gr, FILE *fp){
    int i,j,nx=gr->nx, ny=gr->ny;
    double dx=gr->dx, dy=gr->dy;
    double t=gr->t;
    
    fprintf(fp,"# %lf\n",t);
    for(i=0;i<=nx;i++){
        for(j=0;j<=ny;j++){
            fprintf(fp,"%lf %lf %lf\n",i*dx,j*dy,U(i,j));
        }
        fprintf(fp,"\n");
    }
    fprintf(fp,"\n\n");
}
#undef U