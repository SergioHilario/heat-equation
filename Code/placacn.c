#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "grRDF.h"

#define K 0.13
#define C 0.11
#define RHO 7.8

/*
 * Per compilar:
        gcc -o placacn -g -Wall placacn.c grRDF.c -lm
 */

/*Per comparar resultats: paste -d ' ' placacn.txt placacn2.txt | awk '{ print $3-$6}' | less*/

/*!
 * \brief Funcio f del problema mixt per l'equaci\'o de la
 * calor, imposant que la soluci\'o sigui un polinomi.
 */
double F (double t, double x, double y) {
    if(sqrt((x-0.5)*(x-0.5)+(y-0.5)*(y-0.5))<=0.2){
        return 100/K;
    }
    else return 0;
}

/*!
 * \brief Funcio g del problema mixt per l'equaci\'o de la
 * calor, imposant que la soluci\'o sigui un polinomi.
 */
double G (double t, double x, double y) {
  return 0;
}

/*!
 * \brief Funcio h del problema mixt per l'equaci\'o de la
 * calor, imposant que la soluci\'o sigui un polinomi.
 */
double H (double x, double y) {
  return 0;
}

/*!\brief Implementa l'algorisme 1.1 per al punt 2 del gui\'o. */
int main (int argc, char *argv[]) {
  //Declaracions
  int k,nx,ny,ntau,maxit;
  double dtau,tol;
  grRDF gr;

  FILE *f=fopen("placacn.txt","w");
  if (f == NULL){
        printf("Error a l'obrir l'arxiu!\n");
        exit(1);
    }

  //Control parametres linia de comandes
  if (argc!=7
         || sscanf(argv[1],"%d",&nx)!=1
         || sscanf(argv[2],"%d",&ny)!=1
         || sscanf(argv[3],"%lf",&dtau)!=1
         || sscanf(argv[4],"%d",&ntau)!=1
         || sscanf(argv[5],"%lf",&tol)!=1
         || sscanf(argv[6],"%d",&maxit)!=1
      ){
      fprintf(stderr, "./placacn nx ny dtau ntau tol maxit\n");
      return -1;
   }

   //Configuracio parametres
   double dx=1./nx;
   double dy=1./ny;
   double dt=K/(C*RHO)*dtau;
   
   //Inicialitzem graella (parametres i llesca t=0)
   grRDF_init(&gr,dx,dy,dt,nx,ny,H);

   //Escrivim graella inicial 
   grRDF_escriure(&gr,f);

   //Fem passos d'integracio. Bucle en el temps
   for(k=0;k<=ntau;k++){
     grRDF_pasCalCN(&gr,1.7,tol,maxit,F,G);
     grRDF_escriure(&gr,f);
   }
   fclose(f);
   return 0;
}
#undef K
#undef RHO
#undef C
