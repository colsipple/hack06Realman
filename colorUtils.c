/*
 *Author(s): Victor Nguyen, Collin Sipple, Joe Wyrick
 *Date Created: 09/27/2018
 *Date Modified: 09/27/2018
 */

#include<stdlib.h>
#include<stdio.h>
#include<math.h>
#include"colorUtils.h"

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
	
	if(r < 0 || r > 255) {
		return 1;
	} else if(g < 0 || g > 255) {
		return 1;
	} else if(b < 0 || b > 255) {
		return 1;
	}
	
	if(c == NULL) {
		return 1;
	} else if(m == NULL) {
		return 1;
	} else if(y == NULL) {
		return 1;
	} else if(k == NULL) {
		return 1;
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
	
	if(c < 0 || c > 1) {
		return 1;
	} else if(m < 0 || m > 1) {
		return 1;
	} else if(y < 0 || y > 1) {
		return 1;
	} else if(k < 0 || k > 1) {
		return 1;
	}
	
	if(r == NULL) {
		return 1;
	} else if(g == NULL) {
		return 1;
	} else if(b == NULL) {
		return 1;
	}
	
	//If the rounding is still off, then it will round up
	*r = round(255 * (1 - c) * (1 - k));
	double rReal = 255 * (1 - c) * (1 - k);
	if(fabs(*r - rReal) >= 0.5) {
		*r += 1;
	}
	
	*g = round(255 * (1 - m) * (1 - k));
	double gReal = 255 * (1 - m) * (1 - k);
	if(fabs(*g - gReal) >= 0.5) {
		*g += 1;
	}
	
	*b = round(255 * (1 - y) * (1 - k));
	double bReal = 255 * (1 - y) * (1 - k);
	if(fabs(*b - bReal) >= 0.5) {
		*b += 1;
	}
	
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
	
	if(r == NULL) {
		return 1;
	} else if(g == NULL) {
		return 1;
	} else if(b == NULL) {
		return 1;
	}
	
	if(*r < 0 || *r > 255) {
		return 1;
	} else if(*g < 0 || *g > 255) {
		return 1;
	} else if(*b < 0 || *b > 255) {
		return 1;
	}
	
	if(m == AVERAGE) {
		int rgbAvg = round((*r + *g + *b) / 3);
		double realAvg = (double) (*r + *g + *b) / 3;
		if(fabs(rgbAvg - realAvg) >= 0.5) {
			rgbAvg++;
		}
		*r = rgbAvg;
		*g = rgbAvg;
		*b = rgbAvg;
	} else if(m == LIGHTNESS) {
		int rgbLight = round((intmax(intmax(*r, *g), *b) + intmin(intmin(*r, *g), *b)) / 2);
		double realLight = (double) (intmax(intmax(*r, *g), *b) + intmin(intmin(*r, *g), *b)) / 2;
		if(fabs(rgbLight - realLight) >= 0.5) {
			rgbLight++;
		}
		*r = rgbLight;
		*g = rgbLight;
		*b = rgbLight;
	} else if(m == LUMINOSITY) {
		int rgbLum = round((0.21 * (*r)) + (0.72 * (*g)) + (0.07 * (*b)));
		*r = rgbLum;
		*g = rgbLum;
		*b = rgbLum;
	} else {
		return 1;
	}
	return 0;
}