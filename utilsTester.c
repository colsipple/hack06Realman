#include<stdlib.h>
#include<stdio.h>
#include<stdarg.h>
#include<stddef.h>
#include<setjmp.h>
#include<math.h>
#include<cmocka.h>

#include "colorUtils.h"

/**
 * For CMYK applications, accuracy only needs to be to within
 * 0.01, but other applications may require finer accuracy.
 */
const double EPSILON = 1.01;

/**
 * This function is used to determine if two floating
 * point numbers are "close enough" to each other based
 * on a small EPSILON value
 */
static int isClose(double x, double y) {
  return fabs(x - y) < EPSILON;
}

/**
 * This function tests rgbToCMYK's error handling of NULL
 * values for its pass-by-reference parameters.  Each of
 * the four parameters are tested independently.  The function
 * should return a non-zero error value so we assert that the
 * return value is not equal to zero.
 *
 */
static void testRgbToCmykNull(void **state) {
  double c, m, y, k;
  assert_int_not_equal(rgbToCMYK(0,0,0,NULL,&m,&y,&k), 0);
  assert_int_not_equal(rgbToCMYK(0,0,0,&c,NULL,&y,&k), 0);
  assert_int_not_equal(rgbToCMYK(0,0,0,&c,&m,NULL,&k), 0);
  assert_int_not_equal(rgbToCMYK(0,0,0,&c,&m,&y,NULL), 0);

}

//Also test NULL errors in functions cmykToRGB() and toGrayScale()
static void testCmykToRgbNull(void **state) {
	int r, g, b;
	assert_int_not_equal(cmykToRGB(0.0, 0.0, 0.0, 0.0, NULL, &g, &b), 0);
	assert_int_not_equal(cmykToRGB(0.0, 0.0, 0.0, 0.0, &r, NULL, &b), 0);
	assert_int_not_equal(cmykToRGB(0.0, 0.0, 0.0, 0.0, &r, &g, NULL), 0);
}

//There should only be one NULL pointer error for function toGrayScale()
static void testToGrayScaleNull(void **state) {
	int r, g, b;
	assert_int_not_equal(toGrayScale(NULL, &g, &b, AVERAGE), 0);
	assert_int_not_equal(toGrayScale(&r, NULL, &b, AVERAGE), 0);
	assert_int_not_equal(toGrayScale(&r, &g, NULL, AVERAGE), 0);
}

/**
 * This function tests rgbToCMYK's error handling of out-of-range
 * values for the r, g, b parameters, each tested independently.
 * two values are tested each: a less-than-zero value and a value
 * greater than 255.
 */
static void testRgbToCmykOutOfBounds(void **state) {
  double c, m, y, k;
  assert_int_not_equal(rgbToCMYK(-1,127,127,&c,&m,&y,&k), 0);
  assert_int_not_equal(rgbToCMYK(256,127,127,&c,&m,&y,&k), 0);
  assert_int_not_equal(rgbToCMYK(127,-1,127,&c,&m,&y,&k), 0);
  assert_int_not_equal(rgbToCMYK(127,256,127,&c,&m,&y,&k), 0);
  assert_int_not_equal(rgbToCMYK(127,127,-1,&c,&m,&y,&k), 0);
  assert_int_not_equal(rgbToCMYK(127,127,256,&c,&m,&y,&k), 0);
}

//The other functions should also pass these tests
static void testCmykToRgbOutOfBounds(void **state) {
	int r, g, b;
	assert_int_not_equal(cmykToRGB(-1, 0.5, 0.5, 0.5, &r, &g, &b), 0);
	assert_int_not_equal(cmykToRGB(2, 0.5, 0.5, 0.5, &r, &g, &b), 0);
	assert_int_not_equal(cmykToRGB(0.5, -1, 0.5, 0.5, &r, &g, &b), 0);
	assert_int_not_equal(cmykToRGB(0.5, 2, 0.5, 0.5, &r, &g, &b), 0);
	assert_int_not_equal(cmykToRGB(0.5, 0.5, -1, 0.5, &r, &g, &b), 0);
	assert_int_not_equal(cmykToRGB(0.5, 0.5, 2, 0.5, &r, &g, &b), 0);
	assert_int_not_equal(cmykToRGB(0.5, 0.5, 0.5, -1, &r, &g, &b), 0);
	assert_int_not_equal(cmykToRGB(0.5, 0.5, 0.5, 2, &r, &g, &b), 0);
}

