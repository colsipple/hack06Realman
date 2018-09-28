/*
 *Author(s): Victor Nguyen, Collin Sipple, Joe Wyrick
 *Date Created: 09/27/2018
 *Date Modified: 09/27/2018
 *Purpose: Provide Functions to convert color coordinates into different systems.
 */

 typedef enum {
	AVERAGE,
	LIGHTNESS,
	LUMINOSITY,
} Mode;

//RGB to CMYK
int rgbToCMYK(int r, int g, int b, double *c, double *m, double *y, double *k);

//CMYK to RGB
int cmykToRGB(int *r, int *g, int *b, double c, double m, double y, double k);

//RGB to grayscale for three different methods
int toGrayScale(int *r, int *g, int *b, Mode m);

//Find the maximum and minimum of two integers
int intmax(int a, int b);

int intmin(int a, int b);