//
// Created by masy on 12.03.20.
//

#include "cedar/Entity.hpp"
#include "cedar/Math.hpp"

using namespace cedar;

unsigned int Entity::NEXT_ENTITY_ID = 0;

unsigned int Entity::nextEntityId()
{
	return NEXT_ENTITY_ID++;
}

Entity::Entity(unsigned int entityId, const cedar::Vector3f &position)
{
	this->m_entityId = entityId;
	this->m_prevPosition = position;
	this->m_position = position;
	this->m_speed = CEDAR_DEFAULT_SPEED;
	this->m_rotationEuler = Vector3f();
	this->m_prevRotation = Quaternionf();
	this->m_rotation = Quaternionf();
	this->m_lastUpdate = 0;
	this->m_model = nullptr;
}

Entity::Entity(unsigned int entityId, const cedar::Vector3f &position, const cedar::Vector3f &rotation)
{
	this->m_entityId = entityId;
	this->m_prevPosition = position;
	this->m_position = position;
	this->m_speed = CEDAR_DEFAULT_SPEED;
	this->m_rotationEuler = rotation;
	this->m_prevRotation = Quaternionf();
	this->m_prevRotation.rotation(rotation);
	this->m_rotation = this->m_prevRotation;
	this->m_lastUpdate = 0;
	this->m_model = nullptr;
}

Entity::Entity(unsigned int entityId, const cedar::Vector3f &position, const cedar::Quaternionf &rotation)
{
	this->m_entityId = entityId;
	this->m_prevPosition = position;
	this->m_position = position;
	this->m_speed = CEDAR_DEFAULT_SPEED;
	rotation.getEulerAngles(&this->m_rotationEuler);
	this->m_prevRotation = rotation;
	this->m_rotation = rotation;
	this->m_lastUpdate = 0;
	this->m_model = nullptr;
}

void Entity::update(const unsigned long currentTime, const unsigned long tickCount) {
	this->m_lastUpdate = currentTime;
	this->m_prevPosition = this->m_position;
	this->m_prevRotation = this->m_rotation;
}

void Entity::move(const float deltaX, const float deltaY, const float deltaZ) {
	this->m_position.x += deltaX;
	this->m_position.y += deltaY;
	this->m_position.z += deltaZ;
}

void Entity::move(const Vector3f &deltaMove) {
	this->m_position += deltaMove;
}

void Entity::moveX(const float deltaX) {
	this->m_position.x += deltaX;
}

void Entity::moveY(const float deltaY) {
	this->m_position.y += deltaY;
}

void Entity::moveZ(const float deltaZ) {
	this->m_position.z += deltaZ;
}

void Entity::moveLocal(float deltaX, float deltaY, float deltaZ) {
	Vector3f localMove;
	this->m_rotation.transform(deltaX, deltaY, deltaZ, &localMove);
	this->m_position += localMove;
}

void Entity::moveLocal(const Vector3f &deltaMove) {
	this->moveLocal(deltaMove.x, deltaMove.y, deltaMove.z);
}

void Entity::setPosition(const float newX, const float newY, const float newZ) {
	this->m_position.x = newX;
	this->m_position.y = newY;
	this->m_position.z = newZ;
}

void Entity::setPosition(const Vector3f &newPosition) {
	this->m_position = newPosition;
}

void Entity::setPosX(const float newX) {
	this->m_position.x = newX;
}

void Entity::setPosY(const float newY) {
	this->m_position.y = newY;
}

void Entity::setPosZ(const float newZ) {
	this->m_position.z = newZ;
}

void Entity::setSpeed(const float newSpeed) {
	this->m_speed = newSpeed;
}