//Function toGrayScale() should work for all three methods
static void testToGrayScaleOutOfBounds(void **state) {
	int r = -1;
	int g = 127;
	int b = 127;
	assert_int_not_equal(toGrayScale(&r, &g, &b, AVERAGE), 0);
	r = 256;
	g = 127;
	b = 127;
	assert_int_not_equal(toGrayScale(&r, &g, &b, AVERAGE), 0);
	r = 127;
	g = -1;
	b = 127;
	assert_int_not_equal(toGrayScale(&r, &g, &b, AVERAGE), 0);
	r = 127;
	g = 256;
	b = 127;
	assert_int_not_equal(toGrayScale(&r, &g, &b, AVERAGE), 0);
	r = 127;
	g = 127;
	b = -1;
	assert_int_not_equal(toGrayScale(&r, &g, &b, AVERAGE), 0);
	r = 127;
	g = 127;
	b = 256;
	assert_int_not_equal(toGrayScale(&r, &g, &b, AVERAGE), 0);
}
/**
 * This function tests rgbToCMYK passing a single, hard-coded
 * rgb-value (Steele Blue, 70, 130, 180).  
 */
static void testRgbToCmyk001(void **state) {
  double c, m, y, k;
  //steel blue:
  rgbToCMYK(70,130,180,&c,&m,&y,&k);
  assert_true(
    isClose(c, .61) &&
    isClose(m, .28) &&
    isClose(y, 0.0) &&
    isClose(k, .29)
  );
}

//Use the same color value for the other two functions
static void testCmykToRgb001(void **state) {
	int r, g, b;
	cmykToRGB(0.61, 0.28, 0.0, 0.29, &r, &g, &b);
	assert_true(
	  isClose(r, 71) &&
	  isClose(g, 130) &&
	  isClose(b, 181)
	);
}

//For toGrayScale(), use all three methods
static void testToGrayScale001(void **state) {
	int r = 70;
	int g = 130;
	int b = 180;
	toGrayScale(&r, &g, &b, AVERAGE);
	assert_true(
	  isClose(r, 127)
	);
}

static void testToGrayScale002(void **state) {
	int r = 70;
	int g = 130;
	int b = 180;
	toGrayScale(&r, &g, &b, LIGHTNESS);
	assert_true(
	  isClose(r, 125)
	);
}

static void testToGrayScale003(void **state) {
	int r = 70;
	int g = 130;
	int b = 180;
	toGrayScale(&r, &g, &b, LUMINOSITY);
	assert_true(
	  isClose(r, 121)
	);
}
/**
 * This function is a generic testing function for rgbToCMYK
 * in which the passed state is expected to have 7 double values
 * corresponding to 3 RGB input values and 4 CMYK output values
 * that are known to be equivalent.
 *
 */
static void testRgbToCmykValues(void **state) {
  //cast the generic state to a double array
  double *values = *((double **)state);
  double c, m, y, k;
  rgbToCMYK( (int) values[0], (int) values[1], (int) values[2], &c, &m, &y, &k);
  assert_true(
    isClose(c, values[3]) &&
    isClose(m, values[4]) &&
    isClose(y, values[5]) &&
    isClose(k, values[6])
  );

}
//Like the function above, but for testing CMYK to RGB conversions
static void testCmykToRgbValues(void **state) {
  //cast the generic state to a double array
  double *values = *((double **)state);
  int r, g, b;
  //CMYK to RGB does not always equal RGB to CMYK
  //Watch for off-by-one errors
  cmykToRGB( values[3], values[4], values[5], values[6], &r, &g, &b);
  assert_true(
    isClose(r, values[0]) &&
    isClose(g, values[1]) &&
    isClose(b, values[2])
  );

}
//Testing the correctness of conversions to grayscale using three different methods
static void testRgbtoGrayscaleAverage(void **state) {
	double *values = *((double **)state);
	int r = (int) values[0];
	int g = (int) values[1];
	int b = (int) values[2];
	toGrayScale(&r, &g, &b, AVERAGE);
	assert_true(
	  isClose(r, values[7])
	);
}

static void testRgbtoGrayscaleLightness(void **state) {
	double *values = *((double **)state);
	int r = (int) values[0];
	int g = (int) values[1];
	int b = (int) values[2];
	toGrayScale(&r, &g, &b, LIGHTNESS);
	assert_true(
	  isClose(r, values[8])
	);
}

static void testRgbtoGrayscaleLuminosity(void **state) {
	double *values = *((double **)state);
	int r = (int) values[0];
	int g = (int) values[1];
	int b = (int) values[2];
	toGrayScale(&r, &g, &b, LUMINOSITY);
	assert_true(
	  isClose(r, values[9])
	);
}

