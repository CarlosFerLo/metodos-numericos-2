#include <stdio.h>
#include <stdlib.h>

#include "functions.h"

void iterate (int N, double **U, double **V) ;

int main (void) {
	int N, i, j ;
	double **U, **V, **Aux ;	

	/* Leer el valor de N */

	printf("Introduzca un valor para N: ") ;
	scanf(" %d", &N) ;

	/* Reservar memoria para U */

	U = (double **) malloc((N - 1) * sizeof(double *)) ;
	if (U == NULL) {
		printf("ERROR al asignar memoria para U.") ;
		return 1 ;
	}

	for (i = 0; i < N - 1; i++) {
		U[i] = (double *) malloc((N - 1) * sizeof(double)) ;
		if (U[i] == NULL) {
			printf("ERROR al asignar memoria para la fila %d de U.", i) ;
			return 1 ;
		}
	}

	/* Reservar memoria para V */
	
	V = (double **) malloc((N - 1) * sizeof(double *)) ;
	if (V == NULL) {
		printf("ERROR al asignar memoria para V.") ;
		return 1 ;
	}

	for (i = 0; i < N - 1; i++) {
		V[i] = (double *) malloc((N - 1) * sizeof(double)) ;
		if (V[i] == NULL) {
			printf("ERROR al asignar memoria para la fila %d de V.", i) ;
			return 1 ;
		}	
	}

	/* Inicializar U */

	for (i = 0; i < N - 1; i++) {
		for (j = 0; j < N - 1; j++) {
			U[i][j] = 0. ;	
		}
	}

	/* Calcular iteración */

	for (i = 0; i < 100; i++) {
		iterate(N, U, V) ;
	
		Aux = U ;
		U = V ;
		V = Aux ;
	}

	/* Mostrar resultados */

	printf("\n--- RESULTADOS ---\n") ;

	for (i = 0; i < N - 1; i++) {
		for (j = 0; j < N - 1; j++) {
			printf(" %le", V[i][j]) ;
		}
		printf("\n") ;
	}

	printf("-----------------\n") ;


	/* --- LIVERAR MEMORIA --- */
	
	/* Liverar memoria para U */
	
	for (i = 0; i < N - 1; i++) {
		free(U[i]) ;
	}

	free(U) ;

	/* Liverar memoria para V */

	for (i = 0; i < N - 1; i++) {
		free(V[i]) ;
	}

	free(V) ;

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

			V[i][j] = - f( (i + 2) / (N + 1.), (j + 2) / (N + 1.) )  ;
			V[i][j] /= (double) (N + 1) * (N + 1) ;
		
			if (i == 0) {
				V[i][j] += g_1((j + 2) / (N + 1.)) ;
			} else {
				V[i][j] += V[i - 1][j] ; 
			}
			
			if (i == N - 2) {
				V[i][j] += g_2((j + 2) / (N + 1.)) ;
			
			} else {
				V[i][j] += U[i + 1][j] ;
			}	
			
			if (j == 0) {
				V[i][j] += g_3((i + 2) / (N + 1.)) ;
			} else { 
				V[i][j] += V[i][j - 1] ; 
			}
			if (j == N - 1) {
				V[i][j] += g_4((i + 2) / (N + 1.)) ;
			} else {
				 V[i][j] += U[i][j + 1] ;
			}

			V[i][j] /= 4. ;
		}
		
	}

	return ;

}
