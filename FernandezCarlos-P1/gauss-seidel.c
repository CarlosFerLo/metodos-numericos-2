#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "functions.h"

#define MAX_FNAME_LEN 25
#define ITER_MAX 100000

int main (void) {
	int N, i, j, k ;
	double tol, norm, oldUij, **U ;
	char fileName[MAX_FNAME_LEN] ;
	FILE *file ;

	/* --- LECTURA DE DATOS Y INICIALIZACIÓN --- */

	/* Leer el valor de N */

	printf("Introduzca un valor para N: ") ;
	scanf(" %d", &N) ;

	/* Comprobar que el valor de N sea valido */
	
	if (N < 1) {
		printf("El valor de N ha de ser positivo! (Valor introducido: %d)\n", N) ;
		return 1 ;
	}

	/* Leer el valor de tol */
	
	printf("Introduzca la tolerancia deseada: ") ;
	scanf(" %lf", &tol) ;
	
	/* Comprobar que el valor de tol sea valido */

	if (tol <= 0) {
		printf("La tolerancia ha de ser un valor positivo! (Valor introducido: %le)\n", tol) ;
		return 1 ;
	}

	/* Reservar memoria para U */

	U = (double **) malloc(N * sizeof(double *)) ;
	if (U == NULL) {
		printf("ERROR al asignar memoria para U.\n") ;
		return 1 ;
	}

	for (i = 0; i < N; i++) {
		U[i] = (double *) malloc(N * sizeof(double)) ;
		if (U[i] == NULL) {
			printf("ERROR al asignar memoria para la fila %d de U.\n", i) ;
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

		/* Inicializar la norma */
		
		norm = 0. ;
		
		/* Calcular nuevo valor de U */
	
		for (i = 0; i < N; i++) {
			for (j = 0; j < N; j++) {
				
				/* Guardar antiguo valor de Uij */

				oldUij = U[i][j] ;

				/* Calcular el nuevo valor de Uij */

				U[i][j] = -f(a * (i + 1) / (N + 1.), b * (j + 1) / (N + 1.)) ;
				U[i][j] /= (double) (N + 1) * (N + 1) ;

				if (i == 0) {
					U[i][j] += g_1(b * (j + 1) / (N + 1.)) / (a * a) ;
				} else {
					U[i][j] += U[i - 1][j] / (a * a) ;
				}

				if (i == N - 1) {
					U[i][j] += g_2(b * (j + 1) / (N + 1.)) / (a * a) ;
				} else {
					U[i][j] += U[i + 1][j] / (a * a) ;
				}

				if (j == 0) {
					U[i][j] += g_3(a * (i + 1) / (N + 1.)) / (b * b) ;
				} else {
					U[i][j] += U[i][j - 1] / (b * b) ;
				}

				if (j == N - 1) {
					U[i][j] += g_4(a * (i + 1) / (N + 1.)) / (b * b) ;
				} else {
					U[i][j] += U[i][j + 1] / (b * b) ;
				}

				U[i][j] /= (2. / (a * a)) + (2. / (b * b)) ;

				/* Computar diferencia y actualizar la norma */

				if (fabs(oldUij - U[i][j]) > norm) {
					norm = fabs(oldUij - U[i][j]) ;
				}
			}
		}

		/* Comprobar si se satisface la condicion de parada */

		if (norm <= tol) {
			break ;
		}
	}

	/* --- LOGS --- */

	printf(" --- PARAMETROS ---\nIter max: %d\nN: %d\na: %le\nb: %le\n\n", ITER_MAX, N, a, b) ;

	printf(" --- RESULTADOS ---\n") ;

	if (k == ITER_MAX) { /* No se ha obtenido la tolerancia deseada */
		printf("La serie no ha convergido tras %d iteraciones!\n", ITER_MAX) ;

	} else { /* Si se ha obtenido la tolerancia deseada */
		printf("La serie ha convergido tras %d iteraciones.\n", k + 1) ;
	}

	printf("Valor de la norma final: %le\n", norm) ;
	
	/* --- ESCRITURA DE DATOS --- */

	/* Leer el nombre del archivo de escritura */
	
	printf("Introduzca el nombre del archivo de escritura: ") ;
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
