#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "functions.h" 

#define ITER_MAX 10000

int main (void) {
	int N, i, j, k, optimal_k ;
	double omega, minOmega, optimalOmega, r, tol, norm, paso,**U ;

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

	/* Leer el valor minimo de Omega */

	printf("Introduzca el primer valor de omega a contemplar: ") ;
	scanf(" %lf", &minOmega) ;

	/* Comprobar que el valor de minimo de Omega */

	if (minOmega >= 2 || minOmega <= 0) {
		printf("El valor minimo de omega ha de ser un valor entre 0 y 2! (Valor introducido: %le)\n", minOmega) ;
		return 1 ;
	}

	/* Leer el valor del paso */

	printf("Introduzca un paso: ") ;
	scanf(" %lf", &paso) ;

	/* Comprobar que el valor de paso sea valido */

	if (paso <= 0 || paso >= 2) {
		printf("El paso ha de ser un valor entre 0 y 2! (Valor introducido: %le)\n", paso) ;
		return 1 ;
	}

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
		
	optimal_k = ITER_MAX ;	
	optimalOmega = paso ;

	for (omega = minOmega; omega < 2.; omega += paso) {	

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
			
			/* Si el valor de k es mayor al optimo pasar al siguiente valor de omega */	

			if (k >= optimal_k) {
				continue ;
			}			

		}

		/* Actualizar valor de omega optimo */		

		if (k < optimal_k) {
			optimal_k = k ;
			optimalOmega = omega ;
		}

	} 

	/* --- LOGS --- */

	printf(" --- PARAMETROS ---\nIter max: %d\nN: %d\na: %le\nb: %le\nPaso: %le\n", ITER_MAX, N, a, b, paso) ;

	printf(" --- RESULTADOS ---\nValor optimo de omega: %le\nIteraciones hasta convergencia: %d\n\n\n", optimalOmega, optimal_k) ;
	
	/* --- LIVERAR MEMORIA --- */

	/* Liverar memoria para U */

	for (i = 0; i < N; i++) {
		free(U[i]) ;
	}

	free(U) ;

	return 0 ;
}
