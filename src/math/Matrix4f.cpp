//
// Created by masy on 06.02.20.
//

#include "cedar/Matrix4f.h"
#include <cmath>

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
	float rm21 = yz + yz - xw - xw ;
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
	float dzw = zw + zw;
	float dxy = xy + xy;
	float dxz = xz + xz;
	float dyw = yw + yw;
	float dyz = yz + yz;
	float dxw = xw + xw;

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
