//
// Created by masy on 06.02.20.
//

#include "cedar/Matrix4f.h"

// Normally i wouldn't do this, but i guess in the implementation file of a class its's ok.
using namespace cedar;

Matrix4f::Matrix4f()
{
	// first column
	this->m_00 = 1.0f;
	this->m_01 = 0.0f;
	this->m_02 = 0.0f;
	this->m_03 = 0.0f;

	// second column
	this->m_10 = 0.0f;
	this->m_11 = 1.0f;
	this->m_12 = 0.0f;
	this->m_13 = 0.0f;

	// third column
	this->m_20 = 0.0f;
	this->m_21 = 0.0f;
	this->m_22 = 1.0f;
	this->m_23 = 0.0f;

	// fourth column
	this->m_30 = 0.0f;
	this->m_31 = 0.0f;
	this->m_32 = 0.0f;
	this->m_33 = 1.0f;
}

Matrix4f::Matrix4f(const float value)
{
	// first column
	this->m_00 = value;
	this->m_01 = value;
	this->m_02 = value;
	this->m_03 = value;

	// second column
	this->m_10 = value;
	this->m_11 = value;
	this->m_12 = value;
	this->m_13 = value;

	// third column
	this->m_20 = value;
	this->m_21 = value;
	this->m_22 = value;
	this->m_23 = value;

	// fourth column
	this->m_30 = value;
	this->m_31 = value;
	this->m_32 = value;
	this->m_33 = value;
}

Matrix4f::Matrix4f(const float *values)
{
	// first column
	this->m_00 = values[0];
	this->m_01 = values[1];
	this->m_02 = values[2];
	this->m_03 = values[3];

	// second column
	this->m_10 = values[4];
	this->m_11 = values[5];
	this->m_12 = values[6];
	this->m_13 = values[7];

	// third column
	this->m_20 = values[8];
	this->m_21 = values[9];
	this->m_22 = values[10];
	this->m_23 = values[11];

	// fourth column
	this->m_30 = values[12];
	this->m_31 = values[13];
	this->m_32 = values[14];
	this->m_33 = values[15];
}

Matrix4f::Matrix4f(const Matrix4f &copy)
{
	// first column
	this->m_00 = copy.m_00;
	this->m_01 = copy.m_01;
	this->m_02 = copy.m_02;
	this->m_03 = copy.m_03;

	// second column
	this->m_10 = copy.m_10;
	this->m_11 = copy.m_11;
	this->m_12 = copy.m_12;
	this->m_13 = copy.m_13;

	// third column
	this->m_20 = copy.m_20;
	this->m_21 = copy.m_21;
	this->m_22 = copy.m_22;
	this->m_23 = copy.m_23;

	// fourth column
	this->m_30 = copy.m_30;
	this->m_31 = copy.m_31;
	this->m_32 = copy.m_32;
	this->m_33 = copy.m_33;
}

Matrix4f::Matrix4f(const float nm00, const float nm01, const float nm02, const float nm03,
				   const float nm10, const float nm11, const float nm12, const float nm13,
				   const float nm20, const float nm21, const float nm22, const float nm23,
				   const float nm30, const float nm31, const float nm32, const float nm33)
{
	this->m_00 = nm00;
	this->m_01 = nm01;
	this->m_02 = nm02;
	this->m_03 = nm03;
	this->m_10 = nm10;
	this->m_11 = nm11;
	this->m_12 = nm12;
	this->m_13 = nm13;
	this->m_20 = nm20;
	this->m_21 = nm21;
	this->m_22 = nm22;
	this->m_23 = nm23;
	this->m_30 = nm30;
	this->m_31 = nm31;
	this->m_32 = nm32;
	this->m_33 = nm33;
}

void Matrix4f::zero()
{
	// first column
	this->m_00 = 0.0f;
	this->m_01 = 0.0f;
	this->m_02 = 0.0f;
	this->m_03 = 0.0f;

	// second column
	this->m_10 = 0.0f;
	this->m_11 = 0.0f;
	this->m_12 = 0.0f;
	this->m_13 = 0.0f;

	// third column
	this->m_20 = 0.0f;
	this->m_21 = 0.0f;
	this->m_22 = 0.0f;
	this->m_23 = 0.0f;

	// fourth column
	this->m_30 = 0.0f;
	this->m_31 = 0.0f;
	this->m_32 = 0.0f;
	this->m_33 = 0.0f;
}

