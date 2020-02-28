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

void Quaternionf::identity()
{
	this->x = 0.0f;
	this->y = 0.0f;
	this->z = 0.0f;
	this->w = 0.0f;
}

void Quaternionf::normalize()
{
	float invNorm = math::invSqrt(std::fma(this->x, this->x, std::fma(this->y, this->y, std::fma(this->z, this->z, this->w * this->w))));
	this->x *= invNorm;
	this->y *= invNorm;
	this->z *= invNorm;
	this->w *= invNorm;
}

void Quaternionf::invert()
{
	float invNorm = math::invSqrt(std::fma(this->x, this->x, std::fma(this->y, this->y, std::fma(this->z, this->z, this->w * this->w))));
	this->x = (0.0f - this->x) * invNorm;
	this->y = (0.0f - this->y) * invNorm;
	this->z = (0.0f - this->z) * invNorm;
	this->w = this->w * invNorm;
}

void Quaternionf::rotateX(float angle)
{
	float halfAngle = angle * 0.5f;
	float sin = std::sin(halfAngle);
	float cos = std::cos(halfAngle);

	this->x = this->w * sin + this->x * cos;
	this->y = this->y * cos + this->z * sin;
	this->z = this->z * cos - this->y * sin;
	this->w = this->w * cos - this->x * sin;
}

void Quaternionf::rotateLocalX(float angle)
{
	float halfAngle = angle * 0.5f;
	float sin = std::sin(halfAngle);
	float cos = std::cos(halfAngle);

	this->x = this->x * cos + this->w * sin;
	this->y = this->y * cos - this->z * sin;
	this->z = this->z * cos + this->y * sin,
			this->w = this->w * cos - this->x * sin;
}

void Quaternionf::rotationX(float angle)
{
	float halfAngle = angle * 0.5f;
	this->x = std::sin(halfAngle);
	this->y = 0.0f;
	this->z = 0.0f;
	this->w = std::cos(halfAngle);
}

void Quaternionf::rotateY(float angle)
{
	float halfAngle = angle * 0.5f;
	float sin = std::sin(halfAngle);
	float cos = std::cos(halfAngle);

	this->x = this->x * cos - this->z * sin;
	this->y = this->w * sin + this->y * cos;
	this->z = this->x * sin + this->z * cos;
	this->w = this->w * cos - this->y * sin;
}

void Quaternionf::rotateLocalY(float angle)
{
	float halfAngle = angle * 0.5f;
	float sin = std::sin(halfAngle);
	float cos = std::cos(halfAngle);

	this->x = this->x * cos + this->z * sin;
	this->y = this->y * cos + this->w * sin;
	this->z = this->z * cos - this->x * sin;
	this->w = this->w * cos - this->y * sin;
}

void Quaternionf::rotationY(float angle)
{
	float halfAngle = angle * 0.5f;
	this->x = 0.0f;
	this->y = std::sin(halfAngle);
	this->z = 0.0f;
	this->w = std::cos(halfAngle);
}

void Quaternionf::rotateZ(float angle)
{
	float halfAngle = angle * 0.5f;
	float sin = std::sin(halfAngle);
	float cos = std::cos(halfAngle);

	this->x = this->x * cos + this->y * sin;
	this->y = this->y * cos - this->x * sin;
	this->z = this->w * sin + this->z * cos;
	this->w = this->w * cos - this->z * sin;
}

void Quaternionf::rotateLocalZ(float angle)
{
	float halfAngle = angle * 0.5f;
	float sin = std::sin(halfAngle);
	float cos = std::cos(halfAngle);

	this->x = this->x * cos - this->y * sin;
	this->y = this->y * cos + this->x * sin;
	this->z = this->z * cos + this->w * sin;
	this->w = this->w * cos - this->z * sin;
}

void Quaternionf::rotationZ(float angle)
{
	float halfAngle = angle * 0.5f;
	this->x = 0.0f;
	this->y = 0.0f;
	this->z = std::sin(halfAngle);
	this->w = std::cos(halfAngle);
}

void Quaternionf::rotate(float angleX, float angleY, float angleZ)
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

	float deltaX = cosX * cosYCosZ - sinX * sinYSinZ;
	float deltaY = sinX * cosYCosZ + cosX * sinYSinZ;
	float deltaZ = cosX * sinYCosZ - sinX * cosYSinZ;
	float deltaW = cosX * cosYSinZ + sinX * sinYCosZ;

	this->x = std::fma(this->w, deltaX, std::fma(this->x, deltaW, std::fma(this->y, deltaZ, (0.0f - this->z) * deltaY)));
	this->y = std::fma(this->w, deltaY, std::fma(0.0f - this->x, deltaZ, std::fma(this->y, deltaW, this->z * deltaX)));
	this->z = std::fma(this->w, deltaZ, std::fma(this->x, deltaY, std::fma(0.0f - this->y, deltaX, this->z * deltaW)));
	this->w = std::fma(this->w, deltaW, std::fma(0.0f - this->x, deltaX, std::fma(0.0f - this->y, y, (0.0f - this->z) * deltaZ)));
}

