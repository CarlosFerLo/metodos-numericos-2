#include <stdio.h>
#include <math.h>

double f (double x, double y) ;
double dfdx (double x, double y) ;
double dfdy (double x, double y) ;

int main (void) {



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
