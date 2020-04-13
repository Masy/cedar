//
// Created by masy on 11.03.20.
//

#include "cedar/FrustumRayBuilder.hpp"

using namespace cedar;

FrustumRayBuilder::FrustumRayBuilder()
{
	this->m_bottomLeft = Vector3f();
	this->m_bottomRight = Vector3f();
	this->m_topLeft = Vector3f();
	this->m_topRight = Vector3f();
	this->m_origin = Vector3f();
}

FrustumRayBuilder *FrustumRayBuilder::set(const Matrix4f &viewSpaceMatrix) {
	float nxX = viewSpaceMatrix.m_03 + viewSpaceMatrix.m_00;
	float nxY = viewSpaceMatrix.m_13 + viewSpaceMatrix.m_10;
	float nxZ = viewSpaceMatrix.m_23 + viewSpaceMatrix.m_20;
	float d1 = viewSpaceMatrix.m_33 + viewSpaceMatrix.m_30;
	float pxX = viewSpaceMatrix.m_03 - viewSpaceMatrix.m_00;
	float pxY = viewSpaceMatrix.m_13 - viewSpaceMatrix.m_10;
	float pxZ = viewSpaceMatrix.m_23 - viewSpaceMatrix.m_20;
	float d2 = viewSpaceMatrix.m_33 - viewSpaceMatrix.m_30;
	float nyX = viewSpaceMatrix.m_03 + viewSpaceMatrix.m_01;
	float nyY = viewSpaceMatrix.m_13 + viewSpaceMatrix.m_11;
	float nyZ = viewSpaceMatrix.m_23 + viewSpaceMatrix.m_21;
	float pyX = viewSpaceMatrix.m_03 - viewSpaceMatrix.m_01;
	float pyY = viewSpaceMatrix.m_13 - viewSpaceMatrix.m_11;
	float pyZ = viewSpaceMatrix.m_23 - viewSpaceMatrix.m_21;
	float d3 = viewSpaceMatrix.m_33 - viewSpaceMatrix.m_31;

	this->m_bottomLeft = Vector3f(nyY * nxZ - nyZ * nxY, nyZ * nxX - nyX * nxZ, nyX * nxY - nyY * nxX);
	this->m_bottomRight = Vector3f(pxY * nyZ - pxZ * nyY, pxZ * nyX - pxX * nyZ, pxX * nyY - pxY * nyX);
	this->m_topLeft = Vector3f(nxY * pyZ - nxZ * pyY, nxZ * pyX - nxX * pyZ, nxX * pyY - nxY * pyX);
	this->m_topRight = Vector3f(pyY * pxZ - pyZ * pxY, pyZ * pxX - pyX * pxZ, pyX * pxY - pyY * pxX);
	Vector3f center(pxY * nxZ - pxZ * nxY, pxZ * nxX - pxX * nxZ, pxX * nxY - pxY * nxX);

	float invDot = 1.0f / (nxX * this->m_topRight.x + nxY * this->m_topRight.y + nxZ * this->m_topRight.z);
	this->m_origin = (-this->m_topRight * d1 - this->m_topLeft * d2 - center * d3) * invDot;
	return this;
}

Vector3f *FrustumRayBuilder::getOrigin(Vector3f *origin) {
	*origin = this->m_origin;
	return origin;
}

Vector3f *FrustumRayBuilder::getRayDir(const float x, const float y, Vector3f *rayDir) {
	Vector3f y1 = this->m_bottomLeft + (this->m_topLeft - this->m_bottomLeft) * y;
	Vector3f y2 = this->m_bottomRight + (this->m_topRight - this->m_bottomRight) * y;
	*rayDir = y1 + (y2 - y1) * x;
	return rayDir->normalize();
}
