/*
 *Author(s): Victor Nguyen, Collin Sipple, Joe Wyrick
 *Date Created: 09/27/2018
 *Date Modified: 09/27/2018
 */

#include<stdlib.h>
#include<stdio.h>
#include<math.h>
#include"utils.h"

int intmax(int a, int b) {
	if(a > b) {
		return a;
	} else {
		return b;
	}
}

int intmin(int a, int b) {
	if(a < b) {
		return a;
	} else {
		return b;
	}
}

int rgbToCMYK(int r, int g, int b, double *c, double *m, double *y, double *k) {
	
	if(c == NULL) {
		return 2;
	} else if(m == NULL) {
		return 2;
	} else if(y == NULL) {
		return 2;
	} else if(k == NULL) {
		return 2;
	}
	
	double rPrime = (double) r / 255;
	double gPrime = (double) g / 255;
	double bPrime = (double) b / 255;
	
	*k = 1 - fmax(fmax(rPrime, gPrime), bPrime);
	if(*k >= 1) {
		return 1;
	}
	*c = (1 - rPrime - *k) / (1 - *k);
	*m = (1 - gPrime - *k) / (1 - *k);
	*y = (1 - bPrime - *k) / (1 - *k);
	
	return 0;
}

int cmykToRGB(double c, double m, double y, double k, int *r, int *g, int *b) {
	
	if(r == NULL) {
		return 2;
	} else if(g == NULL) {
		return 2;
	} else if(b == NULL) {
		return 2;
	}
	
	*r = 255 * (1 - c) * (1 - k);
	*g = 255 * (1 - m) * (1 - k);
	*b = 255 * (1 - y) * (1 - k);
	if(*r < 0 || *r > 255) {
		return 1;
	} else if(*g < 0 || *g > 255) {
		return 1;
	} else if(*b < 0 || *b > 255) {
		return 1;
	}
	return 0;
}

int toGrayScale(int *r, int *g, int *b, Mode m) {
	
	if(*r < 0 || *r > 255) {
		return 1;
	} else if(*g < 0 || *g > 255) {
		return 1;
	} else if(*b < 0 || *b > 255) {
		return 1;
	}
	
	if(r == NULL) {
		return 2;
	} else if(g == NULL) {
		return 2;
	} else if(b == NULL) {
		return 2;
	}
	
	if(m == AVERAGE) {
		int rgbAvg = round((*r + *g + *b) / 3);
		*r = rgbAvg;
		*g = rgbAvg;
		*b = rgbAvg;
	} else if(m == LIGHTNESS) {
		int rgbLight = round((intmax(intmax(*r, *g), *b) + intmin(intmin(*r, *g), *b)) / 2);
		*r = rgbLight;
		*g = rgbLight;
		*b = rgbLight;
	} else if(m == LUMINOSITY) {
		int rgbLum = round((0.21 * *r) + (0.72 * *g) + (0.07 * *b));
		*r = rgbLum;
		*g = rgbLum;
		*b = rgbLum;
	} else {
		return 3;
	}
	return 0;
}