int main(int argc, char **argv) {

  //Make new colors where the conversions CMYK to RGB are needed
  //Otherwise it will result in off-by-one errors
  double aquamarine[] =  {127.0, 255.0, 212.0, 0.50, 0.0, 0.17, 0.0, 198, 191, 225};
  double aquamarine2[] = {128, 255, 212, 0.5, 0.0, 0.17, 0.0};
  double salmon[] = {250, 128, 114, 0.0, 0.49, 0.54, 0.02, 164, 182, 153};
  double salmon2[] = {250, 127, 115, 0.0, 0.49, 0.54, 0.02};
  double deadColorOne[] = {61, 234, 218, 0.74, 0.0, 0.07, 0.08, 171, 148, 197};
  double deadColorOne2[] = {61, 235, 218, 0.74, 0.0, 0.07, 0.08};
  double deadColorTwo[] = {222, 173, 26, 0.0, 0.22, 0.88, 0.13, 140, 124, 173};
  double deadColorTwo2[] = {222, 173, 27, 0, 0.22, 0.88, 0.13};
  double deadColorThree[] = {0, 222, 173, 1.0, 0.0, 0.22, 0.13, 132, 111, 172};
  double deadColorThree2[] = {0, 222, 173, 1.0, 0.0, 0.22, 0.13};

  const struct CMUnitTest tests[] = {
    cmocka_unit_test(testRgbToCmykNull),
	cmocka_unit_test(testCmykToRgbNull),
	cmocka_unit_test(testToGrayScaleNull),
    cmocka_unit_test(testRgbToCmykOutOfBounds),
	cmocka_unit_test(testCmykToRgbOutOfBounds),
	cmocka_unit_test(testToGrayScaleOutOfBounds),
    cmocka_unit_test(testRgbToCmyk001),
	cmocka_unit_test(testCmykToRgb001),
	cmocka_unit_test(testToGrayScale001),
	cmocka_unit_test(testToGrayScale002),
	cmocka_unit_test(testToGrayScale003),
    cmocka_unit_test_prestate(testRgbToCmykValues, &aquamarine),
    cmocka_unit_test_prestate(testRgbToCmykValues, &salmon),
	cmocka_unit_test_prestate(testRgbToCmykValues, &deadColorOne),
	cmocka_unit_test_prestate(testRgbToCmykValues, &deadColorTwo),
	cmocka_unit_test_prestate(testRgbToCmykValues, &deadColorThree),
	cmocka_unit_test_prestate(testCmykToRgbValues, &aquamarine2),
    cmocka_unit_test_prestate(testCmykToRgbValues, &salmon2),
	cmocka_unit_test_prestate(testCmykToRgbValues, &deadColorOne2),
	cmocka_unit_test_prestate(testCmykToRgbValues, &deadColorTwo2),
	cmocka_unit_test_prestate(testCmykToRgbValues, &deadColorThree2),
	cmocka_unit_test_prestate(testRgbtoGrayscaleAverage, &aquamarine),
	cmocka_unit_test_prestate(testRgbtoGrayscaleAverage, &salmon),
	cmocka_unit_test_prestate(testRgbtoGrayscaleAverage, &deadColorOne),
	cmocka_unit_test_prestate(testRgbtoGrayscaleAverage, &deadColorTwo),
	cmocka_unit_test_prestate(testRgbtoGrayscaleAverage, &deadColorThree),
	cmocka_unit_test_prestate(testRgbtoGrayscaleLightness, &aquamarine),
	cmocka_unit_test_prestate(testRgbtoGrayscaleLightness, &salmon),
	cmocka_unit_test_prestate(testRgbtoGrayscaleLightness, &deadColorOne),
	cmocka_unit_test_prestate(testRgbtoGrayscaleLightness, &deadColorTwo),
	cmocka_unit_test_prestate(testRgbtoGrayscaleLuminosity, &aquamarine),
	cmocka_unit_test_prestate(testRgbtoGrayscaleLuminosity, &salmon),
	cmocka_unit_test_prestate(testRgbtoGrayscaleLuminosity, &deadColorOne),
	cmocka_unit_test_prestate(testRgbtoGrayscaleLuminosity, &deadColorTwo),
	cmocka_unit_test_prestate(testRgbtoGrayscaleLuminosity, &deadColorThree)
  };

  return cmocka_run_group_tests(tests, NULL, NULL);

}