//
// Created by masy on 13.03.20.
//

#ifndef CEDAR_DISTANCE2D_H
#define CEDAR_DISTANCE2D_H

#include "Vector2f.h"
#include <cmath>

/**
 * Base namespace of the cedar engine.
 */
namespace cedar
{
	/**
	 * Calculates the shortest distance between the given line segment and point.
	 *
	 * @param lineStart The start of the line segment.
	 * @param lineEnd The end of the line segment.
	 * @param point The point.
	 * @return The shortest distance between the line segment and point.
	 */
	static float distancePointToLineSegment(const Vector2f &lineStart, const Vector2f &lineEnd, const Vector2f &point)
	{
		const float distanceSquared = lineStart.distanceSquared(lineEnd);
		if (distanceSquared == 0.0)
			return point.distance(lineStart);

		const Vector2f startToPoint = point - lineStart;
		const Vector2f startToEnd = lineEnd - lineStart;
		const float t = std::max(0.0f, std::min(1.0f, startToPoint.dot(startToEnd) / distanceSquared));
		const Vector2f projection = lineStart + t * startToEnd;
		return point.distance(projection);
	}

	/**
	 * Calculates the shortest squared distance between the given line segment and point.
	 *
	 * @param lineStart The start of the line segment.
	 * @param lineEnd The end of the line segment.
	 * @param point The point.
	 * @return The shortest squared distance between the line segment and point.
	 */
	static float distanceSquaredPointToLineSegment(const Vector2f &lineStart, const Vector2f &lineEnd, const Vector2f &point)
	{
		const float distanceSquared = lineStart.distanceSquared(lineEnd);
		if (distanceSquared == 0.0)
			return point.distanceSquared(lineStart);

		const Vector2f startToPoint = point - lineStart;
		const Vector2f startToEnd = lineEnd - lineStart;
		const float t = std::max(0.0f, std::min(1.0f, startToPoint.dot(startToEnd) / distanceSquared));
		const Vector2f projection = lineStart + t * startToEnd;
		return point.distanceSquared(projection);
	}
}

#endif //CEDAR_DISTANCE2D_H