void Matrix4f::identity()
{
	// first column
	this->m_00 = 1.0f;
	this->m_01 = 0.0f;
	this->m_02 = 0.0f;
	this->m_03 = 0.0f;

	// second column
	this->m_10 = 0.0f;
	this->m_11 = 1.0f;
	this->m_12 = 0.0f;
	this->m_13 = 0.0f;

	// third column
	this->m_20 = 0.0f;
	this->m_21 = 0.0f;
	this->m_22 = 1.0f;
	this->m_23 = 0.0f;

	// fourth column
	this->m_30 = 0.0f;
	this->m_31 = 0.0f;
	this->m_32 = 0.0f;
	this->m_33 = 1.0f;
}

void Matrix4f::invert()
{
	float a = this->m_00 * this->m_11 - this->m_01 * this->m_10;
	float b = this->m_00 * this->m_12 - this->m_02 * this->m_10;
	float c = this->m_00 * this->m_13 - this->m_03 * this->m_10;
	float d = this->m_01 * this->m_12 - this->m_02 * this->m_11;
	float e = this->m_01 * this->m_13 - this->m_03 * this->m_11;
	float f = this->m_02 * this->m_13 - this->m_03 * this->m_12;
	float g = this->m_20 * this->m_31 - this->m_21 * this->m_30;
	float h = this->m_20 * this->m_32 - this->m_22 * this->m_30;
	float i = this->m_20 * this->m_33 - this->m_23 * this->m_30;
	float j = this->m_21 * this->m_32 - this->m_22 * this->m_31;
	float k = this->m_21 * this->m_33 - this->m_23 * this->m_31;
	float l = this->m_22 * this->m_33 - this->m_23 * this->m_32;
	float det = a * l - b * k + c * j + d * i - e * h + f * g;
	det = 1.0f / det;
	float nm00 = ( m_11 * l - m_12 * k + m_13 * j) * det;
	float nm01 = (-m_01 * l + m_02 * k - m_03 * j) * det;
	float nm02 = ( m_31 * f - m_32 * e + m_33 * d) * det;
	float nm03 = (-m_21 * f + m_22 * e - m_23 * d) * det;
	float nm10 = (-m_10 * l + m_12 * i - m_13 * h) * det;
	float nm11 = ( m_00 * l - m_02 * i + m_03 * h) * det;
	float nm12 = (-m_30 * f + m_32 * c - m_33 * b) * det;
	float nm13 = ( m_20 * f - m_22 * c + m_23 * b) * det;
	float nm20 = ( m_10 * k - m_11 * i + m_13 * g) * det;
	float nm21 = (-m_00 * k + m_01 * i - m_03 * g) * det;
	float nm22 = ( m_30 * e - m_31 * c + m_33 * a) * det;
	float nm23 = (-m_20 * e + m_21 * c - m_23 * a) * det;
	float nm30 = (-m_10 * j + m_11 * h - m_12 * g) * det;
	float nm31 = ( m_00 * j - m_01 * h + m_02 * g) * det;
	float nm32 = (-m_30 * d + m_31 * b - m_32 * a) * det;
	float nm33 = ( m_20 * d - m_21 * b + m_22 * a) * det;

	this->m_00 = nm00;
	this->m_01 = nm01;
	this->m_02 = nm02;
	this->m_03 = nm03;
	this->m_10 = nm10;
	this->m_11 = nm11;
	this->m_12 = nm12;
	this->m_13 = nm13;
	this->m_20 = nm20;
	this->m_21 = nm21;
	this->m_22 = nm22;
	this->m_23 = nm23;
	this->m_30 = nm30;
	this->m_31 = nm31;
	this->m_32 = nm32;
	this->m_33 = nm33;
}

void Matrix4f::perspective(const float aspectRatio, const float fov, const float near, const float far)
{
	const float tangent = std::tan(fov * 0.5f);
	const float d = near - far;

	this->m_00 = 1.0f / (tangent * aspectRatio);
	this->m_01 = 0.0f;
	this->m_02 = 0.0f;
	this->m_03 = 0.0f;

	this->m_10 = 0.0f;
	this->m_11 = 1.0f / tangent;
	this->m_12 = 0.0f;
	this->m_13 = 0.0f;

	this->m_20 = 0.0f;
	this->m_21 = 0.0f;
	this->m_22 = (far + near) / d;
	this->m_23 = -1.0f;

	this->m_30 = 0.0f;
	this->m_31 = 0.0f;
	this->m_32 = (far + far) * near / d;
	this->m_33 = 0.0f;
}

