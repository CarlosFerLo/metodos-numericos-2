#include <stdio.h>
#include <math.h>

double f (double x, double y) ;
double dfdx (double x, double y) ;
double dfdy (double x, double y) ;

int main (void) {
	int N, imax ;
	double h, prec, tol ;

	/* --- LECTURA DE PARAMETROS --- */

	/* Lectura del valor N (numero de puntos de la curba a calcular) */
	
	printf("Introduzca el numero de puntos de la curba a calcular (N): ") ;
	scanf(" %d", &N) ;

	/* Comprobar que el valor de N sea valido */
	
	if (N < 1) {
		printf("El valor de N ha de ser positivo! (Valor introducido: %d)\n", N) ;
		return 1 ;
	} 

	/* Lectura del valor de imax (numero maximo de iteraciones del método de Newton) */
	
	printf("Introduzca el numero maximo de iteraciones del metodo de Newton (imax): ") ;
	scanf(" %d", &imax) ;

	/* Comprobar que el valor de imax sea valido */
	
	if (imax < 1) {
		printf("El valor de imax ha de ser positivo! (Valor introducido: %d)\n", imax) ;
		return 1 ;
	}

	/* Leer el valor de h (distancia entre los puntos de la curba) */
	
	printf("Introduzca la distanca deseada entre puntos de la curba (h): ") ;
	scanf(" %lf", &h) ;

	/* Comprobar que el valor de h sea valido */
	
	if (h <= 0) {
		printf("El valor de h ha de ser positivo! (Valor introducido: %lf)\n", h);
		return 1 ;
	}

	/* Lectura del valor de prec (precision del método de Newton) */
	
	printf("Introduzca la precision deseada por el método de Newton (prec): ") ;
	scanf(" %lf", &prec) ;

	/* Comprobar que el valor de prec sea valido */

	if (prec <= 0) {
		printf("El valor de prec ha de ser positivo! (Valor introducido: %lf)\n", prec) ;
		return 1 ;
	}
	
	/* Lectura del valo de tol (control de division entre 0) */

	printf("Introduzca un valore de control de division entre 0 (tol): ") ;
	scanf(" %lf", &tol) ;

	/* Comprobar que el valor de tol sea valido */

	if (tol <= 0) {
		printf("El valor de tol ha de ser positivo! (Valor introducido: %lf) \n", tol) ;
		return 1 ;
	} 

	


	return 0;
}

double f (double x, double y) {
	return 2 + x*x - 2*x*y - 4y + 7*y*y - 4*y*y*y + y*y*y*y + sin(x) + exp(x*y) ;
}

double dfdx (double x, double y) {
	return 2*x - 2*y + cos(x) + y*exp(x*y) ;
}

double dfdy (double x, double y) {
	return -2*x - 4 +14*y - 12*y*y + 4*y*y*y + x*exp(x*y) ;
}
