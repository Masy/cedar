//
// Created by masy on 06.03.20.
//

#ifndef CEDAR_CAMERA_H
#define CEDAR_CAMERA_H

#include "cedar/Vector3f.h"
#include "cedar/Quaternionf.h"

/**
 * Base namespace of the cedar engine.
 */
namespace cedar
{
	/**
	 * Entity class representing a camera.
	 */
	class Camera
	{
	private:
		/**
		 * The old position of the camera.
		 */
		Vector3f m_oldPosition;
		/**
		 * The current position of the camera.
		 */
		Vector3f m_position;
		/**
		 * The rotation of the camera in euler angles.
		 */
		Vector3f m_rotationEuler;
		/**
		 * The old rotation of the camera.
		 */
		Quaternionf m_oldRotation;
		/**
		 * The current rotation of the camera.
		 */
		Quaternionf m_rotation;
		/**
		 * The current zoom level of the camera
		 */
		float m_zoomLevel;

		/**
		 * The timestamp of when the camera was updated the last time.
		 */
		unsigned long m_lastUpdate;

		/**
		 * Fixes the euler angles of the camera and applies them to the current rotation.
		 */
		void fixRotation();

	public:
		/**
		 * Creates a new camera.
		 */
		Camera();

		/**
		 * Moves the camera in the given direction.
		 *
		 * @param deltaX The offset of the camera on the x axis.
		 * @param deltaY The offset of the camera on the y axis.
		 * @param deltaZ The offset of the camera on the z axis.
		 */
		void move(float deltaX, float deltaY, float deltaZ);

		/**
		 * Moves the camera along the x axis.
		 *
		 * @param deltaX The offset of the camera on the x axis.
		 */
		void moveX(float deltaX);

		/**
		 * Moves the camera along the y axis.
		 *
		 * @param deltaX The offset of the camera on the y axis.
		 */
		void moveY(float deltaY);

		/**
		 * Moves the camera along the z axis.
		 *
		 * @param deltaX The offset of the camera on the z axis.
		 */
		void moveZ(float deltaZ);

		/**
		 * Moves the camera in the given direction based on the camera's current rotation.
		 *
		 * @param deltaX The offset of the camera on the forward axis.
		 * @param deltaY The offset of the camera on the upwards axis.
		 * @param deltaZ The offset of the camera on the sideways axis.
		 */
		void moveLocal(float deltaX, float deltaY, float deltaZ);

		/**
		 * Rotates the camera.
		 *
		 * @param pitch The rotation amount on the x axis in radians.
		 * @param yaw The rotation amount on the y axis in radians.
		 * @param roll The rotation amount on the z axis in radians.
		 */
		void rotate(float pitch, float yaw, float roll);

		/**
		 * Rotates the camera around the x axis.
		 *
		 * @param pitch The rotation amount on the x axis in radians.
		 */
		void rotateX(float pitch);

		/**
		 * Rotates the camera around the y axis.
		 *
		 * @param yaw The rotation amount on the y axis in radians.
		 */
		void rotateY(float yaw);

		/**
		 * Rotates the camera around the z axis.
		 *
		 * @param roll The rotation amount on the z axis in radians.
		 */
		void rotateZ(float roll);

		/**
		 * Updates the camera.
		 *
		 * @param currentTime The current time of the tick in microseconds.
		 */
		void update(unsigned long currentTime);

		/**
		 * Gets the current position of the camera.
		 *
		 * @return A constant pointer to the current position of the camera.
		 */
		[[nodiscard]] const Vector3f *getPosition() const;

		/**
		 * Gets the current rotation of the camera.
		 *
		 * @return A constant pointer to the rotation of the camera.
		 */
		[[nodiscard]] const Quaternionf *getRotation() const;

		/**
		 * Gets the current rotation of the camera.
		 *
		 * @return a constant pointer to the current rotation of the camera.
		 */
		[[nodiscard]] const Vector3f *getRotationEuler() const;

		/**
		 * Gets the zoom level of the camera.
		 *
		 * @return the zoom level of the camera.
		 */
		[[nodiscard]] float getZoomLevel() const;

		/**
		 * Sets the zoom level of the camera.
		 *
		 * @param newZoomLevel The new zoom level of the camera.
		 */
		void setZoomLevel(float newZoomLevel);

		/**
		 * Zooms the camera over time by the given amount.
		 *
		 * @param deltaZoom The amount that will be zoomed.
		 */
		void zoom(float deltaZoom);
	};
}

#endif //CEDAR_CAMERA_H
