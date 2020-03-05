//
// Created by masy on 07.02.20.
//

#ifndef CEDAR_MATH_H
#define CEDAR_MATH_H

#include <cmath>

#define PI_2f32 __f32(6.283185307179586231995926937088370323)

/**
 * Base namespace of the cedar engine.
 */
namespace cedar
{

	/**
	 * Constant float of one degree in radians.
	 */
	static const float RADIANTf = M_PIf32 / 180.0f;
	/**
	 * Constant double of one degree in radians.
	 */
	static const double RADIANTd = M_PI / 180.0;
	/**
	 * Constant float of one radiant in degrees.
	 */
	static const float DEGREEf = 180.0f / M_PIf32;
	/**
	 * Constant double of one radiant in degrees.
	 */
	static const double DEGREEd = 180.0 / M_PI;

	/**
	 * Calculates the inverse square root of the given value.
	 *
	 * @param value The value the inverse square root will be calculated of.
	 * @return the inverse square root of the given value.
	 */
	inline float invSqrt(const float value)
	{
		return 1.0f / std::sqrt(value);
	}

	/**
	 * Calculates the inverse square root of the given value.
	 *
	 * @param value The value the inverse square root will be calculated of.
	 * @return the inverse square root of the given value.
	 */
	inline double invSqrt(const double value)
	{
		return 1.0 / std::sqrt(value);
	}

	/**
	 * Converts the given angle from degrees to radians.
	 *
	 * @param degrees The angle that will be converted.
	 * @return the angle in radians.
	 */
	inline float toRadians(const float degrees)
	{
		return degrees * RADIANTf;
	}

	/**
	 * Converts the given angle from degrees to radians.
	 *
	 * @param degrees The angle that will be converted.
	 * @return the angle in radians.
	 */
	inline double toRadians(const double degrees)
	{
		return degrees * RADIANTd;
	}

	/**
	 * Converts the given angle from radians to degrees.
	 *
	 * @param radiant The angle that will be converted.
	 * @return the angle in degrees.
	 */
	inline float toDegrees(const float radiant)
	{
		return radiant * DEGREEf;
	}

	/**
	 * Converts the given angle from radians to degrees.
	 *
	 * @param radiant The angle that will be converted.
	 * @return the angle in degrees.
	 */
	inline double toDegrees(const double radiant)
	{
		return radiant * DEGREEd;
	}

	/**
	 * Linearly interpolates <code>a</code> and <code>b</code> with factor <code>t</code>.
	 *
	 * @param a The first value that represents <code>t = 0.0</code>
	 * @param b The second value that represents <code>t = 1.0</code>
	 * @param t The factor of the interpolation.
	 * @return the linearly interpolated value.
	 */
	inline float lerp(const float a, const float b, const float t)
	{
		return std::fmaf(b - a, t, a);
	}

	/**
	 * Linearly interpolates <code>a</code> and <code>b</code> with factor <code>t</code>.
	 *
	 * @param a The first value that represents <code>t = 0.0</code>
	 * @param b The second value that represents <code>t = 1.0</code>
	 * @param t The factor of the interpolation.
	 * @return the linearly interpolated value.
	 */
	inline double lerp(const double a, const double b, const double t)
	{
		return std::fma(b - a, t, a);
	}

	/**
	 * Clamps the given value between <code>min</code> and <code>max</code>.
	 *
	 * @param value The value that will be clamped.
	 * @param min The min boundary of the value.
	 * @param max The max boundary of the value.
	 * @return the clamped value.
	 */
	inline float clamp(const float value, const float min, const float max)
	{
		return value < min ? min : (value > max ? max : value);
	}

	/**
	 * Clamps the given value between <code>min</code> and <code>max</code>.
	 *
	 * @param value The value that will be clamped.
	 * @param min The min boundary of the value.
	 * @param max The max boundary of the value.
	 * @return the clamped value.
	 */
	inline double clamp(const double value, const double min, const double max)
	{
		return value < min ? min : (value > max ? max : value);
	}

	/**
	 * Floors the given value and returns it as integer.
	 *
	 * @param value The value that will be floored.
	 * @return the floored integer.
	 */
	inline int fastFloor(const float value)
	{
		int _value = static_cast<int>(value);
		return value < _value ? _value - 1 : _value;
	}

	/**
	 * Floors the given value and returns it as integer.
	 *
	 * @param value The value that will be floored.
	 * @return the floored integer.
	 */
	inline int fastFloor(const double value)
	{
		int _value = static_cast<int>(value);
		return value < _value ? _value - 1 : _value;
	}

};


#endif //CEDAR_MATH_H
