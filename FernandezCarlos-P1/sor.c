#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "functions.h" 

#define ITER_MAX 100000
#define MAX_FNAME_LEN 25

int main (void) {
	int N, i, j, k ;
	double omega, r, tol, norm, **U ;
	char fileName[MAX_FNAME_LEN] ;
	FILE *file ;

	/* --- LECTURA DE DATOS E INICIALIZACIÓN --- */

	/* Leer el valor de N */

	printf("Introduzca el valor de N: ") ;
	scanf(" %d", &N) ;

	/* Comprovar que el valor de N sea valido */
	
	if (N < 1) {
		printf("El valor de N ha de ser positivo! (Valor introducido: %d)\n", N) ;
		return 1 ;
	}

	/* Leer el valor de tol */

	printf("Introduzca la tolerancia deseada: ") ;
	scanf(" %lf", &tol) ;

	/* Comprobar que el valor de tols sea valido */

	if (tol <= 0) {
		printf("La tolerancia ha de ser un valor positivo! (Valor introducido: %le)\n", tol) ;
		return 1 ;
	}

	/* Leer el valor de omega */

	printf("Introduzca el valor de omega: ") ;
	scanf(" %lf", &omega) ;

	/* Reservar memoria para U */

	U = (double **) malloc(N * sizeof(double *)) ;
	if (U == NULL) {
		printf("ERROR al asignar memoria para U.\n") ;
		return 1;
	}

	for (i = 0; i < N; i++) {
		U[i] = (double *) malloc(N * sizeof(double)) ;
		if (U[i] == NULL) {
			printf("ERROR al asignar memoria para la file %d de U.\n", i) ;
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

	/* Calcular iteracion */

	for (k = 0; k < ITER_MAX; k++) {

		/* Inicializar la norma */		

		norm = 0. ;

		/* Calcular nuevo valor de U */

		for (i = 0; i < N; i++) {
			for (j = 0; j < N; j++) {
				
				/* Calcular r^(k) */
				
				r = -f(a * (i + 1) / (N + 1.), b * (j + 1) / (N + 1.)) ;
				r /= (double) (N + 1.) * (N + 1.) ;

				if (i == 0) {
					r += g_1(b * (j + 1) / (N + 1.)) / (a * a) ;
				} else {
					r += U[i - 1][j] / (a * a) ;
				}

				if (i == N - 1) {
					r += g_2(b * (j + 1) / (N + 1.)) / (a * a) ;
				} else {
					r += U[i + 1][j] / (a * a) ;
				}

				if (j == 0) {
					r += g_3(a * (i + 1) / (N + 1.)) / (b * b) ;
				} else {
					r += U[i][j - 1] / (b * b) ;
				}

				if (j == N - 1) {
					r += g_4(a * (i + 1) / (N + 1.)) / (b * b) ;
				} else {
					r += U[i][j + 1] / (b * b) ;
				}
				
				r /= (2. / (a * a)) + (2. / (b * b)) ;
				r -= U[i][j] ;

				/* Calcular Uij */

				U[i][j] += omega * r ;
					
				/* Calcular diferencia y actualizar la norma */

				if (fabs(r) / omega > norm) {
					norm = fabs(r) / omega ;
				}

			}
		}

		/* Comprobar si se satisface la condicion de parada */

		if (norm <= tol) {
			break ;
		}
	
	} 

	/* --- LOGS --- */

	printf(" --- PARAMETROS ---\nIter max: %d\nN: %d\na: %le\nb: %le\n", ITER_MAX, N, a, b) ;
	printf("Aproximacion de omega: %le\n\n", omega) ;

	printf(" --- RESULTADOS ---\n") ;
	
	if (k == ITER_MAX) { /* No se ha obtenido la tolerancia deseada */
		printf("La serie no ha convergido tras %d iteraciones!\n", ITER_MAX) ;
	
	} else { /* Si se ha obtenido la tolerancia deseada */
		printf("La serie ha convergido tras %d iteraciones.\n", k + 1) ;
	}

	printf("Valor de la norma final: %le\n\n\n", norm) ;
	
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

	/* Escribir valored de a, b y N */
	
	fprintf(file, "%le %le %d\n", a, b, N) ;

	/* Escribir primera file (i = 0) */
	
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

	/* Escribir la ultima fila (i = N + 1) */
	
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
