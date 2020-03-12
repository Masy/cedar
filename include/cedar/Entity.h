//
// Created by masy on 12.03.20.
//

#ifndef CEDAR_ENTITY_H
#define CEDAR_ENTITY_H

#include "cedar/Vector3f.h"
#include "cedar/Quaternionf.h"
#include "cedar/Model.h"

/**
 * The time of a single tick of the engine thread in micro seconds.
 */
#define CEDAR_TICK_TIME 50000000.0f
/**
 * The default speed of entities.
 */
#define CEDAR_DEFAULT_SPEED 0.1f

/**
 * Base namespace of the cedar engine
 */
namespace cedar
{
	/**
	 * Base class for all entities.
	 */
	class Entity
	{
	private:
		/**
		 * Unsigned integer storing the id of the next entity.
		 */
		static unsigned int NEXT_ENTITY_ID;

	protected:
		/**
		 * The unique identifier of the entity.
		 */
		unsigned int m_entityId;
		/**
		 * The previous position of the entity.
		 */
		Vector3f m_prevPosition;
		/*
		 * The current position of the entity.
		 */
		Vector3f m_position;
		/**
		 * The speed of the entity.
		 */
		float m_speed;
		/**
		 * The current rotation of the entity in euler angles.
		 */
		Vector3f m_rotationEuler;
		/**
		 * The previous rotation of the entity.
		 */
		Quaternionf m_prevRotation;
		/**
		 * The current rotation of the entity.
		 */
		Quaternionf m_rotation;
		/**
		 * The time in microseconds when the entity was last updated.
		 */
		unsigned long m_lastUpdate;
		/**
		 * A pointer to the model of the entity.
		 */
		Model *m_model;

		/**
		 * Updates the rotation.
		 *
		 * <p>The {@link #m_rotationEuler} variable is clamped between boundaries and then
		 * the {@link #m_rotation} variable is updated to it.</p>
		 */
		void updateRotation();

		/**
		 * Calculates an interpolation factor based on the current time and the time when the entity was updated.
		 *
		 * @param currentTime The current time in microseconds.
		 * @return The calculated interpolation factor.
		 */
		[[nodiscard]] inline float getInterpolationFactor(const unsigned long currentTime) const
		{
			return static_cast<float>(currentTime - this->m_lastUpdate) / CEDAR_TICK_TIME;
		}

	public:
		/**
		 * Gets the next entity id.
		 *
		 * @return The next entity id.
		 */
		static unsigned int nextEntityId();

		/**
		 * Creates a new entity.
		 *
		 * @param entityId The id of the entity.
		 * @param position The position of the entity.
		 */
		explicit Entity(unsigned int entityId, const Vector3f &position = Vector3f());

		/**
		 * Creates a new entity.
		 *
		 * @param entityId The id of the entity.
		 * @param position The position of the entity.
		 * @param rotation The rotation of the entity in euler angles.
		 */
		Entity(unsigned int entityId, const Vector3f &position, const Vector3f &rotation);

		/**
		 * Creates a new entity.
		 *
		 * @param entityId The id of the entity.
		 * @param position The position of the entity.
		 * @param rotation The rotation of the entity.
		 */
		Entity(unsigned int entityId, const Vector3f &position, const Quaternionf &rotation);

		/**
		 * Updates the entity.
		 *
		 * @param currentTime The current time in microseconds.
		 * @param tickCount The current tick count.
		 */
		void update(unsigned long currentTime, unsigned long tickCount);

		/**
		 * Moves the entity in the given direction.
		 *
		 * @param deltaX The movement of the entity on the x axis.
		 * @param deltaY The movement of the entity on the y axis.
		 * @param deltaZ The movement of the entity on the z axis.
		 */
		void move(float deltaX, float deltaY, float deltaZ);

		/**
		 * Moved the entity in the given direction.
		 *
		 * @param deltaMove The movement of the entity.
		 */
		void move(const Vector3f &deltaMove);

		/**
		 * Moves the entity along the x axis.
		 *
		 * @param deltaX The movement of the entity along the x axis.
		 */
		void moveX(float deltaX);

		/**
		 * Moves the entity along the y axis.
		 *
		 * @param deltaY The movement of the entity along the y axis.
		 */
		void moveY(float deltaY);

