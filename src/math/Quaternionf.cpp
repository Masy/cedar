//
// Created by masy on 07.02.20.
//

#include "cedar/Quaternionf.h"
#include "cedar/Math.h"
#include <cmath>

// Normally i wouldn't do this, but i guess in the implementation file of a class its's ok.
using namespace cedar;

Quaternionf::Quaternionf()
{
	this->x = 0.0f;
	this->y = 0.0f;
	this->z = 0.0f;
	this->w = 1.0f;
}

Quaternionf::Quaternionf(const float x, const float y, const float z, const float w)
{
	this->x = x;
	this->y = y;
	this->z = z;
	this->w = w;
}

Quaternionf::Quaternionf(const float *values)
{
	this->x = values[0];
	this->y = values[1];
	this->z = values[2];
	this->w = values[3];
}

Quaternionf::Quaternionf(const Quaternionf &copy)
{
	this->x = copy.x;
	this->y = copy.y;
	this->z = copy.z;
	this->w = copy.w;
}

Quaternionf *Quaternionf::identity()
{
	this->x = 0.0f;
	this->y = 0.0f;
	this->z = 0.0f;
	this->w = 1.0f;
	return this;
}

Quaternionf *Quaternionf::normalize()
{
	float invNorm = cedar::invSqrt(std::fmaf(this->x, this->x, std::fmaf(this->y, this->y, std::fmaf(this->z, this->z, this->w * this->w))));
	this->x *= invNorm;
	this->y *= invNorm;
	this->z *= invNorm;
	this->w *= invNorm;
	return this;
}

Quaternionf *Quaternionf::invert()
{
	float invNorm = cedar::invSqrt(std::fmaf(this->x, this->x, std::fmaf(this->y, this->y, std::fmaf(this->z, this->z, this->w * this->w))));
	this->x = (0.0f - this->x) * invNorm;
	this->y = (0.0f - this->y) * invNorm;
	this->z = (0.0f - this->z) * invNorm;
	this->w = this->w * invNorm;
	return this;
}

Quaternionf *Quaternionf::rotateX(float angle)
{
	float halfAngle = angle * 0.5f;
	float sin = std::sin(halfAngle);
	float cos = std::cos(halfAngle);

	float _x = std::fmaf(this->w, sin, this->x * cos);
	float _y = std::fmaf(this->y, cos, this->z * sin);
	float _z = std::fmaf(this->z, cos, (0.0f - this->y) * sin);
	float _w = std::fmaf(this->w, cos, (0.0f - this->x) * sin);

	this->x = _x;
	this->y = _y;
	this->z = _z;
	this->w = _w;
	return this;
}

Quaternionf *Quaternionf::rotateLocalX(float angle)
{
	float halfAngle = angle * 0.5f;
	float sin = std::sin(halfAngle);
	float cos = std::cos(halfAngle);

	float _x = std::fmaf(this->x, cos, this->w * sin);
	float _y = std::fmaf(this->y, cos, (0.0f - this->z) * sin);
	float _z = std::fmaf(this->z, cos, this->y * sin);
	float _w = std::fmaf(this->w, cos, (0.0f - this->x) * sin);

	this->x = _x;
	this->y = _y;
	this->z = _z,
	this->w = _w;
	return this;
}

Quaternionf *Quaternionf::rotationX(float angle)
{
	float halfAngle = angle * 0.5f;
	this->x = std::sin(halfAngle);
	this->y = 0.0f;
	this->z = 0.0f;
	this->w = std::cos(halfAngle);
	return this;
}

Quaternionf *Quaternionf::rotateY(float angle)
{
	float halfAngle = angle * 0.5f;
	float sin = std::sin(halfAngle);
	float cos = std::cos(halfAngle);

	float _x = std::fmaf(this->x, cos, (0.0f - this->z) * sin);
	float _y = std::fmaf(this->w, sin, this->y * cos);
	float _z = std::fmaf(this->x, sin, this->z * cos);
	float _w = std::fmaf(this->w, cos, (0.0f - this->y) * sin);

	this->x = _x;
	this->y = _y;
	this->z = _z;
	this->w = _w;
	return this;
}

