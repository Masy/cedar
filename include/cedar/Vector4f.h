//
// Created by masy on 04.02.20.
//

#ifndef CEDAR_VECTOR4F_H
#define CEDAR_VECTOR4F_H

#include "Vector3f.h"

/**
 * Base namespace of the cedar engine.
 */
namespace cedar
{

	/**
	 * 4 dimensional float vector implementation based on <a href="https://github.com/JOML-CI/JOML">JOML</a>.
	 */
	class Vector4f
	{
	public:
		float x;
		float y;
		float z;
		float w;

		Vector4f();

		explicit Vector4f(float value);

		Vector4f(const Vector3f &xyz, float w);

		Vector4f(const Vector2f &xy, const Vector2f &zw);

		Vector4f(float x, float y, float z, float w);

		Vector4f(const Vector4f &copy);

		[[nodiscard]] float length() const;

		[[nodiscard]] float lengthSquared() const;

		void normalize();

		[[nodiscard]] float distance(const Vector4f &other) const;

		[[nodiscard]] float distanceSquared(const Vector4f &other) const;

		[[nodiscard]] float dot(const Vector4f &other) const;

		Vector4f &operator=(const Vector4f &other);

		Vector4f &operator+=(const Vector4f &other);

		Vector4f &operator-=(const Vector4f &other);

		Vector4f &operator*=(const Vector4f &other);

		Vector4f &operator/=(const Vector4f &other);

		inline friend Vector4f operator+(const Vector4f &lhs, const Vector4f &rhs)
		{
			return Vector4f(lhs.x + rhs.x, lhs.y + rhs.y, lhs.z + rhs.z, lhs.w + rhs.w);
		};

		inline friend Vector4f operator-(const Vector4f &lhs, const Vector4f &rhs)
		{
			return Vector4f(lhs.x - rhs.x, lhs.y - rhs.y, lhs.z - rhs.z, lhs.w - rhs.w);
		};

		inline friend Vector4f operator*(const Vector4f &lhs, const Vector4f &rhs)
		{
			return Vector4f(lhs.x * rhs.x, lhs.y * rhs.y, lhs.z * rhs.z, lhs.w * rhs.w);
		};

		inline friend Vector4f operator/(const Vector4f &lhs, const Vector4f &rhs)
		{
			return Vector4f(lhs.x / rhs.x, lhs.y / rhs.y, lhs.z / rhs.z, lhs.w / rhs.w);
		};

		inline friend bool operator==(const Vector4f &lhs, const Vector4f &rhs)
		{
			return lhs.x == rhs.x && lhs.y == rhs.y && lhs.z == rhs.z && lhs.w == rhs.z;
		};

		inline friend bool operator!=(const Vector4f &lhs, const Vector4f &rhs)
		{
			return !(lhs == rhs);
		};

		inline friend bool operator<(const Vector4f &lhs, const Vector4f &rhs)
		{
			return lhs.lengthSquared() < rhs.lengthSquared();
		};

		inline friend bool operator>(const Vector4f &lhs, const Vector4f &rhs)
		{
			return lhs.lengthSquared() > rhs.lengthSquared();
		};

		inline friend bool operator<=(const Vector4f &lhs, const Vector4f &rhs)
		{
			return lhs.lengthSquared() <= rhs.lengthSquared();
		};

		inline friend bool operator>=(const Vector4f &lhs, const Vector4f &rhs)
		{
			return lhs.lengthSquared() >= rhs.lengthSquared();
		};
	};

}

#endif //CEDAR_VECTOR4F_H
