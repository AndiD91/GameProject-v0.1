#ifndef MATH_HELPER_H
#define MATH_HELPER_H
#include <math.h>
namespace Math
{
	const float M_PI=3.14159265358979323846F;
	
		inline double ToRadians(const double degree)
		{
			return degree* M_PI / 180.0;
		}


		inline double ToDegree(const double radian)
		{
			return radian * 180.0 / M_PI;
		}

}

#endif