Quaternionf *Quaternionf::rotateLocalY(float angle)
{
	float halfAngle = angle * 0.5f;
	float sin = std::sin(halfAngle);
	float cos = std::cos(halfAngle);

	float _x = std::fmaf(this->x, cos, this->z * sin);
	float _y = std::fmaf(this->y, cos, this->w * sin);
	float _z = std::fmaf(this->z, cos, (0.0f - this->x) * sin);
	float _w = std::fmaf(this->w, cos, (0.0f - this->y) * sin);

	this->x = _x;
	this->y = _y;
	this->z = _z;
	this->w = _w;
	return this;
}

Quaternionf *Quaternionf::rotationY(float angle)
{
	float halfAngle = angle * 0.5f;
	this->x = 0.0f;
	this->y = std::sin(halfAngle);
	this->z = 0.0f;
	this->w = std::cos(halfAngle);
	return this;
}

Quaternionf *Quaternionf::rotateZ(float angle)
{
	float halfAngle = angle * 0.5f;
	float sin = std::sin(halfAngle);
	float cos = std::cos(halfAngle);

	float _x = std::fmaf(this->x, cos, this->y * sin);
	float _y = std::fmaf(this->y, cos, (0.0f - this->x) * sin);
	float _z = std::fmaf(this->w, sin, this->z * cos);
	float _w = std::fmaf(this->w, cos, (0.0f - this->z) * sin);

	this->x = _x;
	this->y = _y;
	this->z = _z;
	this->w = _w;
	return this;
}

Quaternionf *Quaternionf::rotateLocalZ(float angle)
{
	float halfAngle = angle * 0.5f;
	float sin = std::sin(halfAngle);
	float cos = std::cos(halfAngle);

	float _x = std::fmaf(this->x, cos, (0.0f - this->y) * sin);
	float _y = std::fmaf(this->y, cos, this->x * sin);
	float _z = std::fmaf(this->z, cos, this->w * sin);
	float _w = std::fmaf(this->w, cos, (0.0f - this->z) * sin);

	this->x = _x;
	this->y = _y;
	this->z = _z;
	this->w = _w;
	return this;
}

Quaternionf *Quaternionf::rotationZ(float angle)
{
	float halfAngle = angle * 0.5f;
	this->x = 0.0f;
	this->y = 0.0f;
	this->z = std::sin(halfAngle);
	this->w = std::cos(halfAngle);
	return this;
}

Quaternionf *Quaternionf::rotate(float angleX, float angleY, float angleZ)
{
	float halfAngleX = angleX * 0.5f;
	float halfAngleY = angleY * 0.5f;
	float halfAngleZ = angleZ * 0.5f;
	float sinX = std::sin(halfAngleX);
	float sinY = std::sin(halfAngleY);
	float sinZ = std::sin(halfAngleZ);
	float cosX = std::cos(halfAngleX);
	float cosY = std::cos(halfAngleY);
	float cosZ = std::cos(halfAngleZ);

	float cosYCosZ = cosY * cosZ;
	float sinYSinZ = sinY * sinZ;
	float sinYCosZ = sinY * cosZ;
	float cosYSinZ = cosY * sinZ;

	float deltaW = cosX * cosYCosZ - sinX * sinYSinZ;
	float deltaX = sinX * cosYCosZ + cosX * sinYSinZ;
	float deltaY = cosX * sinYCosZ - sinX * cosYSinZ;
	float deltaZ = cosX * cosYSinZ + sinX * sinYCosZ;

	float _x = std::fmaf(this->w, deltaX, std::fmaf(this->x, deltaW, std::fmaf(this->y, deltaZ, (0.0f - this->z) * deltaY)));
	float _y = std::fmaf(this->w, deltaY, std::fmaf(0.0f - this->x, deltaZ, std::fmaf(this->y, deltaW, this->z * deltaX)));
	float _z = std::fmaf(this->w, deltaZ, std::fmaf(this->x, deltaY, std::fmaf(0.0f - this->y, deltaX, this->z * deltaW)));
	float _w = std::fmaf(this->w, deltaW, std::fmaf(0.0f - this->x, deltaX, std::fmaf(0.0f - this->y, deltaY, (0.0f - this->z) * deltaZ)));

	this->x = _x;
	this->y = _y;
	this->z = _z;
	this->w = _w;
	return this;
}

Quaternionf *Quaternionf::rotate(const Vector3f *angles)
{
	return this->rotate(angles->x, angles->y, angles->z);
}

