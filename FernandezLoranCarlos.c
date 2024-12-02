#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define X_INIT 0.0
#define Y_INIT 0.0

double square (double x) ;

double f (double x, double y) ;
double dfdx (double x, double y) ;
double dfdy (double x, double y) ;

double newton_y (int imax, double prec, double y) ; /* TODO: Control de division entre 0 */
void pred (double h, double x, double y, double* pred_x, double* pred_y) ; /* TODO: Control de division entre 0 | Calculo d u y v fuera para optimizar? */
void correccion (double h, int imax, double prec, double tol, double x0, double y0, double* x, double* y ) ;

int main (void) {
	int N, imax ;
	double h, prec, tol, x0, y0 ;

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

	/* --- CALCULAR PRIMER PUNTO DE LA CURVA --- */

	/* Calcular un cero de f en el eje de ordenadas */
	
	x0 = X_INIT ;
	y0 = newton_y(imax, prec, Y_INIT) ;

		


	return 0;
}

double f (double x, double y) {
	return -2 + x*x - 2*x*y - 4*y + 7*y*y - 4*y*y*y + y*y*y*y + sin(x) + exp(x*y) ;
}

double dfdx (double x, double y) {
	return 2*x - 2*y + cos(x) + y*exp(x*y) ;
}

double dfdy (double x, double y) {
	return -2*x - 4 + 14*y - 12*y*y + 4*y*y*y + x*exp(x*y) ;
}

double newton_y (int imax, double prec, double y) {
/* 
	El objetivo de esta función es aproximar un cero de f en el eje de las ordenadas. Esto se debe a que en el caso de las abcisas, la funcion no tiene ceros, y en este caso si los hay son más sencillos de calcular dado que:
	f(0, y) = 3 - 4*y + 7*y*y - 4*y*y*y + y*y*y*y
*/
	int i ;

	for (i = 0; i < imax; i++) {
		y -= (-1 - 4*y + 7*y*y - 4*y*y*y + y*y*y*y) / (-4 + 14*y - 12*y*y + 4*y*y*y) ;

		if (fabs(-1 - 4*y + 7*y*y - 4*y*y*y + y*y*y*y) < prec) {
			return y ;
		}
	}

	printf("ERROR: El método de Newton no ha convergido tras %d iteraciones!\n", imax) ;
	exit(1) ;	
}

void pred (double h, double x, double y, double* pred_x, double* pred_y) {
	*pred_x = x - (h * dfdy(x, y)) / sqrt(square(dfdx(x, y)) + square(dfdy(x, y))) ;
	*pred_y = y + (h * dfdx(x, y)) / sqrt(square(dfdx(x, y)) + square(dfdy(x, y))) ;
}

double square (double x) {
	return x*x ;
}

void correccion (double h, int imax, double prec, double tol, double x0, double y0, double* x, double* y ) {
	int i ;
	double  z1, den, u ;

	for (i = 0; i < imax; i++) {
		/* Calcular el denominador y ver si es demasiado pequeño */

		u = dfdx(*x, *y) ;
		
		den = (*y - y0) * u - (*x - x0) * dfdy(*x, *y) ;
	
		if (fabs(den) < tol) {
			printf("ERROR: Peligro de division por cero en la función 'correccion' iteración %d.\n\n --- PARAMETROS ---\n", i+1);
			printf("h = %le\nimax = %d\nprec = %le\ntol = %le\nx0 = %le\n y0 = %le\n", h, imax, prec, tol, x0, y0) ;
			exit(1) ; 
		}

		/* Calcular z1 */


		z1 = ( (*x - x0) * f(*x, *y) + 0.5 * u * (h*h - (*x - x0)*(*x - x0) - (*y - y0)*(*y - y0)) ) / den ;

		/* Calcular el denominador y ver si es demasiado pequeño */

		den = 2 * (*x - x0) ;

				
		if (fabs(den) < tol) {
			printf("ERROR: Peligro de division por cero en la función 'correccion' iteración %d.\n\n --- PARAMETROS ---\n", i+1);
			printf("h = %le\nimax = %d\nprec = %le\ntol = %le\nx0 = %le\n y0 = %le\n", h, imax, prec, tol, x0, y0) ;
			exit(1) ; 
		}
	
		/* Actualizar x e y */

		*x += ( h*h - den - (*y - y0)*(*y - y0) - 2 * (*y - y0) * z1 ) / den ;
		*y += z1 ;

		/* Comprovar si se satisfacen las condiciones de convergencia */

		if (fabs(f(*x, *y)) < prec) {
			return ;
		}
	}

	printf("ERROR: La corrección no ha convergido tras %d iteraciones!\n", imax) ;
	exit(1) ;

}
