#include <stdio.h>
#include <stdlib.h>

#include "functions.h"

void iterate (int N, double **U, double **V) ;

int main (void) {
	int N, i ;
	double tol, **U ;	

	FILE *f ;

	/* Leer el valor de N */

	printf("Introduzca un valor para N: ") ;
	scanf(" %d", &N) ;
	

	/* Reservar memoria para U */

	U = (double **) malloc((N - 1) * sizeof(double *)) ;
	if (U == NULL) {
		printf("ERROR al asignar memoria para U.")
		return 1 ;
	}

	for (i = 0; i < N - 1; i++) {
		U[i] = (double *) malloc((N - 1) * sizeof(double)) ;
		if (U[i] == NULL) {
			printf("ERROR al asignar memoria para la fila %d de U.", i) ;
			return 1 ;
		}
	}

	/* Leer valor de tol */
	printf("Introduzca un valor para la tolerancia: ") ;
	scanf(" %lf", &tol) ;

	/*  */


	
	/* Liverar memoria para U */
	
	for (i = 0; i < N - 1; i++) {
		free(U[i]) ;
	}

	free(U) ;


	return 0 ;
}


void iterate (int N, double **U, double **V) {
	/*

	Calcular el valor del siguiente vector en la serie.

	U: vector actual ( x_k )
	V: vector nevo ( x_k+1 )

	*/
	
	int i, j ;

	for (i = 0; i < N - 1; i++) {
		
		for (j = 0; j < N - 1; j++) {

			V[i][j] = f( (i + 1) / (N + 1), (j + 1) / (N + 1) ) ;
		
			if (i == 0) {
				V[i][j] -= g_1((j + 1) / (N + 1)) ;
			} else {
				V[i][j] -= V[i - 1][j] ; 
			}
			
			if (i == N - 2) {
				V[i][j] -= g_2((j + 1) / (N + 1)) ;
			
			} else {
				V[i][j] -= U[i + 1][j] ;
			}	
			
			if (j == 0) {
				V[i][j] -= g_3((i + 1) / (N + 1)) ;
			} else { 
				V[i][j] -= V[i][j - 1] ; 
			}
			if (j == N - 1) {
				V[i][j] -= g_4((i + 1) / (N + 1)) ;
			} else {
				 V[i][j] -= U[i][j + 1] ;
			}

			V[i][j] *= - (N + 1) * (N + 1) / 4. ;
		}
		
	}

	return ;

}