Quaternionf *Quaternionf::rotation(float angleX, float angleY, float angleZ)
{
	float halfAngleX = angleX * 0.5f;
	float halfAngleY = angleY * 0.5f;
	float halfAngleZ = angleZ * 0.5f;
	float sinX = std::sin(halfAngleX);
	float sinY = std::sin(halfAngleY);
	float sinZ = std::sin(halfAngleZ);
	float cosX = std::cos(halfAngleX);
	float cosY = std::cos(halfAngleY);
	float cosZ = std::cos(halfAngleZ);

	float cosYCosZ = cosY * cosZ;
	float sinYSinZ = sinY * sinZ;
	float sinYCosZ = sinY * cosZ;
	float cosYSinZ = cosY * sinZ;

	this->x = sinX * cosYCosZ + cosX * sinYSinZ;
	this->y = cosX * sinYCosZ - sinX * cosYSinZ;
	this->z = cosX * cosYSinZ + sinX * sinYCosZ;
	this->w = cosX * cosYCosZ - sinX * sinYSinZ;
	return this;
}

Quaternionf *Quaternionf::rotation(const Vector3f &angles)
{
	return this->rotation(angles.x, angles.y, angles.z);
}

Quaternionf *Quaternionf::rotateAxis(float angle, float axisX, float axisY, float axisZ)
{
	float halfAngle = angle * 0.5f;
	float sinHalfAngle = std::sin(halfAngle);
	float invAxisLength = cedar::invSqrt(axisX * axisX + axisY * axisY + axisZ * axisZ);

	float deltaX = axisX * invAxisLength * sinHalfAngle;
	float deltaY = axisY * invAxisLength * sinHalfAngle;
	float deltaZ = axisZ * invAxisLength * sinHalfAngle;
	float deltaW = std::cos(halfAngle);

	float _x = std::fmaf(this->w, deltaX, std::fmaf(this->x, deltaW, std::fmaf(this->y, deltaZ, (0.0f - this->z) * deltaY)));
	float _y = std::fmaf(this->w, deltaY, std::fmaf(0.0f - this->x, deltaZ, std::fmaf(this->y, deltaW, this->z * deltaX)));
	float _z = std::fmaf(this->w, deltaZ, std::fmaf(this->x, deltaY, std::fmaf(0.0f - this->y, deltaX, this->z * deltaW)));
	float _w = std::fmaf(this->w, deltaW, std::fmaf(0.0f - this->x, deltaX, std::fmaf(0.0f - this->y, deltaY, (0.0f - this->z) * deltaZ)));

	this->x = _x;
	this->y = _y;
	this->z = _z;
	this->w = _w;
	return this;
}

Quaternionf *Quaternionf::rotateAxis(float angle, const Vector3f &axis)
{
	return this->rotateAxis(angle, axis.x, axis.y, axis.z);
}

Quaternionf *Quaternionf::rotationAxis(float angle, float axisX, float axisY, float axisZ)
{
	float halfAngle = angle * 0.5f;
	float sinHalfAngle = std::sin(halfAngle);
	float invAxisLength = cedar::invSqrt(axisX * axisX + axisY * axisY + axisZ * axisZ);

	this->x = axisX * invAxisLength * sinHalfAngle;
	this->y = axisY * invAxisLength * sinHalfAngle;
	this->z = axisZ * invAxisLength * sinHalfAngle;
	this->w = std::cos(halfAngle);
	return this;
}

Quaternionf *Quaternionf::rotationAxis(float angle, const Vector3f &axis)
{
	return this->rotationAxis(angle, axis.x, axis.y, axis.z);
}

Vector3f *Quaternionf::transform(const float vecX, const float vecY, const float vecZ, Vector3f *storage) const
{
	float xSquared = this->x * this->x;
	float ySquared = this->y * this->y;
	float zSquared = this->z * this->z;
	float wSquared = this->w * this->w;
	float xy = this->x * this->y;
	float xz = this->x * this->z;
	float xw = this->x * this->w;
	float yz = this->y * this->z;
	float yw = this->y * this->w;
	float zw = this->z * this->w;
	float k = 1.0f / (xSquared + ySquared + zSquared + wSquared);

	storage->x = std::fmaf((xSquared - ySquared - zSquared + wSquared) * k, vecX, std::fmaf(2 * (xy - zw) * k, vecY, (2 * (xz + yw) * k) * vecZ));
	storage->y = std::fmaf(2 * (xy + zw) * k, vecX, std::fmaf((ySquared - xSquared - zSquared + wSquared) * k, vecY, (2 * (yz - zw) * k) * vecZ));
	storage->z = std::fmaf(2 * (xz - yw) * k, vecX, std::fmaf(2 * (yz + xw) * k, vecY, ((zSquared - xSquared - ySquared + wSquared) * k) * vecZ));
	return storage;
}

