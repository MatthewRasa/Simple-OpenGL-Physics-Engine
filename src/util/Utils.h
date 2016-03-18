/*
 * Utils.h
 *
 * Header file for Utils.cpp, defines class Utils.
 */
#ifndef UTILS_H_
#define UTILS_H_

#include <cmath>
#include "string.h"

/*
 * Class containing static utility functions.
 */
class Utils {
public:

	/*
	 * PI - Approximation for pi
	 */
	static const double PI;

	/*
	 * Calculate the absolute value of an integer.
	 */
	static int abs(int value);

	/*
	 * Calculate the absolute value of a double.
	 */
	static double abs(double value);

	template<typename T>
	static T *arrcpy(T *rp_dest, T *p_src, int length) {
		for (int i = 0; i < length; i++)
			rp_dest[i] = p_src[i];
		return rp_dest;
	}

	/*
	 * Convert an angle in radians to degrees.
	 */
	static double to_degrees(double value_in_radians);

	/*
	 * Convert an angle in degrees to radians.
	 */
	static double to_radians(double value_in_degrees);

};

#endif
