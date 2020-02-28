//
// Created by masy on 07.02.20.
//

#ifndef CEDAR_QUATERNIONF_H
#define CEDAR_QUATERNIONF_H

#include "Vector3f.h"

namespace cedar
{

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

		void identity();

		void normalize();

		void invert();

		void rotateX(float angle);

		void rotateLocalX(float angle);

		void rotationX(float angle);

		void rotateY(float angle);

		void rotateLocalY(float angle);

		void rotationY(float angle);

		void rotateZ(float angle);

		void rotateLocalZ(float angle);

		void rotationZ(float angle);

		void rotate(float angleX, float angleY, float angleZ);

		void rotate(const Vector3f *angles);

		void rotation(float angleX, float angleY, float angleZ);

		void rotation(const Vector3f *angles);

		void rotateAxis(float angle, float axisX, float axisY, float axisZ);

		void rotateAxis(float angle, const Vector3f *axis);

		void rotationAxis(float angle, float axisX, float axisY, float axisZ);

		void rotationAxis(float angle, const Vector3f *axis);

		void transform(float x, float y, float z, Vector3f *dest) const;

		Vector3f *getEulerAngles(Vector3f *result);

		Quaternionf *slerp(const Quaternionf *other, Quaternionf *dest, float t) const;

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

#endif //CEDAR_QUATERNIONF_H