void Matrix4f::orthographic(const float left, const float right, const float bottom, const float top, const float near, const float far)
{
	this->m_00 = 2.0f / (right - left);
	this->m_01 = 0.0f;
	this->m_02 = 0.0f;
	this->m_03 = 0.0f;

	this->m_10 = 0.0f;
	this->m_11 = 2.0f / (top - bottom);
	this->m_12 = 0.0f;
	this->m_13 = 0.0f;

	this->m_20 = 0.0f;
	this->m_21 = 0.0f;
	this->m_22 = 2.0f / (near - far);
	this->m_23 = 0.0f;

	this->m_30 = (right + left) / (left - right);
	this->m_31 = (top + bottom) / (bottom - top);
	this->m_32 = (far + near) / (near - far);
	this->m_33 = 1.0f;
}

void Matrix4f::translate(const float offsetX, const float offsetY, const float offsetZ)
{
	this->m_30 = this->m_00 * offsetX + this->m_10 * offsetY + this->m_20 * offsetZ + this->m_30;
	this->m_31 = this->m_01 * offsetX + this->m_11 * offsetY + this->m_21 * offsetZ + this->m_31;
	this->m_32 = this->m_02 * offsetX + this->m_12 * offsetY + this->m_22 * offsetZ + this->m_32;
	this->m_33 = this->m_03 * offsetX + this->m_13 * offsetY + this->m_23 * offsetZ + this->m_33;
}

void Matrix4f::translate(const Vector3f *offset)
{
	this->translate(offset->x, offset->y, offset->z);
}

void Matrix4f::translation(const float offsetX, const float offsetY, const float offsetZ)
{
	// first column
	this->m_00 = 1.0f;
	this->m_01 = 0.0f;
	this->m_02 = 0.0f;
	this->m_03 = 0.0f;

	// second column
	this->m_10 = 0.0f;
	this->m_11 = 1.0f;
	this->m_12 = 0.0f;
	this->m_13 = 0.0f;

	// third column
	this->m_20 = 0.0f;
	this->m_21 = 0.0f;
	this->m_22 = 1.0f;
	this->m_23 = 0.0f;

	// fourth column
	this->m_30 = offsetX;
	this->m_31 = offsetY;
	this->m_32 = offsetZ;
	this->m_33 = 1.0f;
}

void Matrix4f::translation(const Vector3f *offset)
{
	this->translation(offset->x, offset->y, offset->z);
}

void Matrix4f::rotate(const float angleX, const float angleY, const float angleZ)
{
	float sinX = std::sin(angleX);
	float cosX = std::cos(angleX);
	float sinY = std::sin(angleY);
	float cosY = std::cos(angleY);
	float sinZ = std::sin(angleZ);
	float cosZ = std::cos(angleZ);
	float nSinX = -sinX;
	float nSinY = -sinY;
	float nSinZ = -sinZ;

	float nm10 = this->m_10 * cosX + this->m_20 * sinX;
	float nm11 = this->m_11 * cosX + this->m_21 * sinX;
	float nm12 = this->m_12 * cosX + this->m_22 * sinX;
	float nm13 = this->m_13 * cosX + this->m_23 * sinX;
	float nm20 = this->m_10 * nSinX + this->m_20 * cosX;
	float nm21 = this->m_11 * nSinX + this->m_21 * cosX;
	float nm22 = this->m_12 * nSinX + this->m_22 * cosX;
	float nm23 = this->m_13 * nSinX + this->m_23 * cosX;
	float nm00 = this->m_00 * cosY + nm20 * nSinY;
	float nm01 = this->m_01 * cosY + nm21 * nSinY;
	float nm02 = this->m_02 * cosY + nm22 * nSinY;
	float nm03 = this->m_03 * cosY + nm23 * nSinY;

	this->m_20 = this->m_00 * sinY + nm20 * cosY;
	this->m_21 = this->m_01 * sinY + nm21 * cosY;
	this->m_22 = this->m_02 * sinY + nm22 * cosY;
	this->m_23 = this->m_03 * sinY + nm23 * cosY;
	this->m_10 = nm00 * nSinZ + nm10 * cosZ;
	this->m_11 = nm01 * nSinZ + nm11 * cosZ;
	this->m_12 = nm02 * nSinZ + nm12 * cosZ;
	this->m_13 = nm03 * nSinZ + nm13 * cosZ;
	this->m_00 = nm00 * cosZ + nm10 * sinZ;
	this->m_01 = nm01 * cosZ + nm11 * sinZ;
	this->m_02 = nm02 * cosZ + nm12 * sinZ;
	this->m_03 = nm03 * cosZ + nm13 * sinZ;
}