Vector3f *Quaternionf::getEulerAngles(Vector3f *result) const
{
	float ySquared = this->y * this->y;
	result->x = std::atan2(2.0f * (this->x * this->w - this->y * this->z), 1.0f - 2.0f * (this->x * this->x + ySquared));
	result->y = std::asin(2.0f * (this->x * this->z + this->y * this->w));
	result->z = std::atan2(2.0f * (this->z * this->w - this->x * this->y), 1.0f - 2.0f * (ySquared + this->z * this->z));
	return result;
}

Quaternionf Quaternionf::slerp(const cedar::Quaternionf &other, float t) const
{
	float cosom = std::fmaf(this->x, other.x, std::fmaf(this->y, other.y, std::fmaf(this->z, other.z, this->w * other.w)));
	float absCosom = std::abs(cosom);
	float scale0;
	float scale1;
	if (1.0f - absCosom > 1E-6f)
	{
		float sinSqr = 1.0f - absCosom * absCosom;
		float invSinSqr = cedar::invSqrt(sinSqr);
		float omega = std::atan2(sinSqr * invSinSqr, absCosom);
		scale0 = static_cast<float>(std::sin((1.0 - t) * omega) * invSinSqr);
		scale1 = static_cast<float>(std::sin(t * omega) * invSinSqr);
	}
	else
	{
		scale0 = 1.0f - t;
		scale1 = t;
	}

	scale1 = cosom >= 0.0f ? scale1 : 0.0f - scale1;
	return Quaternionf(
			std::fmaf(scale0, this->x, scale1 * other.x),
			std::fmaf(scale0, this->y, scale1 * other.y),
			std::fmaf(scale0, this->z, scale1 * other.z),
			std::fmaf(scale0, this->w, scale1 * other.w)
			);
}

Quaternionf *Quaternionf::slerp(const Quaternionf &other, Quaternionf *storage, float t) const
{
	float cosom = std::fmaf(this->x, other.x, std::fmaf(this->y, other.y, std::fmaf(this->z, other.z, this->w * other.w)));
	float absCosom = std::abs(cosom);
	float scale0;
	float scale1;
	if (1.0f - absCosom > 1E-6f)
	{
		float sinSqr = 1.0f - absCosom * absCosom;
		float invSinSqr = cedar::invSqrt(sinSqr);
		float omega = std::atan2(sinSqr * invSinSqr, absCosom);
		scale0 = static_cast<float>(std::sin((1.0 - t) * omega) * invSinSqr);
		scale1 = static_cast<float>(std::sin(t * omega) * invSinSqr);
	}
	else
	{
		scale0 = 1.0f - t;
		scale1 = t;
	}

	scale1 = cosom >= 0.0f ? scale1 : 0.0f - scale1;
	storage->x = std::fmaf(scale0, this->x, scale1 * other.x);
	storage->y = std::fmaf(scale0, this->y, scale1 * other.y);
	storage->z = std::fmaf(scale0, this->z, scale1 * other.z);
	storage->w = std::fmaf(scale0, this->w, scale1 * other.w);
	return storage;
}
Quaternionf &Quaternionf::operator=(const Quaternionf &other) = default;

Quaternionf &Quaternionf::operator=(const float *values)
{
	this->x = values[0];
	this->y = values[1];
	this->z = values[2];
	this->w = values[3];
	return *this;
}

Quaternionf &Quaternionf::operator+=(const Quaternionf &other)
{
	this->x += other.x;
	this->y += other.y;
	this->z += other.z;
	this->w += other.w;
	return *this;
}

Quaternionf &Quaternionf::operator*=(const Quaternionf &other)
{
	this->x *= other.x;
	this->y *= other.y;
	this->z *= other.z;
	this->w *= other.w;
	return *this;
}

bool Quaternionf::operator==(const Quaternionf &other) {
	return this->x == other.x && this->y == other.y && this->z == other.z && this->w == other.w;
}