		/**
		 * Moves the entity along the z axis.
		 *
		 * @param deltaZ The movement of the entity along the z axis.
		 */
		void moveZ(float deltaZ);

		/**
		 * Moves the entity in the given direction local to the current rotation.
		 *
		 * @param deltaX The movement of the entity on the local x axis.
		 * @param deltaY The movement of the entity on the local y axis.
		 * @param deltaZ The movement of the entity on the local z axis.
		 */
		void moveLocal(float deltaX, float deltaY, float deltaZ);

		/**
		 * Moves the entity in the given direction local to the current rotation.
		 *
		 * @param deltaMove The movement of the entity on the local axes.
		 */
		void moveLocal(const Vector3f &deltaMove);

		/**
		 * Sets the position of the entity.
		 *
		 * @param newX The new x coordinate of the entity.
		 * @param newY The new y coordinate of the entity.
		 * @param newZ The new z coordinate of the entity.
		 */
		void setPosition(float newX, float newY, float newZ);

		/**
		 * Sets the position of the entity.
		 *
		 * @param newPosition The new position of the entity.
		 */
		void setPosition(const Vector3f &newPosition);

		/**
		 * Sets the x coordinate of the entity.
		 *
		 * @param newX The new x coordinate of the entity.
		 */
		void setPosX(float newX);

		/**
		 * Sets the y coordinate of the entity.
		 *
		 * @param newY The new y coordinate of the entity.
		 */
		void setPosY(float newY);

		/**
		 * Sets the z coordinate of the entity.
		 *
		 * @param newZ The new z coordinate of the entity.
		 */
		void setPosZ(float newZ);

		/**
		 * Sets the speed of the entity.
		 *
		 * @param newSpeed The new speed of the entity.
		 */
		void setSpeed(float newSpeed);

		/**
		 * Rotates the entity by the given angles.
		 *
		 * @param deltaPitch The rotation around the x axis in radians.
		 * @param deltaYaw The rotation around the y axis in radians.
		 * @param deltaRoll The rotation around the z axis in radians.
		 */
		void rotate(float deltaPitch, float deltaYaw, float deltaRoll);

		/**
		 * Rotates the entity by the given angles.
		 *
		 * @param deltaRotation The amount the entity is rotated by in radians.
		 */
		void rotate(const Vector3f &deltaRotation);

		/**
		 * Rotates the entity around the x axis.
		 *
		 * @param deltaPitch The rotation around the x axis in radians.
		 */
		void rotateX(float deltaPitch);

		/**
		 * Rotates the entity around the y axis.
		 *
		 * @param deltaYaw The rotation around the y axis in radians.
		 */
		void rotateY(float deltaYaw);

		/**
		 * Rotates the entity around the z axis.
		 *
		 * @param deltaRoll The rotation around the z axis in radians.
		 */
		void rotateZ(float deltaRoll);

		/**
		 * Sets the rotation of the entity.
		 *
		 * @param newRotation The new rotation of the entity.
		 */
		void setRotation(const Quaternionf &newRotation);

		/**
		 * Sets the rotation of the entity.
		 *
		 * @param newPitch The new rotation along the x axis in radians.
		 * @param newYaw The new rotation along the y axis in radians.
		 * @param newRoll The new rotation along the z axis in radians.
		 */
		void setRotation(float newPitch, float newYaw, float newRoll);

		/**
		 * Sets the rotation of the entity.
		 *
		 * @param newRotation The new rotation of the entity in euler angles.
		 */
		void setRotation(const Vector3f &newRotation);

		/**
		 * Sets the pitch of the entity.
		 *
		 * @param newPitch The new rotation along the x axis in radians.
		 */
		void setPitch(float newPitch);

		/**
		 * Sets the yaw of the entity.
		 *
		 * @param newYaw The new rotation along the y axis in radians.
		 */
		void setYaw(float newYaw);

		/**
		 * Sets the roll of the entity.
		 *
		 * @param newRoll The new rotation along the z axis in radians.
		 */
		void setRoll(float newRoll);

		/**
		 * Gets the id of the entity.
		 *
		 * @return The id of the entity.
		 */
		[[nodiscard]] unsigned int getEntityId() const;