void Matrix4f::rotate(const Vector3f *angle)
{
	this->rotate(angle->x, angle->y, angle->z);
}

void Matrix4f::rotation(const float angleX, const float angleY, const float angleZ)
{
	float sinX = std::sin(angleX);
	float cosX = std::cos(angleX);
	float sinY = std::sin(angleY);
	float cosY = std::cos(angleY);
	float sinZ = std::sin(angleZ);
	float cosZ = std::cos(angleZ);
	float nSinX = -sinX;
	float nSinY = -sinY;
	float nSinZ = -sinZ;

	float nm01 = nSinX * nSinY;
	float nm02 = cosX * nSinY;

	// first column
	this->m_00 = cosY * cosZ;
	this->m_01 = nm01 * cosZ + cosX * sinZ;
	this->m_02 = nm02 * cosZ + sinX * sinZ;
	this->m_03 = 0.0f;

	// second column
	this->m_10 = cosY * nSinZ;
	this->m_11 = nm01 * nSinZ + cosX * cosZ;
	this->m_12 = nm02 * nSinZ + sinX * cosZ;
	this->m_13 = 0.0f;

	// third column
	this->m_20 = sinY;
	this->m_21 = nSinX * cosY;
	this->m_22 = cosX * cosY;
	this->m_23 = 0.0f;

	// fourth column
	this->m_30 = 0.0f;
	this->m_31 = 0.0f;
	this->m_32 = 0.0f;
	this->m_33 = 1.0f;
}

void Matrix4f::rotate(const Quaternionf *rotation)
{
	float xSquared = rotation->x * rotation->x;
	float ySquared = rotation->y * rotation->y;
	float zSquared = rotation->z * rotation->z;
	float wSquared = rotation->w * rotation->w;
	float zw = rotation->z * rotation->w;
	float xy = rotation->x * rotation->y;
	float xz = rotation->x * rotation->z;
	float yw = rotation->y * rotation->w;
	float yz = rotation->y * rotation->z;
	float xw = rotation->x * rotation->w;

	float rm00 = wSquared + xSquared - zSquared - ySquared;
	float rm01 = xy + zw + zw + xy;
	float rm02 = xz - yw + xz - yw;
	float rm10 = -zw + xy - zw + xy;
	float rm11 = ySquared - zSquared + wSquared - xSquared;
	float rm12 = yz + yz + xw + xw;
	float rm20 = yw + xz + xz + yw;
	float rm21 = yz + yz - xw - xw;
	float rm22 = zSquared - ySquared - xSquared + wSquared;
	float nm00 = this->m_00 * rm00 + this->m_10 * rm01 + this->m_20 * rm02;
	float nm01 = this->m_01 * rm00 + this->m_11 * rm01 + this->m_21 * rm02;
	float nm02 = this->m_02 * rm00 + this->m_12 * rm01 + this->m_22 * rm02;
	float nm03 = this->m_03 * rm00 + this->m_13 * rm01 + this->m_23 * rm02;
	float nm10 = this->m_00 * rm10 + this->m_10 * rm11 + this->m_20 * rm12;
	float nm11 = this->m_01 * rm10 + this->m_11 * rm11 + this->m_21 * rm12;
	float nm12 = this->m_02 * rm10 + this->m_12 * rm11 + this->m_22 * rm12;
	float nm13 = this->m_03 * rm10 + this->m_13 * rm11 + this->m_23 * rm12;

	this->m_20 = this->m_00 * rm20 + this->m_10 * rm21 + this->m_20 * rm22;
	this->m_21 = this->m_01 * rm20 + this->m_11 * rm21 + this->m_21 * rm22;
	this->m_22 = this->m_02 * rm20 + this->m_12 * rm21 + this->m_22 * rm22;
	this->m_23 = this->m_03 * rm20 + this->m_13 * rm21 + this->m_23 * rm22;

	this->m_00 = nm00;
	this->m_01 = nm01;
	this->m_02 = nm02;
	this->m_03 = nm03;

	this->m_10 = nm10;
	this->m_11 = nm11;
	this->m_12 = nm12;
	this->m_13 = nm13;
}

