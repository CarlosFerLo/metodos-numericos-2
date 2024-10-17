#include <stdio.h>
#include <stdlib.h>

#include "functions.h"

/* ----- TODO ----- 
 * 
 * - Implementar el valored de a y b diferentes de 0 y 1.
 * - Implementar metodo de parada riguroso.
 */

#define MAX_FNAME_LEN 25

void iterate (int N, double **U) ;

int main (void) {
	int N, i, j ;
	double a, b, **U ;
	char fileName[MAX_FNAME_LEN] ;
	FILE *f ;

	/* TO BE DELEATED */
	a = 1. ; 
	b = 1. ;
	/* --- */
	

	/* --- LECTURA DE DATOS Y INICIALIZACIÓN --- */

	/* Leer el valor de N */

	printf("Introduzca un valor para N: ") ;
	scanf(" %d", &N) ;

	/* Reservar memoria para U */

	U = (double **) malloc(N * sizeof(double *)) ;
	if (U == NULL) {
		printf("ERROR al asignar memoria para U.") ;
		return 1 ;
	}

	for (i = 0; i < N; i++) {
		U[i] = (double *) malloc(N * sizeof(double)) ;
		if (U[i] == NULL) {
			printf("ERROR al asignar memoria para la fila %d de U.", i) ;
			return 1 ;
		}
	}

	/* --- RESOLUCION DEL SISTEMA --- */

	/* Inicializar U */

	for (i = 0; i < N; i++) {
		for (j = 0; j < N; j++) {
			U[i][j] = 0. ;	
		}
	}

	/* Calcular iteración */

	for (i = 0; i < 100; i++) {
		iterate(N, U) ;
	}

	/* --- ESCRITURA DE DATOS --- */

	/* Leer el nombre del archivo de escritura */
	
	printf("Introduce el nombre del archivo de escritura: ") ;
	scanf("%s", fileName) ;

	/* Abrir archivo de escritura */

	f = fopen(fileName, "w") ;
	if (f == NULL) {
		printf("ERROR al abrir el archivo de escritura '%s'.\n", fileName) ;
		return 1 ;
	}
	
	/* Escribir valores de a, b y N */

	fprintf(f, "%le %le %d\n", a, b, N) ;

	/* Escribir primera fila (i = 0) */

	for (j = 0; j < N + 2; j++) {
		fprintf(f, "%le ", g_1(j / (N + 1.))) ;
	}
	fprintf(f, "\n") ;

	/* Escribir las filas para i = 1, 2, ..., N */
	
	for (i = 0; i < N; i++) {
		fprintf(f, "%le ", g_3((i + 1) / (N + 1.))) ;

		for (j = 0; j < N; j++) {
			fprintf(f, "%le ", U[i][j]) ;
		}

		fprintf(f, "%le\n", g_4((i + 1) / (N + 1.))) ; 
	}

	/* Escribir ultima fila (i = N + 1) */
	
	for (j = 0; j < N + 2; j++) {
		fprintf(f, "%le ", g_2(j / (N + 1.))) ;
	}

	/* Cerrar archivo de escritura */
	
	fclose(f) ;


	/* --- LIVERAR MEMORIA --- */
	
	/* Liverar memoria para U */
	
	for (i = 0; i < N; i++) {
		free(U[i]) ;
	}

	free(U) ;

	return 0 ;
}


void iterate (int N, double **U) {
	/*

	Calcular el valor del siguiente vector en la serie.

	U: vector actual ( x_k ) [ MODIFICADO ] -> vector x_k+1

	*/
	
	int i, j ;

	for (i = 0; i < N; i++) {
		for (j = 0; j < N; j++) {

			U[i][j] = - f( (i + 2) / (N + 1.), (j + 2) / (N + 1.) )  ;
			U[i][j] /= (double) (N + 1) * (N + 1) ;
		
			if (i == 0) {
				U[i][j] += g_1((j + 2) / (N + 1.)) ;
			} else {
				U[i][j] += U[i - 1][j] ; 
			}
			
			if (i == N - 1) {
				U[i][j] += g_2((j + 2) / (N + 1.)) ;
			
			} else {
				U[i][j] += U[i + 1][j] ;
			}	
			
			if (j == 0) {
				U[i][j] += g_3((i + 2) / (N + 1.)) ;
			} else { 
				U[i][j] += U[i][j - 1] ; 
			}
			if (j == N - 1) {
				U[i][j] += g_4((i + 2) / (N + 1.)) ;
			} else {
				 U[i][j] += U[i][j + 1] ;
			}

			U[i][j] /= 4. ;
		}
	}

	return ;

}
