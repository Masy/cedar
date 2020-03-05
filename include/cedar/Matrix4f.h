//
// Created by Marcel Schauer on 04.02.20.
//

#ifndef CEDAR_MATRIX4F_H
#define CEDAR_MATRIX4F_H

#include "Vector3f.h"
#include "Quaternionf.h"
#include <ostream>

/**
 * Base namespace of the cedar engine.
 */
namespace cedar
{

	/**
	 * Column major 4x4 float matrix implementation based on <a href="https://github.com/JOML-CI/JOML">JOML</a>.
	 *
	 * Since OpenGL is column major this will make it easier to upload the data to the graphics card.
	 */
	class Matrix4f
	{
	public:
		/**
		 * m_00 m_10 m_20 m_30
		 * m_01 m_11 m_21 m_31
		 * m_02 m_12 m_22 m_32
		 * m_03 m_13 m_23 m_33
		 */
		float m_00;
		float m_01;
		float m_02;
		float m_03;
		float m_10;
		float m_11;
		float m_12;
		float m_13;
		float m_20;
		float m_21;
		float m_22;
		float m_23;
		float m_30;
		float m_31;
		float m_32;
		float m_33;

		Matrix4f();

		explicit Matrix4f(float value);

		explicit Matrix4f(const float *values);

		Matrix4f(const Matrix4f &copy);

		void zero();

		void identity();

		void perspective(float aspectRatio, float fov, float near, float far);

		void orthographic(float left, float right, float top, float bottom, float near, float far);

		//	void translateX(float offset);
		//	void translationX(float offset);
		//	void translateY(float offset);
		//	void translationY(float offset);
		//	void translateZ(float offset);
		//	void translationZ(float offset);
		void translate(float offsetX, float offsetY, float offsetZ);

		void translate(const Vector3f *offset);

		void translation(float offsetX, float offsetY, float offsetZ);

		void translation(const Vector3f *offset);

		//	void rotateX(float angle);
		//	void rotateLocalX(float angle);
		//	void rotationX(float angle);
		//	void rotateY(float angle);
		//	void rotateLocalY(float angle);
		//	void rotationY(float angle);
		//	void rotateZ(float angle);
		//	void rotateLocalZ(float angle);
		//	void rotationZ(float angle);
		void rotate(float angleX, float angleY, float angleZ);

		void rotate(const Vector3f *angle);

		void rotate(const Quaternionf *rotation);

		void rotation(float angleX, float angleY, float angleZ);

		void rotation(const Vector3f *angle);

		void rotation(const Quaternionf *rotation);

		//	void rotateAxis(float angle, float axisX, float axisY, float axisZ);
		//	void rotateAxis(float angle, const Vector3f *axis);
		//	void rotationAxis(float angle, float axisX, float axisY, float axisZ);
		//	void rotationAxis(float angle, const Vector3f *axis);
		//	void scaleX(float scale);
		//	void scalingX(float scale);
		//	void scaleY(float scale);
		//	void scalingY(float scale);
		//	void scaleZ(float scale);
		//	void scalingZ(float scale);
		void scale(float scaleX, float scaleY, float scaleZ);

		void scale(const Vector3f *scale);

		void scaling(float scaleX, float scaleY, float scaleZ);

		void scaling(const Vector3f *scaling);

		friend std::ostream &operator<<(std::ostream &os, const Matrix4f &matrix)
		{
			os << "[" << matrix.m_00 << ", " << matrix.m_10 << ", " << matrix.m_20 << ", " << matrix.m_30 << "]\n";
			os << "[" << matrix.m_01 << ", " << matrix.m_11 << ", " << matrix.m_21 << ", " << matrix.m_31 << "]\n";
			os << "[" << matrix.m_02 << ", " << matrix.m_12 << ", " << matrix.m_22 << ", " << matrix.m_32 << "]\n";
			os << "[" << matrix.m_03 << ", " << matrix.m_13 << ", " << matrix.m_23 << ", " << matrix.m_33 << "]";
			return os;
		}
	};

}

#endif //CEDAR_MATRIX4F_H
