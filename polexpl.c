#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "grRDF.h"

/*
 * Per compilar:
        gcc -o polexpl -g -Wall polexpl.c grRDF.c -lm
 */

/*!
 * \brief Funcio f del problema mixt per l'equaci\'o de la
 * calor, imposant que la soluci\'o sigui un polinomi.
 */
double f_pol (double t, double x, double y) {
  return x*x*x*y*y*y-6*t*(x*y*y*y+y*x*x*x);
}

/*!
 * \brief Funcio g del problema mixt per l'equaci\'o de la
 * calor, imposant que la soluci\'o sigui un polinomi.
 */
double g_pol (double t, double x, double y) {
  return 1+t*x*x*x*y*y*y;
}

/*!
 * \brief Funcio h del problema mixt per l'equaci\'o de la
 * calor, imposant que la soluci\'o sigui un polinomi.
 */
double h_pol (double x, double y) {
  return 1;
}

/*!\brief Implementa l'algorisme 1.1 per al punt 2 del gui\'o. */
int main (int argc, char *argv[]) {
  //Declaracions
  int k,nx,ny,nt;
  double dx;
  grRDF gr;

  FILE *f=fopen("file.txt","w");
  if (f == NULL){
        printf("Error a l'obrir l'arxiu!\n");
        exit(1);
    }

  //Control parametres linia de comandes
  if (argc!=5
         || sscanf(argv[1],"%lf",&dx)!=1
         || sscanf(argv[2],"%d",&nx)!=1
         || sscanf(argv[3],"%d",&ny)!=1
         || sscanf(argv[4],"%d",&nt)!=1
      ) {
      fprintf(stderr, "./polexpl dx nx ny nt\n");
      return -1;
   }

   //Configuracio parametres
   double mux=0.2;
   double dt=mux*dx*dx;
   double dy=dx;
   
   
   //Inicialitzo graella (parametres i llesca t=0)
   grRDF_init(&gr,dx,dy,dt,nx,ny,h_pol);

   //Escric graella inicial 
   grRDF_escriure(&gr,f);

   //Fem passos d'integracio. Bucle en el temps
   for(k=0;k<=nt;k++){
     grRDF_pasCalExpl(&gr,f_pol,g_pol);
     grRDF_escriure(&gr,f);
   }
   fclose(f);
   return 0;
}
