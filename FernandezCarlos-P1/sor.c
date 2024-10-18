#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "functions.h" 

#define ITER_MAX 1000

/* --- TODO ---
 *
 */

int main (void) {
	int N, i, k ;
	double specRad, omega, U ;
	
	/* --- LECTURA DE DATOS E INICIALIZACIÓN --- */

	/* Leer el valor de N */

	printf("Introduzca el valor de N: ") ;
	scanf(" %d", &N) ;

	/* Comprovar que el valor de N sea valido */
	
	if (N < 1) {
		printf("El valor de N ha de ser positivo! (Valor introducido: %d)\n", N) ;
		return 1 ;
	}

	/* Leer el valor del radio espectral */

	printf("Introduce una aproximación del radio espectral: ") ;
	sxanf(" %le", &specRad) ;

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

	/* Calcular valor optimo de omega */

	omega = 2. / (1 + sqrt(1 - specRad)) ;

	/* Calcular iteracion */

	for (k = 0; k < ITER_MAX; k++) {

	}

	return 0 ;
}
