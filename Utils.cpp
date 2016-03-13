/*
 * Utils.cpp
 *
 * Implements member functions from class Utils, see file 'Utils.h'.
 */
#include "Utils.h"

/*
 * Static member declarations
 *
 * PI - Approximation for pi
 */
const double Utils::PI = 3.14159265359;

/*
 * Calculate the absolute value of an integer.
 */
int Utils::abs(int value) {
	return value >= 0 ? value : -value;
}

/*
 * Calculate the absolute value of a double.
 */
double Utils::abs(double value) {
	return value >= 0 ? value : -value;
}

/*
 * Convert an angle in radians to degrees.
 */
double Utils::to_degrees(double value_in_radians) {
	return value_in_radians*180/PI;
}

/*
 * Convert an angle in degrees to radians.
 */
double Utils::to_radians(double value_in_degrees) {
	return value_in_degrees*PI/180;
}