void Matrix4f::rotation(const Vector3f *angle)
{
	this->rotation(angle->x, angle->y, angle->z);
}

void Matrix4f::rotation(const Quaternionf *rotation)
{
	float xSquared = rotation->x * rotation->x;
	float ySquared = rotation->y * rotation->y;
	float zSquared = rotation->z * rotation->z;
	float wSquared = rotation->w * rotation->w;
	float zw = rotation->z * rotation->w;
	float xy = rotation->x * rotation->y;
	float xz = rotation->x * rotation->z;
	float yw = rotation->y * rotation->w;
	float yz = rotation->y * rotation->z;
	float xw = rotation->x * rotation->w;

	this->m_00 = wSquared + xSquared - zSquared - ySquared;
	this->m_01 = xy + zw + zw + xy;
	this->m_02 = xz - yw + xz - yw;
	this->m_03 = 0.0f;

	this->m_10 = -zw + xy - zw + xy;
	this->m_11 = ySquared - zSquared + wSquared - xSquared;
	this->m_12 = yz + yz + xw + xw;
	this->m_13 = 0.0f;

	this->m_20 = yw + xz + xz + yw;
	this->m_21 = yz + yz - xw - xw;
	this->m_22 = zSquared - ySquared - xSquared + wSquared;
	this->m_23 = 0.0f;

	this->m_30 = 0.0f;
	this->m_31 = 0.0f;
	this->m_32 = 0.0f;
	this->m_33 = 1.0f;
}

void Matrix4f::scale(const float scaleX, const float scaleY, const float scaleZ)
{
	this->m_00 *= scaleX;
	this->m_01 *= scaleX;
	this->m_02 *= scaleX;
	this->m_03 *= scaleX;

	this->m_10 *= scaleY;
	this->m_11 *= scaleY;
	this->m_12 *= scaleY;
	this->m_13 *= scaleY;

	this->m_20 *= scaleZ;
	this->m_21 *= scaleZ;
	this->m_22 *= scaleZ;
	this->m_23 *= scaleZ;
}

void Matrix4f::scale(const Vector3f *scale)
{
	this->scale(scale->x, scale->y, scale->z);
}

void Matrix4f::scaling(const float scaleX, const float scaleY, const float scaleZ)
{
	// first column
	this->m_00 = scaleX;
	this->m_01 = 0.0f;
	this->m_02 = 0.0f;
	this->m_03 = 0.0f;

	// second column
	this->m_10 = 0.0f;
	this->m_11 = scaleY;
	this->m_12 = 0.0f;
	this->m_13 = 0.0f;

	// third column
	this->m_20 = 0.0f;
	this->m_21 = 0.0f;
	this->m_22 = scaleZ;
	this->m_23 = 0.0f;

	// fourth column
	this->m_30 = 0.0f;
	this->m_31 = 0.0f;
	this->m_32 = 0.0f;
	this->m_33 = 1.0f;
}

void Matrix4f::scaling(const Vector3f *scaling)
{
	this->scaling(scaling->x, scaling->y, scaling->z);
}

Matrix4f &Matrix4f::operator=(const Matrix4f &rhs)
= default;

Matrix4f &Matrix4f::operator+=(const Matrix4f &rhs)
{
	this->m_00 += rhs.m_00;
	this->m_01 += rhs.m_01;
	this->m_02 += rhs.m_02;
	this->m_03 += rhs.m_03;
	this->m_10 += rhs.m_10;
	this->m_11 += rhs.m_11;
	this->m_12 += rhs.m_12;
	this->m_13 += rhs.m_13;
	this->m_20 += rhs.m_20;
	this->m_21 += rhs.m_21;
	this->m_22 += rhs.m_22;
	this->m_23 += rhs.m_23;
	this->m_30 += rhs.m_30;
	this->m_31 += rhs.m_31;
	this->m_32 += rhs.m_32;
	this->m_33 += rhs.m_33;

	return *this;
}

Matrix4f &Matrix4f::operator-=(const Matrix4f &rhs)
{
	this->m_00 -= rhs.m_00;
	this->m_01 -= rhs.m_01;
	this->m_02 -= rhs.m_02;
	this->m_03 -= rhs.m_03;
	this->m_10 -= rhs.m_10;
	this->m_11 -= rhs.m_11;
	this->m_12 -= rhs.m_12;
	this->m_13 -= rhs.m_13;
	this->m_20 -= rhs.m_20;
	this->m_21 -= rhs.m_21;
	this->m_22 -= rhs.m_22;
	this->m_23 -= rhs.m_23;
	this->m_30 -= rhs.m_30;
	this->m_31 -= rhs.m_31;
	this->m_32 -= rhs.m_32;
	this->m_33 -= rhs.m_33;
	return *this;
}

