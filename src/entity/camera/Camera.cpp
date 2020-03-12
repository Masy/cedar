//
// Created by masy on 06.03.20.
//

#include "cedar/Camera.h"
#include "cedar/Math.h"

using namespace cedar;

Camera::Camera(const float minPitch, const float maxPitch)
{
	this->m_oldPosition = Vector3f();
	this->m_position = Vector3f();
	this->m_rotationEuler = Vector3f(clamp(0.0f, minPitch, maxPitch), 0.0f, 0.0f);
	this->m_minPitch = minPitch;
	this->m_maxPitch = maxPitch;
	this->m_oldRotation = Quaternionf();
	this->m_oldRotation.rotation(this->m_rotationEuler.x, this->m_rotationEuler.y, this->m_rotationEuler.z);
	this->m_rotation = this->m_oldRotation;
	this->m_zoomLevel = 10.0f;
	this->m_lastUpdate = 0;
}

void Camera::move(const float deltaX, const float deltaY, const float deltaZ)
{
	this->m_position += Vector3f(deltaX, deltaY, deltaZ);
}

void Camera::moveX(const float deltaX)
{
	this->m_position.x = deltaX;
}

void Camera::moveY(const float deltaY)
{
	this->m_position.y = deltaY;
}

void Camera::moveZ(const float deltaZ)
{
	this->m_position.z = deltaZ;
}

void Camera::moveLocal(const float deltaX, const float deltaY, const float deltaZ)
{
	Vector3f move;
	this->m_rotation.transform(deltaX, deltaY, deltaZ, &move);
	this->m_position += move;
}

void Camera::fixRotation()
{
	this->m_rotationEuler.x = cedar::clamp(this->m_rotationEuler.x, this->m_minPitch, this->m_maxPitch);

	if (this->m_rotationEuler.y < -M_PIf32)
		this->m_rotationEuler.y += PI_2f32;
	else if (this->m_rotationEuler.y > M_PIf32)
		this->m_rotationEuler.y -= PI_2f32;

	if (this->m_rotationEuler.z < -M_PIf32)
		this->m_rotationEuler.z += PI_2f32;
	else if (this->m_rotationEuler.z > M_PIf32)
		this->m_rotationEuler.z -= PI_2f32;

	this->m_rotation.rotation(this->m_rotationEuler);
}

void Camera::rotate(const float pitch, const float yaw, const float roll)
{
	this->m_rotationEuler += Vector3f(pitch, yaw, roll);
	this->fixRotation();
}

void Camera::rotateX(const float pitch)
{
	this->m_rotationEuler.x += pitch;
	this->fixRotation();
}

void Camera::rotateY(const float yaw)
{
	this->m_rotationEuler.y += yaw;
	this->fixRotation();
}

void Camera::rotateZ(const float roll)
{
	this->m_rotationEuler.z += roll;
	this->fixRotation();
}

void Camera::update(const unsigned long currentTime)
{
	this->m_lastUpdate = currentTime;

	this->m_oldPosition = this->m_position;
	this->m_oldRotation = this->m_rotation;
}

const Vector3f *Camera::getPosition() const
{
	return &this->m_position;
}

const Quaternionf *Camera::getRotation() const
{
	return &this->m_rotation;
}

const cedar::Vector3f *Camera::getRotationEuler() const
{
	return &this->m_rotationEuler;
}

float Camera::getMinPitch() const
{
	return this->m_minPitch;
}

void Camera::setMinPitch(const float newMinPitch)
{
	this->m_minPitch = newMinPitch;
}

float Camera::getMaxPitch() const
{
	return this->m_maxPitch;
}

void Camera::setMaxPitch(const float newMaxPitch)
{
	this->m_maxPitch = newMaxPitch;
}

float Camera::getZoomLevel() const
{
	return this->m_zoomLevel;
}

void Camera::setZoomLevel(float newZoomLevel)
{
	this->m_zoomLevel = std::fmaxf(2.0f, newZoomLevel);
}

void Camera::zoom(const float deltaZoom)
{
	this->m_zoomLevel = std::fmaxf(2.0f, this->m_zoomLevel + deltaZoom);
}
