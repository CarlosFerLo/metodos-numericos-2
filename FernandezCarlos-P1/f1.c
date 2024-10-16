#include <math.h>

double a () {
	return 1. ;
}

double b () {
	return 1. ;
}

double f (double x, double y) {
	return exp(x) * sin(M_PI * y) ;
} 

double g_1 (double y) {
	return sin(M_PI * y) / (1 - M_PI * M_PI) ;
}

double g_2 (double y) {
	return exp(a()) * sin(M_PI * y) / (1 - M_PI * M_PI) ; 
}

double g_3 (double x) {
	return 0. ;
}

double g_4 (double x) {
	return 0. ;
}