Matrix4f &Matrix4f::operator*=(const Matrix4f &rhs)
{
	float nm00 = std::fmaf(this->m_00, rhs.m_00, std::fmaf(this->m_10, rhs.m_01, std::fmaf(this->m_20, rhs.m_02, this->m_30 * rhs.m_03)));
	float nm01 = std::fmaf(this->m_01, rhs.m_00, std::fmaf(this->m_11, rhs.m_01, std::fmaf(this->m_21, rhs.m_02, this->m_31 * rhs.m_03)));
	float nm02 = std::fmaf(this->m_02, rhs.m_00, std::fmaf(this->m_12, rhs.m_01, std::fmaf(this->m_22, rhs.m_02, this->m_32 * rhs.m_03)));
	float nm03 = std::fmaf(this->m_03, rhs.m_00, std::fmaf(this->m_13, rhs.m_01, std::fmaf(this->m_23, rhs.m_02, this->m_33 * rhs.m_03)));

	float nm10 = std::fmaf(this->m_00, rhs.m_10, std::fmaf(this->m_10, rhs.m_11, std::fmaf(this->m_20, rhs.m_12, this->m_30 * rhs.m_13)));
	float nm11 = std::fmaf(this->m_01, rhs.m_10, std::fmaf(this->m_11, rhs.m_11, std::fmaf(this->m_21, rhs.m_12, this->m_31 * rhs.m_13)));
	float nm12 = std::fmaf(this->m_02, rhs.m_10, std::fmaf(this->m_12, rhs.m_11, std::fmaf(this->m_22, rhs.m_12, this->m_32 * rhs.m_13)));
	float nm13 = std::fmaf(this->m_03, rhs.m_10, std::fmaf(this->m_13, rhs.m_11, std::fmaf(this->m_23, rhs.m_12, this->m_33 * rhs.m_13)));

	float nm20 = std::fmaf(this->m_00, rhs.m_20, std::fmaf(this->m_10, rhs.m_21, std::fmaf(this->m_20, rhs.m_22, this->m_30 * rhs.m_23)));
	float nm21 = std::fmaf(this->m_01, rhs.m_20, std::fmaf(this->m_11, rhs.m_21, std::fmaf(this->m_21, rhs.m_22, this->m_31 * rhs.m_23)));
	float nm22 = std::fmaf(this->m_02, rhs.m_20, std::fmaf(this->m_12, rhs.m_21, std::fmaf(this->m_22, rhs.m_22, this->m_32 * rhs.m_23)));
	float nm23 = std::fmaf(this->m_03, rhs.m_20, std::fmaf(this->m_13, rhs.m_21, std::fmaf(this->m_23, rhs.m_22, this->m_33 * rhs.m_23)));

	float nm30 = std::fmaf(this->m_00, rhs.m_30, std::fmaf(this->m_10, rhs.m_31, std::fmaf(this->m_20, rhs.m_32, this->m_30 * rhs.m_33)));
	float nm31 = std::fmaf(this->m_01, rhs.m_30, std::fmaf(this->m_11, rhs.m_31, std::fmaf(this->m_21, rhs.m_32, this->m_31 * rhs.m_33)));
	float nm32 = std::fmaf(this->m_02, rhs.m_30, std::fmaf(this->m_12, rhs.m_31, std::fmaf(this->m_22, rhs.m_32, this->m_32 * rhs.m_33)));
	float nm33 = std::fmaf(this->m_03, rhs.m_30, std::fmaf(this->m_13, rhs.m_31, std::fmaf(this->m_23, rhs.m_32, this->m_33 * rhs.m_33)));

	this->m_00 = nm00;
	this->m_01 = nm01;
	this->m_02 = nm02;
	this->m_03 = nm03;
	this->m_10 = nm10;
	this->m_11 = nm11;
	this->m_12 = nm12;
	this->m_13 = nm13;
	this->m_20 = nm20;
	this->m_21 = nm21;
	this->m_22 = nm22;
	this->m_23 = nm23;
	this->m_30 = nm30;
	this->m_31 = nm31;
	this->m_32 = nm32;
	this->m_33 = nm33;
	return *this;
}
