//
// Created by masy on 08.03.20.
//

#ifndef CEDAR_INTERSECTION_HPP
#define CEDAR_INTERSECTION_HPP

/**
 * Base namespace for various intersection tests.
 */
namespace cedar::intersection
{

	/**
	 * Checks if the given point is inside the given rectangle.
	 *
	 * @param cornerMinX The x coordinate of the first corner of the rectangle.
	 * @param cornerMinY The y coordinate of the first corner of the rectangle.
	 * @param cornerMaxX The x coordinate of the second corner of the rectangle.
	 * @param cornerMaxY The y coordinate of the second corner of the rectangle.
	 * @param pointX The x coordinate of the point.
	 * @param pointY The y coordinate of the point.
	 * @return <code>true</code> if the point is inside the rectangle.
	 */
	static inline bool
	isPointInsideRectangle2Df(const float cornerMinX, const float cornerMinY, const float cornerMaxX, const float cornerMaxY,
						  const float pointX, const float pointY)
	{
		return pointX >= cornerMinX && pointX <= cornerMaxX && pointY >= cornerMinY && pointY <= cornerMaxY;
	}

	/**
	 * Checks if the given point is inside the given rectangle.
	 *
	 * @param cornerMinX The x coordinate of the first corner of the rectangle.
	 * @param cornerMinY The y coordinate of the first corner of the rectangle.
	 * @param cornerMaxX The x coordinate of the second corner of the rectangle.
	 * @param cornerMaxY The y coordinate of the second corner of the rectangle.
	 * @param pointX The x coordinate of the point.
	 * @param pointY The y coordinate of the point.
	 * @return <code>true</code> if the point is inside the rectangle.
	 */
	static inline bool
	isPointInsideRectangle2Dd(const double cornerMinX, const double cornerMinY, const double cornerMaxX, const double cornerMaxY,
						  const double pointX, const double pointY)
	{
		return pointX >= cornerMinX && pointX <= cornerMaxX && pointY >= cornerMinY && pointY <= cornerMaxY;
	}
}

#endif //CEDAR_INTERSECTION_HPP