		/**
		 * Gets the previous position of the entity.
		 *
		 * @return The previous position of the entity.
		 */
		[[nodiscard]] Vector3f getPrevPosition() const;

		/**
		 * Gets the previous position of the entity.
		 *
		 * @param storage A pointer to the vector where the previous position will be stored.
		 * @return The <code>storage</code> pointer.
		 */
		Vector3f *getPrevPosition(Vector3f *storage) const;

		/**
		 * Gets the position of the entity.
		 *
		 * @return The position of the entity.
		 */
		[[nodiscard]] Vector3f getPosition() const;

		/**
		 * Gets the position of the entity.
		 *
		 * @param storage A pointer to the vector where the position will be stored.
		 * @return The <code>storage</code> pointer.
		 */
		Vector3f *getPosition(Vector3f *storage) const;

		/**
		 * Gets the linearly interpolated position of the entity.
		 *
		 * @param currentTime The current time in microseconds.
		 * @return The interpolated position of the entity.
		 */
		[[nodiscard]] Vector3f getLerpedPosition(unsigned long currentTime) const;

		/**
		 * Gets the linearly interpolated position of the entity.
		 *
		 * @param currentTime The current time in microseconds.
		 * @param storage A pointer to the vector where the interpolated position will be stored.
		 * @return The <code>storage</code> pointer.
		 */
		Vector3f *getLerpedPosition(unsigned long currentTime, Vector3f *storage) const;

		/**
		 * Gets the rotation of the entity in euler angles.
		 *
		 * @return The rotation of the entity in euler angles.
		 */
		[[nodiscard]] Vector3f getRotationEuler() const;

		/**
		 * Gets the rotation of the entity in euler angles.
		 *
		 * @param storage A pointer to the vector where the rotation will be stored.
		 * @return The <code>storage</code> pointer.
		 */
		Vector3f *getRotationEuler(Vector3f *storage) const;

		/**
		 * Gets the previous rotation of the entity.
		 *
		 * @return The previous rotation of the entity.
		 */
		[[nodiscard]] Quaternionf getPrevRotation() const;

		/**
		 * Gets the previous rotation of the entity.
		 *
		 * @param storage A pointer to the quaternion where the previous rotation will be stored.
		 * @return The <code>storage</code> pointer.
		 */
		Quaternionf *getPrevRotation(Quaternionf *storage) const;

		/**
		 * Gets the rotation of the entity.
		 *
		 * @return The rotation of the entity.
		 */
		[[nodiscard]] Quaternionf getRotation() const;

		/**
		 * Gets the rotation of the entity.
		 *
		 * @param storage A pointer to the quaternion where the rotation will be stored.
		 * @return The <code>storage</code> pointer.
		 */
		Quaternionf *getRotation(Quaternionf *storage) const;

		/**
		 * Gets the spherically interpolated rotation of the entity.
		 *
		 * @param currentTime The current time in microseconds.
		 * @return The interpolated rotation.
		 */
		[[nodiscard]] Quaternionf getSlerpedRotation(unsigned long currentTime) const;

		/**
		 * Gets the spherically interpolated rotation of the entity.
		 *
		 * @param currentTime The current time in microseconds.
		 * @param storage A pointer to the quaternion where the interpolated rotation will be stored.
		 * @return The <code>storage</code> pointer.
		 */
		Quaternionf *getSlerpedRotation(unsigned long currentTime, Quaternionf *storage) const;

		/**
		 * Gets the speed of the entity.
		 *
		 * @return The speed of the entity.
		 */
		[[nodiscard]] float getSpeed() const;

		/**
		 * Gets the time when the entity was last updated in microseconds.
		 *
		 * @return The time when the entity was last updated in microseconds.
		 */
		[[nodiscard]] unsigned long getLastUpdateTime() const;

		/**
		 * Gets the model of the entity.
		 *
		 * @return A pointer to the model of the entity.
		 */
		[[nodiscard]] Model *getModel() const;

		/**
		 * Sets the model of the entity.
		 *
		 * @param newModel A pointer to the new model of the entity.
		 */
		void setModel(Model *newModel);
	};
}

#endif //CEDAR_ENTITY_H
