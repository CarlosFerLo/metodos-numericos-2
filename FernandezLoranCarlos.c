#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAX_FNAME_LEN 25

#define X_INIT 0.0
#define Y_INIT 2.0

double f (double x, double y) ;
double dfdx (double x, double y) ;
double dfdy (double x, double y) ;

double newton_y (int imax, double prec, double y) ; /* TODO: Control de division entre 0 */
void pred (double h, double tol, double x, double y, double* dx, double* dy, double* pred_x, double* pred_y) ; /* TODO: Calculo d u y v fuera para optimizar? */
void correccion (double h, int imax, double prec, double tol, double x0, double y0, double* x, double* y ) ;

int main (void) {
	int N, imax, i ;
	double h, prec, tol, x0, y0, x1, y1, x2, y2, dx, dy ;
	char fname[MAX_FNAME_LEN] ;
	FILE* file;

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

	/* Lectura del nombre del archivo de escritura */

	printf("Introduzca el nombre del archivo de escritura: ") ;
	scanf("%s", fname) ;

	/* Abrir archivo de escritura */

	file = fopen(fname, "w") ;
	
	if (file == NULL) {
		printf("ERROR al abrir el archivo de escritura '%s'.\n", fname) ;
		return 1 ;
	}

	/* --- CALCULAR PRIMER PUNTO DE LA CURVA --- */

	/* Calcular un cero de f en el eje de ordenadas */
	
	x0 = X_INIT ;
	y0 = newton_y(imax, prec, Y_INIT) ;

	/* Guardar en el archivo de escritura */

	fprintf(file, "%le %le\n", x0, y0) ;

	/* --- CALCULAR LOS SIGUIENTES PUNTOS DE LA CURVA (Sentido 1) --- */
	
	printf("DEBUG: Calculando en el primer sentido...\n") ;

	/* Inicializar x1 y y1 */

	x1 = x0 ;
	y1 = y0 ;

	/* Fijar una direccion inicial */

	dx = dfdx(x0, y0) + 1 ;
	dy = dfdy(x0, y0) ; 

	/* Calculo iterativo de los puntos de la curva */

	for (i = 0; i < (N - 1) / 2; i++) {

		/* Calcular predicción y actualizar dirección */
	
		pred(h, tol,  x1, y1, &dx, &dy, &x2, &y2) ;

		/* Corregir la predicción */
			
		correccion(h, imax, prec, tol, x1, y1, &x2, &y2) ;

		/* Comprobar que no es el punto inicial */

		if (i > 0 && (x2 - x0)*(x2 - x0) + (y2 - y0)*(y2 - y0) < h*h) {
			break ;
		}

		/* Guardar en el archivo de escritura */

		fprintf(file, "%le %le\n", x2, y2) ;

		/* Actualizar x1 y y1 */

		x1 = x2 ;
		y1 = y2 ; 
	}

	printf("DEBUG: los %d puntos en sentido 1 calculados!\n", (N - 1) / 2) ;
	
	/* --- CALCULAR LOS SIGUIENTES PUNTOS DE LA CURVA (Sentido 2) --- */

	printf("DEBUG: Calculando en el segundo sentido...\n") ;

	/* Inicializar x1 y y1 */
	
	x1 = x0 ;
	y1 = y0 ;

	/* Fijar una dirección inicial (opuesta a la anterior) */

	dx = -dfdx(x0, y0) - 1 ;
	dy = -dfdy(x0, y0) ;

	/* Calculo iterativo de los puntos de la curva */

	for (i = 0; i < (N - 1) / 2.; i++) {
		
		/* Calcular prediccion y actualizar dirección */

		pred(h, tol, x1, y1, &dx, &dy, &x2, &y2) ;

		/* Corregir la predicción */

		correccion (h, imax, prec, tol, x1, y1, &x2, &y2) ;

		/* Comprobar que no es el punto inicial */

		if (i > 0 && (x2 - x0)*(x2 - x0) + (y2 - y0)*(y2 - y0) < h*h) {
			break ;
		}

		/* Guardar en el archivo de escritura */

		fprintf(file, "%le %le\n", x2, y2) ;

		/* Actualizar x1 y y1 */

		x1 = x2 ;
		y1 = y2 ;
	}

	printf("DEBUG: Los %d puntos en sentido 2 calculados!\n", (N - 1)/2) ;
	
	/* Cerrar archivo de escritura */

	fclose(file) ;

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

void pred (double h, double tol, double x, double y, double* dx, double* dy, double* pred_x, double* pred_y) {
	double u, v ;

	u = dfdx(x, y) ;
	v = dfdy(x, y) ;

	if (sqrt(u*u + v*v) < tol) {
		printf("ERROR: Peligro de division por cero en la funcion 'pred'.\n") ;
		exit(1) ;
	}

	if (*dy * v - *dx * u < 0) {
		*dx = -	(h * v) / sqrt(u*u + v*v) ;
		*dy =   (h * u) / sqrt(u*u + v*v) ;
	} else {
		*dx =   (h * v) / sqrt(u*u + v*v) ;
		*dy = -	(h * u) / sqrt(u*u + v*v) ;
	}

	*pred_x = x + *dx ;
	*pred_y = y + *dy ;

	return ;
}

void correccion (double h, int imax, double prec, double tol, double x0, double y0, double* x, double* y ) {
	int i ;
	double den, u, v, z0, z1;

	for (i = 0; i < imax; i++) {

		/* Calcular el denominador y ver si es demasiado pequeño */

		u = dfdx(*x, *y) ;
		v = dfdy(*x, *y) ;

		den = 2 * ( (*y - y0) * u - (*x - x0) * v ) ;
	
		if (fabs(den) < tol) {
			printf("ERROR: Peligro de division por cero en la función 'correccion' iteración %d, sistema incompatible.\n\n --- PARAMETROS ---\n", i+1);
			printf("h = %le\nimax = %d\nprec = %le\ntol = %le\nx0 = %le\ny0 = %le\n", h, imax, prec, tol, x0, y0) ;
			exit(1) ; 
		}

		/* Calcular solución del sistema */
	
		z0 = ( v * ((*x - x0)*(*x - x0) + (*y - y0)*(*y - y0) - h*h) - 2 * (*y - y0) * f(*x, *y) ) / den ;
		z1 = (- u * ((*x - x0)*(*x - x0) + (*y - y0)*(*y - y0)) + 2 * (*x - x0) * f(*x, *y)) / den ;

		/* Actualizar x e y */

		*x += z0 ;
		*y += z1 ;
	
		/* Comprovar si se satisfacen las condiciones de convergencia */

		if (fabs(f(*x, *y)) < prec) {
			return ;
		}
	}

	printf("ERROR: La corrección no ha convergido tras %d iteraciones!\n\n --- PARAMETROS ---\n", imax) ;
	printf("h = %le\nimax = %d\nprec = %le\ntol = %le\nx0 = %le\ny0 = %le\n", h, imax, prec, tol, x0, y0) ;
	printf("x = %le\ny = %le\n", *x, *y) ;

	exit(1) ;

}
