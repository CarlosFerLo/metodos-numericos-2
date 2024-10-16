#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "functions.h"

/* ----- TODO ----- 
 * 
 * - Arreglar la iteración, ahora todo se va a inf
 *
 */

#define MAX_FNAME_LEN 25
#define ITER_MAX 10

int main (void) {
	int N, i, j, k ;
	double dist, tol, **U, **V, **Aux ;
	char fileName[MAX_FNAME_LEN] ;
	FILE *file ;

	/* --- LECTURA DE DATOS Y INICIALIZACIÓN --- */

	/* Leer el valor de N */

	printf("Introduzca un valor para N: ") ;
	scanf(" %d", &N) ;

	/* Leer el valor de tol */

	printf("Introduzca la tolerancia: ") ;
	scanf(" %le", &tol) ;

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

	/* Reservar memoria para V */
	
	V = (double **) malloc(N * sizeof(double *)) ;
	if (V == NULL) {
		printf("ERROR al asignar memoria para V.\n") ;
		return 1 ;
	}

	for (i = 0; i < N; i++) {
		V[i] = (double *) malloc(N * sizeof(double)) ;
		if (V[i] == NULL) {
			printf("ERROR al asignar memoria para la fila %d de V.\n", i) ;
			return 1 ;
		}
	}
	
	/* Inicializar U */

	for (i = 0; i < N; i++) {
		for (j = 0; j < N; j++) {
			U[i][j] = 0. ;	
		}
	}

	/* --- RESOLUCION DEL SISTEMA --- */


	/* Iterar U */

	for (k = 0; k < ITER_MAX; k++) {

		printf("\n--- k = %d ---\n", k) ; /* DEBUG */ 
		
		/* Una iteracion de U */
		for (i = 0; i < N; i++) {
			for (j = 0; j < N; j++) {

				V[i][j] = - f( a() * (i + 2) / (N + 1.), b() * (j + 2) / (N + 1.) )  ;
				V[i][j] /= (double) (N + 1) * (N + 1) ;
		
				if (i == 0) {
					V[i][j] += g_1(b() * (j + 2) / (N + 1.)) ;
				} else {
					V[i][j] += V[i - 1][j] ; 
				}
			
				if (i == N - 1) {
					V[i][j] += g_2(b() * (j + 2) / (N + 1.)) ;
			
				} else {
					V[i][j] += U[i + 1][j] ;
				}	
			
				if (j == 0) {
					V[i][j] += g_3(a() * (i + 2) / (N + 1.)) ;
				} else { 
					V[i][j] += V[i][j - 1] ; 
				}
				if (j == N - 1) {
					V[i][j] += g_4(a() * (i + 2) / (N + 1.)) ;
				} else {
					 V[i][j] += U[i][j + 1] ;
				}

				U[i][j] /= 4. ;

				printf("%le ", V[i][j]) ; /* DEBUG */
			}
			printf("\n") ; /* DEBUG */
		}
		
		/* Calcular la distancia entre U y V */
		
		for (i = 0, dist = 0.; i < N; i++) {
			for (j = 0; j < N; j++) {
				if (dist < fabs(U[i][j] - V[i][j])) {
					dist = fabs(U[i][j] - V[i][j]) ;
				}
			}
		}
	
		/* Comprobar si la distancia es menor de la tolerancia */ 
		
		if (dist <= tol) break ; 
		
		/* Intrercambiar U y V */
		
		Aux = U ;
		U = V ;
		V = Aux ;
	}

	/* --- LOGS --- */
	
	printf(" --- PARAMETROS ---\nN = %d\na = %le\nb = %le\n", N, a(), b()) ;
	printf(" --- RESULTADOS ---\n") ;
	if (k < ITER_MAX) {
		printf("Succesión ha convergido! (Numero de iteraciones: %d)\n", k) ;
		printf("Diferencia de terminos succesivos: %le\n", dist) ;	

	} else { 
		printf("La succesión no ha convergido en %d iteraciones.\n", ITER_MAX) ;
	}
	
	printf("\n\n") ;	

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

	fprintf(file, "%le %le %d\n", a(), b(), N) ;

	/* Escribir primera fila (i = 0) */

	for (j = 0; j < N + 2; j++) {
		fprintf(file, "%le ", g_1(b() * j / (N + 1.))) ;
	}
	fprintf(file, "\n") ;

	/* Escribir las filas para i = 1, 2, ..., N */
	
	for (i = 0; i < N; i++) {
		fprintf(file, "%le ", g_3(a() * (i + 1) / (N + 1.))) ;

		for (j = 0; j < N; j++) {
			fprintf(file, "%le ", U[i][j]) ;
		}

		fprintf(file, "%le\n", g_4(a() * (i + 1) / (N + 1.))) ; 
	}

	/* Escribir ultima fila (i = N + 1) */
	
	for (j = 0; j < N + 2; j++) {
		fprintf(file, "%le ", g_2(b() * j / (N + 1.))) ;
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
