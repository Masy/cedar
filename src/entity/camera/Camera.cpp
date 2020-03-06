//
// Created by masy on 06.03.20.
//

#include "cedar/Camera.h"
#include "cedar/Math.h"

/**
 * The time of one tick in microseconds.
 */
#define TICK_TIME_MICRO 50000000.0f

using namespace cedar;

Camera::Camera()
{
	this->m_position = cedar::Vector3f();
	this->m_newPosition = cedar::Vector3f();
	this->m_velocity = cedar::Vector3f();
	this->m_rotateVelocity = cedar::Vector3f();
	this->m_rotationEuler = cedar::Vector3f();
	this->m_rotation = cedar::Quaternionf();
	this->m_newRotation = cedar::Quaternionf();
	this->m_zoomLevel = 10.0f;
	this->m_newZoomLevel = 10.0f;
	this->m_zoomDelta = 0.0f;
	this->m_lastUpdate = 0;
}

void Camera::move(const float deltaX, const float deltaY, const float deltaZ)
{
	this->m_velocity.x = deltaX;
	this->m_velocity.y = deltaY;
	this->m_velocity.z = deltaZ;
}

void Camera::moveLocal(const float deltaX, const float deltaY, const float deltaZ)
{
	this->m_velocity.x = deltaX;
	this->m_velocity.y = deltaY;
	this->m_velocity.z = deltaZ;

	this->m_velocity.rotateY(-this->m_rotationEuler.y);
}

void Camera::rotate(const float pitch, const float yaw, const float roll)
{
	this->m_rotateVelocity.x = pitch;
	this->m_rotateVelocity.y = yaw;
	this->m_rotateVelocity.z = roll;
}

void Camera::getLerpedPosition(const unsigned long currentTime, cedar::Vector3f *result) const
{
	float t = static_cast<float>(currentTime - this->m_lastUpdate) / TICK_TIME_MICRO;
	this->m_position.lerp(&this->m_newPosition, result, t);
}

void Camera::getSlerpedRotation(unsigned long currentTime, cedar::Quaternionf *result) const
{
	float t = static_cast<float>(currentTime - this->m_lastUpdate) / TICK_TIME_MICRO;
	this->m_rotation.slerp(&this->m_newRotation, result, t);
}

void Camera::update(const unsigned long currentTime)
{
	this->m_lastUpdate = currentTime;

	this->m_zoomLevel = this->m_newZoomLevel;
	this->m_newZoomLevel = std::fmaxf(2.0f, this->m_newZoomLevel + this->m_zoomDelta);
	this->m_zoomDelta *= 0.95f;
	if (this->m_zoomDelta > -0.02f && this->m_zoomDelta < 0.02f)
		this->m_zoomDelta = 0;


	this->m_position = this->m_newPosition;
	this->m_newPosition += this->m_velocity;

	this->m_velocity *= 0.75f;

	if (this->m_velocity.x > -0.02f && this->m_velocity.x < 0.02f)
		this->m_velocity.x = 0.0f;

	if (this->m_velocity.y > -0.02f && this->m_velocity.y < 0.02f)
		this->m_velocity.y = 0.0f;

	if (this->m_velocity.z > -0.02f && this->m_velocity.z < 0.02f)
		this->m_velocity.z = 0.0f;

	this->m_rotation = this->m_newRotation;
	this->m_rotationEuler += this->m_rotateVelocity;
	this->m_rotationEuler.x = cedar::clamp(this->m_rotationEuler.x, -M_PI_2f32, M_PI_2f32);
	if (this->m_rotationEuler.y < -M_PIf32)
		this->m_rotationEuler.y += PI_2f32;
	else if (this->m_rotationEuler.y > M_PIf32)
		this->m_rotationEuler.y -= PI_2f32;
	this->m_newRotation.rotation(&this->m_rotationEuler);

	this->m_rotateVelocity *= 0.25f;

	if (this->m_rotateVelocity.x > -0.02f && this->m_rotateVelocity.x < 0.02f)
		this->m_rotateVelocity.x = 0.0f;

	if (this->m_rotateVelocity.y > -0.02f && this->m_rotateVelocity.y < 0.02f)
		this->m_rotateVelocity.y = 0.0f;

	if (this->m_rotateVelocity.z > -0.02f && this->m_rotateVelocity.z < 0.02f)
		this->m_rotateVelocity.z = 0.0f;
}

const cedar::Vector3f *Camera::getPosition() const
{
	return &this->m_newPosition;
}

const cedar::Vector3f *Camera::getRotationEuler() const
{
	return &this->m_rotationEuler;
}

int Camera::getZoomLevel() const
{
	return this->m_zoomLevel;
}

float Camera::getLerpedZoomLevel(const unsigned long currentTime) const
{
	float t = static_cast<float>(currentTime - this->m_lastUpdate) / TICK_TIME_MICRO;
	return cedar::lerp(static_cast<float>(this->m_zoomLevel), static_cast<float>(this->m_newZoomLevel), t);
}

void Camera::setZoomLevel(float newZoomLevel)
{
	this->m_newZoomLevel = std::fmaxf(2.0f, newZoomLevel);
}

void Camera::zoom(const float deltaZoom)
{
	this->m_zoomDelta = deltaZoom;
}
