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
	}
	
	numCase++;
	if(fabs(0 - m) < E) {
		printf("Test Case 2 Passed!\n");
		casePassed++;
	}
	
	numCase++;
	if(fabs(0.58 - y) < E) {
		printf("Test Case 3 Passed!\n");
		casePassed++;
	}
	
	numCase++;
	if(fabs(0.72 - k) < E) {
		printf("Test Case 4 Passed!\n");
		casePassed++;
	}
	
	//Test for function cmykToRGB()
	//Test 2: 0.5, 0.25, 0.0, 0.1
	int r, g, b;
	error = cmykToRGB(0.5, 0.25, 0.0, 0.1, &r, &g, &b);
	numCase++;
	if(abs(115 - r) < E) {
		printf("Test Case 5 Passed!\n");
		casePassed++;
	}
	
	numCase++;
	if(abs(172 - g) < E) {
		printf("Test Case 6 Passed!\n");
		casePassed++;
	}
	
	numCase++;
	if(abs(230 - b) < E) {
		printf("Test Case 7 Passed!\n");
		casePassed++;
	}
	printf("You have passed %d out of %d cases.\n", casePassed, numCase);
	return 0;
}