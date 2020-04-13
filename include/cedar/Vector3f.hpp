//
// Created by masy on 04.02.20.
//

#ifndef CEDAR_VECTOR3F_HPP
#define CEDAR_VECTOR3F_HPP

#include "Vector2f.hpp"

/**
 * Base namespace of the cedar engine.
 */
namespace cedar
{

	/**
	 * 3 dimensional float vector implementation based on <a href="https://github.com/JOML-CI/JOML">JOML</a>.
	 */
	class Vector3f
	{
	public:
		float x;
		float y;
		float z;

		Vector3f();

		explicit Vector3f(float value);

		Vector3f(const Vector2f &xy, float z);

		Vector3f(float x, float y, float z);

		Vector3f(const Vector3f &other);

		[[nodiscard]] float length() const;

		[[nodiscard]] float invLength() const;

		[[nodiscard]] float lengthSquared() const;

		Vector3f *normalize();

		Vector3f *zero();

		Vector3f *negate();

		[[nodiscard]] float distance(const Vector3f &other) const;

		[[nodiscard]] float distanceSquared(const Vector3f &other) const;

		[[nodiscard]] float dot(const Vector3f &other) const;

		Vector3f lerp(const Vector3f &other, float t) const;

		Vector3f *lerp(const Vector3f &other, Vector3f *result, float t) const;

		void crossP(const Vector3f &other, Vector3f *result) const;

		void rotateX(float angle);

		void rotateY(float angle);

		void rotateZ(float angle);

		Vector2f xy() const;

		Vector2f *xy(Vector2f *storage) const;

		Vector2f yz() const;

		Vector2f *yz(Vector2f *storage) const;

		Vector2f xz() const;

		Vector2f *xz(Vector2f *storage) const;

		Vector3f &operator=(const Vector3f &other);

		Vector3f &operator+=(const Vector3f &other);

		Vector3f &operator+=(float value);

		Vector3f &operator-=(const Vector3f &other);

		Vector3f &operator-=(float value);

		Vector3f &operator*=(const Vector3f &other);

		Vector3f &operator*=(float value);

		Vector3f &operator/=(const Vector3f &other);

		Vector3f &operator/=(float value);

		inline friend Vector3f operator+(const Vector3f &lhs, const Vector3f &rhs)
		{
			return Vector3f(lhs.x + rhs.x, lhs.y + rhs.y, lhs.z + rhs.z);
		};

		inline friend Vector3f operator+(const float lhs, const Vector3f &rhs)
		{
			return Vector3f(lhs + rhs.x, lhs + rhs.y, lhs + rhs.z);
		};

		inline friend Vector3f operator+(const Vector3f &lhs, const float rhs)
		{
			return Vector3f(lhs.x + rhs, lhs.y + rhs, lhs.z + rhs);
		};

		inline friend Vector3f operator-(const Vector3f &lhs, const Vector3f &rhs)
		{
			return Vector3f(lhs.x - rhs.x, lhs.y - rhs.y, lhs.z - rhs.z);
		};

		inline friend Vector3f operator-(const float lhs, const Vector3f &rhs)
		{
			return Vector3f(lhs - rhs.x, lhs - rhs.y, lhs - rhs.z);
		};

		inline friend Vector3f operator-(const Vector3f &rhs)
		{
			return Vector3f(-rhs.x, -rhs.y, -rhs.z);
		}

		inline friend Vector3f operator-(const Vector3f &lhs, const float rhs)
		{
			return Vector3f(lhs.x - rhs, lhs.y - rhs, lhs.z - rhs);
		};

		inline friend Vector3f operator*(const Vector3f &lhs, const Vector3f &rhs)
		{
			return Vector3f(lhs.x * rhs.x, lhs.y * rhs.y, lhs.z * rhs.z);
		};

		inline friend Vector3f operator*(const float lhs, const Vector3f &rhs)
		{
			return Vector3f(lhs * rhs.x, lhs * rhs.y, lhs * rhs.z);
		};

		inline friend Vector3f operator*(const Vector3f &lhs, const float rhs)
		{
			return Vector3f(lhs.x * rhs, lhs.y * rhs, lhs.z * rhs);
		};

		inline friend Vector3f operator/(const Vector3f &lhs, const Vector3f &rhs)
		{
			return Vector3f(lhs.x / rhs.x, lhs.y / rhs.y, lhs.z / rhs.z);
		};

		inline friend Vector3f operator/(const float lhs, const Vector3f &rhs)
		{
			return Vector3f(lhs / rhs.x, lhs / rhs.y, lhs / rhs.z);
		};

		inline friend Vector3f operator/(const Vector3f &lhs, const float rhs)
		{
			return Vector3f(lhs.x / rhs, lhs.y / rhs, lhs.z / rhs);
		};

		inline friend bool operator==(const Vector3f &lhs, const Vector3f &rhs)
		{
			return lhs.x == rhs.x && lhs.y == rhs.y && lhs.z == rhs.z;
		};

		inline friend bool operator!=(const Vector3f &lhs, const Vector3f &rhs)
		{
			return !(lhs == rhs);
		};

		inline friend bool operator<(const Vector3f &lhs, const Vector3f &rhs)
		{
			return lhs.lengthSquared() < rhs.lengthSquared();
		};

		inline friend bool operator>(const Vector3f &lhs, const Vector3f &rhs)
		{
			return lhs.lengthSquared() > rhs.lengthSquared();
		};

		inline friend bool operator<=(const Vector3f &lhs, const Vector3f &rhs)
		{
			return lhs.lengthSquared() <= rhs.lengthSquared();
		};

		inline friend bool operator>=(const Vector3f &lhs, const Vector3f &rhs)
		{
			return lhs.lengthSquared() >= rhs.lengthSquared();
		};
	};

}

#endif //CEDAR_VECTOR3F_HPP
