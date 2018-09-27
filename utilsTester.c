/*
 *Author(s): Victor Nguyen, Collin Sipple, Joe Wyrick
 *Date Created: 09/27/2018
 *Date Modified: 09/27/2018
 *Purpose: Hard code test cases to ensure correctness of utils.c
 */

#include<stdlib.h>
#include<stdio.h>
#include<math.h>
#include"utils.h"
#define E 0.01

int main(int argc, char **argv) {
	double c, m, y, k;
	int numCase = 0;
	int casePassed = 0;
	//Test for function rgbToCMYK()
	//Test 1: 65, 71, 30
	int error = rgbToCMYK(65, 71, 30, &c, &m, &y, &k);
	numCase++;
	if(fabs(0.08 - c) < E) {
		printf("Test Case 1 Passed!\n");
		casePassed++;
	} else {
		printf("Test Case 1 Failed! Your output was %f.\n", c);
	}
	
	numCase++;
	if(fabs(0 - m) < E) {
		printf("Test Case 2 Passed!\n");
		casePassed++;
	} else {
		printf("Test Case 2 Failed! Your output was %f.\n", m);
	}
	
	numCase++;
	if(fabs(0.58 - y) < E) {
		printf("Test Case 3 Passed!\n");
		casePassed++;
	} else {
		printf("Test Case 3 Failed! Your output was %f.\n", y);
	}
	
	numCase++;
	if(fabs(0.72 - k) < E) {
		printf("Test Case 4 Passed!\n");
		casePassed++;
	} else {
		printf("Test Case 4 Failed! Your output was %f.\n", k);
	}
	
	//Test for function cmykToRGB()
	//Test 2: 0.5, 0.25, 0.0, 0.1
	int r, g, b;
	error = cmykToRGB(0.5, 0.25, 0.0, 0.1, &r, &g, &b);
	numCase++;
	if(abs(115 - r) < E) {
		printf("Test Case 5 Passed!\n");
		casePassed++;
	} else {
		printf("Test Case 5 Failed! Your output was %d.\n", r);
	}
	
	numCase++;
	if(abs(172 - g) < E) {
		printf("Test Case 6 Passed!\n");
		casePassed++;
	} else {
		printf("Test Case 6 Failed! Your output was %d.\n", g);
	}
	
	numCase++;
	if(abs(230 - b) < E) {
		printf("Test Case 7 Passed!\n");
		casePassed++;
	} else {
		printf("Test Case 7 Failed! Your output was %d.\n", b);
	}
	
	//Test for function toGrayScale() for all methods
	//Test 3: 188, 203, 34 all methods
	r = 188;
	g = 203;
	b = 34;
	error = toGrayScale(&r, &g, &b, AVERAGE);
	
	numCase++;
	if(abs(r - 142) < E) {
		printf("Test Case 8 Passed!\n");
		casePassed++;
	} else {
		printf("Test Case 8 Failed! Your output was %d.\n", r);
	}
	
	r = 188;
	g = 203;
	b = 34;
	error = toGrayScale(&r, &g, &b, LIGHTNESS);
	
	numCase++;
	if(abs(r - 119) < E) {
		printf("Test Case 9 Passed!\n");
		casePassed++;
	} else {
		printf("Test Case 9 Failed! Your output was %d.\n", r);
	}
	
	r = 188;
	g = 203;
	b = 34;
	error = toGrayScale(&r, &g, &b, LUMINOSITY);
	
	numCase++;
	if(abs(r - 188) < E) {
		printf("Test Case 10 Passed!\n");
		casePassed++;
	} else {
		printf("Test Case 10 Failed! Your output was %d.\n", r);
	}
	printf("You have passed %d out of %d cases.\n", casePassed, numCase);
	return 0;
}