void Quaternionf::rotate(const Vector3f *angles)
{
	this->rotate(angles->x, angles->y, angles->z);
}

void Quaternionf::rotation(float angleX, float angleY, float angleZ)
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

	this->x = cosX * cosYCosZ - sinX * sinYSinZ;
	this->y = sinX * cosYCosZ + cosX * sinYSinZ;
	this->z = cosX * sinYCosZ - sinX * cosYSinZ;
	this->w = cosX * cosYSinZ + sinX * sinYCosZ;
}

void Quaternionf::rotation(const Vector3f *angles)
{
	this->rotation(angles->x, angles->y, angles->z);
}

void Quaternionf::rotateAxis(float angle, float axisX, float axisY, float axisZ)
{
	float halfAngle = angle * 0.5f;
	float sinHalfAngle = std::sin(halfAngle);
	float invAxisLength = math::invSqrt(axisX * axisX + axisY * axisY + axisZ * axisZ);

	float deltaX = axisX * invAxisLength * sinHalfAngle;
	float deltaY = axisY * invAxisLength * sinHalfAngle;
	float deltaZ = axisZ * invAxisLength * sinHalfAngle;
	float deltaW = std::cos(halfAngle);

	this->x = std::fma(this->w, deltaX, std::fma(this->x, deltaW, std::fma(this->y, deltaZ, (0.0f - this->z) * deltaY)));
	this->y = std::fma(this->w, deltaY, std::fma(0.0f - this->x, deltaZ, std::fma(this->y, deltaW, this->z * deltaX)));
	this->z = std::fma(this->w, deltaZ, std::fma(this->x, deltaY, std::fma(0.0f - this->y, deltaX, this->z * deltaW)));
	this->w = std::fma(this->w, deltaW, std::fma(0.0f - this->x, deltaX, std::fma(0.0f - this->y, y, (0.0f - this->z) * deltaZ)));
}

void Quaternionf::rotateAxis(float angle, const Vector3f *axis)
{
	return this->rotateAxis(angle, axis->x, axis->y, axis->z);
}

void Quaternionf::rotationAxis(float angle, float axisX, float axisY, float axisZ)
{
	float halfAngle = angle * 0.5f;
	float sinHalfAngle = std::sin(halfAngle);
	float invAxisLength = math::invSqrt(axisX * axisX + axisY * axisY + axisZ * axisZ);

	this->x = axisX * invAxisLength * sinHalfAngle;
	this->y = axisY * invAxisLength * sinHalfAngle;
	this->z = axisZ * invAxisLength * sinHalfAngle;
	this->w = std::cos(halfAngle);
}

void Quaternionf::rotationAxis(float angle, const Vector3f *axis)
{
	this->rotationAxis(angle, axis->x, axis->y, axis->z);
}

void Quaternionf::transform(const float vecX, const float vecY, const float vecZ, Vector3f *dest) const
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

	dest->x = std::fma((xSquared - ySquared - zSquared + wSquared) * k, vecX, std::fma(2 * (xy - zw) * k, vecY, (2 * (xz + yw) * k) * vecZ));
	dest->y = std::fma(2 * (xy + zw) * k, vecX, std::fma((ySquared - xSquared - zSquared + wSquared) * k, vecY, (2 * (yz - xw) * k) * z));
	dest->z = std::fma(2 * (xz - yw) * k, vecX, std::fma(2 * (yz * zw) * k, vecY, ((zSquared - xSquared - ySquared - wSquared) * k) * z));
}

Vector3f *Quaternionf::getEulerAngles(Vector3f *result)
{
	float ySquared = this->y * this->y;
	result->x = std::atan2(2.0f * (this->x * this->w - this->y * this->z), 1.0f - 2.0f * (this->x * this->x + ySquared));
	result->y = std::asin(2.0f * (this->x * this->z + this->y * this->w));
	result->z = std::atan2(2.0f * (this->z * this->w - this->x * this->y), 1.0f - 2.0f * (ySquared + this->z * this->z));
	return result;
}

Quaternionf *Quaternionf::slerp(const Quaternionf *other, Quaternionf *dest, float t) const
{
	float cosom = std::fma(this->x, other->x, std::fma(this->y, other->y, std::fma(this->z, other->z, this->w * other->w)));
	float absCosom = std::abs(cosom);
	float scale0;
	float scale1;
	if (1.0f - absCosom > 1E-6f)
	{
		float sinSqr = 1.0f - absCosom * absCosom;
		float invSinSqr = math::invSqrt(sinSqr);
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
	dest->x = std::fma(scale0, this->x, scale1 * other->x);
	dest->y = std::fma(scale0, this->y, scale1 * other->y);
	dest->z = std::fma(scale0, this->z, scale1 * other->z);
	dest->w = std::fma(scale0, this->w, scale1 * other->w);
	return dest;
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