//
// Created by masy on 04.02.20.
//

#ifndef CEDAR_VECTOR2F_HPP
#define CEDAR_VECTOR2F_HPP

/**
 * Base namespace of the cedar engine.
 */
namespace cedar
{

	/**
	 * 2 dimensional float vector implementation based on <a href="https://github.com/JOML-CI/JOML">JOML</a>.
	 */
	class Vector2f
	{
	public:
		float x;
		float y;

		Vector2f();

		explicit Vector2f(float value);

		Vector2f(float x, float y);

		Vector2f(const Vector2f &copy);

		[[nodiscard]] float length() const;

		[[nodiscard]] float lengthSquared() const;

		void normalize();

		[[nodiscard]] float distance(const Vector2f &other) const;

		[[nodiscard]] float distanceSquared(const Vector2f &other) const;

		[[nodiscard]] float dot(const Vector2f &other) const;

		Vector2f &operator=(const Vector2f &other);

		Vector2f &operator+=(const Vector2f &other);

		Vector2f &operator-=(const Vector2f &other);

		Vector2f &operator*=(const Vector2f &other);

		Vector2f &operator/=(const Vector2f &other);

		inline friend Vector2f operator+(const Vector2f &lhs, const Vector2f &rhs)
		{
			return Vector2f(lhs.x + rhs.x, lhs.y + rhs.y);
		};

		inline friend Vector2f operator+(const float lhs, const Vector2f &rhs)
		{
			return Vector2f(lhs + rhs.x, lhs + rhs.y);
		};

		inline friend Vector2f operator+(const Vector2f &lhs, const float rhs)
		{
			return Vector2f(lhs.x + rhs, lhs.y + rhs);
		};

		inline friend Vector2f operator-(const Vector2f &rhs)
		{
			return Vector2f(-rhs.x, -rhs.y);
		};

		inline friend Vector2f operator-(const Vector2f &lhs, const Vector2f &rhs)
		{
			return Vector2f(lhs.x - rhs.x, lhs.y - rhs.y);
		};

		inline friend Vector2f operator-(const float lhs, const Vector2f &rhs)
		{
			return Vector2f(lhs - rhs.x, lhs - rhs.y);
		};

		inline friend Vector2f operator-(const Vector2f &lhs, const float rhs)
		{
			return Vector2f(lhs.x - rhs, lhs.y - rhs);
		};

		inline friend Vector2f operator*(const Vector2f &lhs, const Vector2f &rhs)
		{
			return Vector2f(lhs.x * rhs.x, lhs.y * rhs.y);
		};

		inline friend Vector2f operator*(const float lhs, const Vector2f &rhs)
		{
			return Vector2f(lhs * rhs.x, lhs * rhs.y);
		};

		inline friend Vector2f operator*(const Vector2f &lhs, const float rhs)
		{
			return Vector2f(lhs.x * rhs, lhs.y * rhs);
		};

		inline friend Vector2f operator/(const Vector2f &lhs, const Vector2f &rhs)
		{
			return Vector2f(lhs.x / rhs.x, lhs.y / rhs.y);
		};

		inline friend Vector2f operator/(const float lhs, const Vector2f &rhs)
		{
			return Vector2f(lhs / rhs.x, lhs / rhs.y);
		};

		inline friend Vector2f operator/(const Vector2f &lhs, const float rhs)
		{
			return Vector2f(lhs.x / rhs, lhs.y / rhs);
		};

		inline friend bool operator==(const Vector2f &lhs, const Vector2f &rhs)
		{
			return lhs.x == rhs.x && lhs.y == rhs.y;
		};

		inline friend bool operator!=(const Vector2f &lhs, const Vector2f &rhs)
		{
			return !(lhs == rhs);
		};

		inline friend bool operator<(const Vector2f &lhs, const Vector2f &rhs)
		{
			return lhs.lengthSquared() < rhs.lengthSquared();
		};

		inline friend bool operator>(const Vector2f &lhs, const Vector2f &rhs)
		{
			return lhs.lengthSquared() > rhs.lengthSquared();
		};

		inline friend bool operator<=(const Vector2f &lhs, const Vector2f &rhs)
		{
			return lhs.lengthSquared() <= rhs.lengthSquared();
		};

		inline friend bool operator>=(const Vector2f &lhs, const Vector2f &rhs)
		{
			return lhs.lengthSquared() >= rhs.lengthSquared();
		};

	};

}

#endif //CEDAR_VECTOR2F_HPP
