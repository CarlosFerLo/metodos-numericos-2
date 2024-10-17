#include <stdio.h>
#include <stdlib.h>

#include "functions.h"

/* ----- TODO ----- 
 *
 * - Eliminar uso de la funcion iterate. 
 * - Implementar metodo de parada riguroso.
 *
 */

#define MAX_FNAME_LEN 25
#define ITER_MAX 1000

int main (void) {
	int N, i, j, k ;
	double **U ;
	char fileName[MAX_FNAME_LEN] ;
	FILE *file ;

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

	for (k = 0; k < ITER_MAX; k++) {
		
		/* Calcular nuevo valor de U */
	
		for (i = 0; i < N; i++) {
			for (j = 0; j < N; j++) {

				U[i][j] = -f(a * (i + 2) / (N + 1.), b * (j + 2) / (N + 1.)) ;
				U[i][j] /= (double) (N + 1) * (N + 1) ;

				if (i == 0) {
					U[i][j] += g_1(b * (j + 2) / (N + 1.)) ;
				} else {
					U[i][j] += U[i - 1][j] ;
				}

				if (i == N - 1) {
					U[i][j] += g_2(b * (j + 2) / (N + 1.)) ;
				} else {
					U[i][j] += U[i + 1][j] ;
				}

				if (j == 0) {
					U[i][j] += g_3(a * (i + 2) / (N + 1.)) ;
				} else {
					U[i][j] += U[i][j - 1] ;
				}

				if (j == N - 1) {
					U[i][j] += g_4(a * (i + 2) / (N + 1.)) ;
				} else {
					U[i][j] += U[i][j + 1] ;
				}

				U[i][j] /= 4. ;
			}
		}
	}

	/* --- ESCRITURA DE DATOS --- */

	/* Leer el nombre del archivo de escritura */
	
	printf("Introduce el nombre del archivo de escritura: ") ;
	scanf("%s", fileName) ;

	/* Abrir archivo de escritura */

	file = fopen(fileName, "w") ;
	if (file == NULL) {
		printf("ERROR al abrir el archivo de escritura '%s'.\n", fileName) ;
		return 1 ;
	}
	
	/* Escribir valores de a, b y N */

	fprintf(file, "%le %le %d\n", a, b, N) ;

	/* Escribir primera fila (i = 0) */

	for (j = 0; j < N + 2; j++) {
		fprintf(file, "%le ", g_1(b * j / (N + 1.))) ;
	}
	fprintf(file, "\n") ;

	/* Escribir las filas para i = 1, 2, ..., N */
	
	for (i = 0; i < N; i++) {
		fprintf(file, "%le ", g_3(a * (i + 1) / (N + 1.))) ;

		for (j = 0; j < N; j++) {
			fprintf(file, "%le ", U[i][j]) ;
		}

		fprintf(file, "%le\n", g_4(a * (i + 1) / (N + 1.))) ; 
	}

	/* Escribir ultima fila (i = N + 1) */
	
	for (j = 0; j < N + 2; j++) {
		fprintf(file, "%le ", g_2(b * j / (N + 1.))) ;
	}

	/* Cerrar archivo de escritura */
	
	fclose(file) ;


	/* --- LIVERAR MEMORIA --- */
	
	/* Liverar memoria para U */
	
	for (i = 0; i < N; i++) {
		free(U[i]) ;
	}

	free(U) ;

	return 0 ;
}
