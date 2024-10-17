#include <stdio.h>
#include <stdlib.h>

#include "functions.h"

#define MAX_FNAME_LEN 25

int main (void) {
	int N ;
	char fileName[MAX_FNAME_LEN] ;
	FILE *file ;
	
	/* Leer el nombre del archivo de lectura */
	
	printf("Introduce el nombre del archivo de lectura: ") ;
	scanf("%s", fileName) ;

	/* Abrir archivo de lectura */
	
	file = fopen(fileName, "r") ;

	/* Leer el valor de N (el de a y b son ignorados al ser incluidos en el archivo de funciones) */

	fscanf(file, "%*le %*le %d", &N) ;

	printf("N: %d\n", N) ;

	return 0 ;
}
