//
// Created by masy on 07.02.20.
//

#ifndef CEDAR_QUATERNIONF_HPP
#define CEDAR_QUATERNIONF_HPP

#include "Vector3f.hpp"

/**
 * Base namespace of the cedar engine.
 */
namespace cedar
{

	/**
	 * Float quaternion implementation based on <a href="https://github.com/JOML-CI/JOML">JOML</a>.
	 */
	class Quaternionf
	{
	public:
		float x;
		float y;
		float z;
		float w;

		Quaternionf();

		Quaternionf(float x, float y, float z, float w);

		explicit Quaternionf(const float *values);

		Quaternionf(const Quaternionf &copy);

		Quaternionf *identity();

		Quaternionf *normalize();

		Quaternionf *invert();

		Quaternionf *rotateX(float angle);

		Quaternionf *rotateLocalX(float angle);

		Quaternionf *rotationX(float angle);

		Quaternionf *rotateY(float angle);

		Quaternionf *rotateLocalY(float angle);

		Quaternionf *rotationY(float angle);

		Quaternionf *rotateZ(float angle);

		Quaternionf *rotateLocalZ(float angle);

		Quaternionf *rotationZ(float angle);

		Quaternionf *rotate(float angleX, float angleY, float angleZ);

		Quaternionf *rotate(const Vector3f *angles);

		Quaternionf *rotation(float angleX, float angleY, float angleZ);

		Quaternionf *rotation(const Vector3f &angles);

		Quaternionf *rotateAxis(float angle, float axisX, float axisY, float axisZ);

		Quaternionf *rotateAxis(float angle, const Vector3f &axis);

		Quaternionf *rotationAxis(float angle, float axisX, float axisY, float axisZ);

		Quaternionf *rotationAxis(float angle, const Vector3f &axis);

		Vector3f *transform(float x, float y, float z, Vector3f *storage) const;

		Vector3f *getEulerAngles(Vector3f *result) const;

		Quaternionf slerp(const Quaternionf &other, float t) const;

		Quaternionf *slerp(const Quaternionf &other, Quaternionf *storage, float t) const;

		Quaternionf &operator=(const Quaternionf &other);

		Quaternionf &operator=(const float *values);

		Quaternionf &operator+=(const Quaternionf &other);

		Quaternionf &operator*=(const Quaternionf &other);

		bool operator==(const Quaternionf &other);

		friend Quaternionf operator+(const Quaternionf &lhs, const Quaternionf &rhs)
		{
			return Quaternionf(lhs.x + rhs.x, lhs.y + rhs.y, lhs.z + rhs.z, lhs.w + rhs.w);
		}

		friend Quaternionf operator*(const Quaternionf &lhs, const Quaternionf &rhs)
		{
			return Quaternionf(lhs.x * rhs.x, lhs.y * rhs.y, lhs.z * rhs.z, lhs.w * rhs.w);
		}
	};

}

#endif //CEDAR_QUATERNIONF_HPP
