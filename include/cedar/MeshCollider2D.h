//
// Created by masy on 11.03.20.
//

#ifndef CEDAR_MESHCOLLIDER2D_H
#define CEDAR_MESHCOLLIDER2D_H

#include "cedar/Vector2f.h"

/**
 * Base namespace of the cedar engine.
 */
namespace cedar
{

	/**
	 * Struct containing indices to 3 corners that make up a triangle.
	 */
	struct Triangle
	{
		/**
		 * The index of the first corner.
		 */
		unsigned int idx1;
		/**
		 * The index of the second corner.
		 */
		unsigned int idx2;
		/**
		 * The index of the third corner.
		 */
		unsigned int idx3;
	};

	/**
	 * Class storing a two dimensional mesh made of triangles and providing intersection related methods for them.
	 */
	class MeshCollider2D
	{
	private:
		/**
		 * A pointer to an array of vertices.
		 */
		Vector2f *m_vertices;
		/**
		 * The number of triangles the mesh of this collider is made of.
		 */
		unsigned int m_triangleCount;
		/**
		 * A pointer to an array of triangles that make up this collider's mesh.
		 */
		Triangle *m_triangles;

	public:
		/**
		 * Creates a new two dimensional mesh collider.
		 *
		 * @param vertices A pointer to the array of vertices.
		 * @param triangleCount The number of triangles the mesh is made of.
		 * @param triangles A pointer to the array of triangles that make up the collider's mesh.
		 */
		MeshCollider2D(Vector2f *vertices, unsigned int triangleCount, Triangle *triangles);

		/**
		 * Destroys the mesh collider.
		 */
		~MeshCollider2D();

		/**
		 * Checks if the given circle intersects with the mesh.
		 *
		 * @param circleCenter The center of the circle.
		 * @param radius The radius of the circle.
		 * @return <code>true</code> if the circle intersects with a triangle of the mesh.
		 */
		bool intersectsCircle(const Vector2f &circleCenter, float radius);
	};
}

#endif //CEDAR_MESHCOLLIDER2D_H
