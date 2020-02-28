//
// Created by masy on 04.02.20.
//

#ifndef CEDAR_VECTOR2F_H
#define CEDAR_VECTOR2F_H

namespace cedar
{

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

		inline friend Vector2f operator-(const Vector2f &lhs, const Vector2f &rhs)
		{
			return Vector2f(lhs.x - rhs.x, lhs.y - rhs.y);
		};

		inline friend Vector2f operator*(const Vector2f &lhs, const Vector2f &rhs)
		{
			return Vector2f(lhs.x * rhs.x, lhs.y * rhs.y);
		};

		inline friend Vector2f operator/(const Vector2f &lhs, const Vector2f &rhs)
		{
			return Vector2f(lhs.x / rhs.x, lhs.y / rhs.y);
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

#endif //CEDAR_VECTOR2F_H
