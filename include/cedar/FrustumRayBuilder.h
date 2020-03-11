//
// Created by masy on 11.03.20.
//

#ifndef CEDAR_FRUSTUMRAYBUILDER_H
#define CEDAR_FRUSTUMRAYBUILDER_H

#include "cedar/Matrix4f.h"

/**
 * Base namespace of the cedar engine.
 */
namespace cedar
{

	/**
	 * Class storing information about the view frustum near plane to calculate eye-rays.
	 */
	class FrustumRayBuilder
	{
	private:
		/**
		 * The coordinates of the bottom-left corner of the near frustum plane.
		 */
		Vector3f m_bottomLeft;
		/**
		 * The coordinates of the bottom-right corner of the near frustum plane.
		 */
		Vector3f m_bottomRight;
		/**
		 * The coordinates of the top-left corner of the near frustum plane.
		 */
		Vector3f m_topLeft;
		/**
		 * The coordinates of the top-right corner of the near frustum plane.
		 */
		Vector3f m_topRight;
		/**
		 * The coordinates of the origin of the view frustum.
		 */
		Vector3f m_origin;

	public:
		/**
		 * Creates a new frustum ray builder.
		 */
		FrustumRayBuilder();

		/**
		 * Sets the frustum to the one described by the given view space matrix.
		 *
		 * @param viewSpaceMatrix The view space matrix
		 * @return A pointer to the instance of the frustum ray builder.
		 */
		FrustumRayBuilder *set(const Matrix4f &viewSpaceMatrix);

		/**
		 * Gets the origin of the frustum.
		 *
		 * @param origin A pointer to the vector where the origin is stored.
		 * @return A pointer to the provided <code>origin</code> vector.
		 */
		Vector3f *getOrigin(Vector3f *origin);

		/**
		 * Gets the direction of the eye ray from the origin to the near plane of the frustum.
		 *
		 * <p>How to calculate x and y:<br>
		 * x = cursorX / windowWidth<br>
		 * y = 1.0 - cursorY / windowHeight<br>
		 * with cursorX and cursorY being the coordinates of the cursor in pixel.</p>
		 *
		 * @param x Normalized x coordinate of the cursor on the near plane.
		 * @param y Normalized y coordinate of the cursor on the near plane.
		 * @param rayDir A pointer to the vector where the direction of the ray is stored.
		 * @return A pointer to the provided <code>rayDir</code> vector.
		 */
		Vector3f *getRayDir(float x, float y, Vector3f *rayDir);
	};

}

#endif //CEDAR_FRUSTUMRAYBUILDER_H
