//
// Created by masy on 11.03.20.
//

#include "cedar/MeshCollider2D.hpp"

using namespace cedar;

MeshCollider2D::MeshCollider2D(cedar::Vector2f *vertices, const unsigned int triangleCount, cedar::Triangle *triangles)
{
	this->m_vertices = vertices;
	this->m_triangleCount = triangleCount;
	this->m_triangles = triangles;
}

MeshCollider2D::~MeshCollider2D()
{
	delete[] this->m_vertices;
	delete[] this->m_triangles;
}

float sign(const Vector2f &p1, const Vector2f &p2, const Vector2f &p3)
{
	return (p1.x - p3.x) * (p2.y - p3.y) * (p2.x - p3.x) * (p1.y - p3.y);
}

bool MeshCollider2D::intersectsCircle(const Vector2f &circleCenter, float radius) {
	float radiusSquared = radius * radius;

	Vector2f v1;
	Vector2f v2;
	Vector2f v3;
	Vector2f c1;
	Vector2f c2;
	Vector2f c3;
	Vector2f e1;
	Vector2f e2;
	Vector2f e3;

	float c1sqr;
	float c2sqr;
	float c3sqr;

	float k;
	float length;
	for (unsigned int n = 0; n < this->m_triangleCount; n++)
	{
		// reverse index order so v1-v3 are clockwise instead of counterclockwise
		v1 = this->m_vertices[this->m_triangles[n].idx3];
		v2 = this->m_vertices[this->m_triangles[n].idx2];
		v3 = this->m_vertices[this->m_triangles[n].idx1];

		c1 = Vector2f(circleCenter - v1);
		c2 = Vector2f(circleCenter - v2);
		c3 = Vector2f(circleCenter - v3);

		c1sqr = c1.lengthSquared() - radiusSquared;
		c2sqr = c2.lengthSquared() - radiusSquared;
		c3sqr = c3.lengthSquared() - radiusSquared;

		// Check if triangle corners are within the circle
		if (c1sqr <= 0.0f)
			return true;

		if (c2sqr <= 0.0f)
			return true;

		if (c3sqr <= 0.0f)
			return true;

		e1 = v2 - v1;
		e2 = v3 - v2;
		e3 = v1 - v3;

		// Check if circle center is inside the triangle
		if (e1.y * c1.x >= e1.x * c1.y
			&& e2.y * c2.x >= e2.x * c2.y
			&& e3.y * c3.x >= e3.x * c3.y)
			return true;

		// Check if circle intersects edges

		// First edge
		k = c1.dot(e1);
		if (k > 0.0f)
		{
			length = e1.lengthSquared();

			if (k < length)
			{
				if (c1sqr * length <= k * k)
					return true;
			}
		}

		// Second edge
		k = c2.dot(e2);
		if (k > 0.0f)
		{
			length = e2.lengthSquared();

			if (k < length)
			{
				if (c2sqr * length <= k * k)
					return true;
			}
		}

		// Second edge
		k = c3.dot(e3);
		if (k > 0.0f)
		{
			length = e3.lengthSquared();

			if (k < length)
			{
				if (c3sqr * length <= k * k)
					return true;
			}
		}
	}

	return false;
}
