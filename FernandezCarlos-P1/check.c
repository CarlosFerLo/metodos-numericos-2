#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "functions.h"

#define MAX_FNAME_LEN 25

int main (void) {
	int N, i, j ;
	double norm, dif, **U ;
	char fileName[MAX_FNAME_LEN] ;
	FILE *file ;
	
	/* Leer el nombre del archivo de lectura */
	
	printf("Introduce el nombre del archivo de lectura: ") ;
	scanf("%s", fileName) ;

	/* Abrir archivo de lectura */
	
	file = fopen(fileName, "r") ;

	/* Leer el valor de N (el de a y b son ignorados al ser incluidos en el archivo de funciones) */

	fscanf(file, "%*le %*le %d", &N) ;

	/* Asignar memoria para U */
	
	U = (double **) malloc((N + 2) * sizeof(double *)) ;
	if (U == NULL) {
		printf("ERROR al asignar memoria para U.\n") ;
		return 1 ;
	}

	for (i = 0; i < N + 2; i++) {
		U[i] = (double *) malloc((N + 2) * sizeof(double)) ;
		if (U[i] == NULL) {
			printf("ERROR al asignar memoria para la fila %d de U.\n", i) ;
			return 1 ;
		}
	}

	/* Leer los valores de la matriz del archivo */
	
	for (i = 0; i < N + 2; i++) {
		for (j = 0; j < N + 2; j++) {
			fscanf(file, " %le", U[i] + j) ;
		}
	}

	/* Cerrar archivo de lectura */
	
	fclose(file) ;

	/* Calcular la norma del vector diferencia */

	norm = 0. ;
	
	for (i = 0; i < N + 2; i++) {
		for (j = 0; j < N + 2; j++) {
			dif = fabs(U[i][j] - solution(a * i / (N + 1.), b * j / (N + 1.))) ;
				
			if (dif > norm) {
				norm = dif ;
			}
		}
	}

	/* Mostrar resultados */

	printf(" --- RESULTADOS ---\n") ;
	printf("N: %d\n", N) ;
	printf("1/N^2: %le\n", 1. / (N * N)) ;
	printf("Norma: %le\n\n", norm) ;

	return 0 ;
}