void Entity::updateRotation()
{
	this->m_rotationEuler.x = cedar::clamp(this->m_rotationEuler.x, -M_PI_2f32, M_PI_2f32);

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

void Entity::rotate(const float deltaPitch, const float deltaYaw, const float deltaRoll) {
	this->m_rotationEuler.x += deltaPitch;
	this->m_rotationEuler.y += deltaYaw;
	this->m_rotationEuler.z += deltaRoll;
	this->updateRotation();
}

void Entity::rotate(const Vector3f &deltaRotation) {
	this->m_rotationEuler += deltaRotation;
	this->updateRotation();
}

void Entity::rotateX(const float deltaPitch) {
	this->m_rotationEuler.x += deltaPitch;
	this->updateRotation();
}

void Entity::rotateY(const float deltaYaw) {
	this->m_rotationEuler.y += deltaYaw;
	this->updateRotation();
}

void Entity::rotateZ(const float deltaRoll) {
	this->m_rotationEuler.z += deltaRoll;
	this->updateRotation();
}

void Entity::setRotation(const Quaternionf &newRotation) {
	this->m_rotation = newRotation;
	this->m_rotation.getEulerAngles(&this->m_rotationEuler);
}

void Entity::setRotation(const float newPitch, const float newYaw, const float newRoll) {
	this->m_rotationEuler.x = newPitch;
	this->m_rotationEuler.y = newYaw;
	this->m_rotationEuler.z = newRoll;
	this->updateRotation();
	this->m_rotation.rotation(this->m_rotationEuler);
}

void Entity::setRotation(const Vector3f &newRotation) {
	this->m_rotationEuler = newRotation;
	this->updateRotation();
	this->m_rotation.rotation(this->m_rotationEuler);
}

void Entity::setPitch(const float newPitch) {
	this->m_rotationEuler.x = newPitch;
	this->updateRotation();
	this->m_rotation.rotation(this->m_rotationEuler);
}

void Entity::setYaw(float newYaw) {
	this->m_rotationEuler.y = newYaw;
	this->updateRotation();
	this->m_rotation.rotation(this->m_rotationEuler);
}

void Entity::setRoll(const float newRoll) {
	this->m_rotationEuler.z = newRoll;
	this->updateRotation();
	this->m_rotation.rotation(this->m_rotationEuler);
}

unsigned int Entity::getEntityId() const {
	return this->m_entityId;
}

Vector3f Entity::getPrevPosition() const {
	return this->m_prevPosition;
}

Vector3f *Entity::getPrevPosition(Vector3f *storage) const {
	*storage = this->m_prevPosition;
	return storage;
}

Vector3f Entity::getPosition() const {
	return this->m_position;
}

Vector3f *Entity::getPosition(Vector3f *storage) const {
	*storage = this->m_position;
	return storage;
}

Vector3f Entity::getLerpedPosition(const unsigned long currentTime) const {
	float t = this->getInterpolationFactor(currentTime);
	return this->m_prevPosition.lerp(this->m_position, t);
}

Vector3f *Entity::getLerpedPosition(const unsigned long currentTime, Vector3f *storage) const {
	float t = this->getInterpolationFactor(currentTime);
	return this->m_prevPosition.lerp(this->m_position, storage, t);
}

Vector3f Entity::getRotationEuler() const {
	return this->m_rotationEuler;
}

Vector3f *Entity::getRotationEuler(Vector3f *storage) const {
	*storage = this->m_rotationEuler;
	return storage;
}

Quaternionf Entity::getPrevRotation() const {
	return this->m_prevRotation;
}

Quaternionf *Entity::getPrevRotation(Quaternionf *storage) const {
	*storage = this->m_prevRotation;
	return storage;
}

Quaternionf Entity::getRotation() const {
	return this->m_rotation;
}

Quaternionf *Entity::getRotation(Quaternionf *storage) const {
	*storage = this->m_rotation;
	return storage;
}

Quaternionf Entity::getSlerpedRotation(const unsigned long currentTime) const {
	float t = this->getInterpolationFactor(currentTime);
	return this->m_prevRotation.slerp(this->m_rotation, t);
}

Quaternionf *Entity::getSlerpedRotation(unsigned long currentTime, Quaternionf *storage) const {
	float t = this->getInterpolationFactor(currentTime);
	return this->m_prevRotation.slerp(this->m_rotation, storage, t);
}

float Entity::getSpeed() const {
	return this->m_speed;
}

unsigned long Entity::getLastUpdateTime() const {
	return this->m_lastUpdate;
}

Model *Entity::getModel() const {
	return this->m_model;
}

void Entity::setModel(Model *newModel) {
	this->m_model = newModel;
}
