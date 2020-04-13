//
// Created by Marcel Schauer on 04.02.20.
//

#ifndef CEDAR_MATRIX4F_HPP
#define CEDAR_MATRIX4F_HPP

#include "Vector4f.hpp"
#include "Quaternionf.hpp"
#include <ostream>
#include <cmath>

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

		Matrix4f(float nm00, float nm01, float nm02, float nm03, float nm10, float nm11, float nm12, float nm13,
				 float nm20, float nm21, float nm22, float nm23, float nm30, float nm31, float nm32, float nm33);

		void zero();

		void identity();

		void invert();

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

		Matrix4f &operator=(const Matrix4f &rhs);

		Matrix4f &operator+=(const Matrix4f &rhs);

		Matrix4f &operator-=(const Matrix4f &rhs);

		Matrix4f &operator*=(const Matrix4f &rhs);

		inline friend Matrix4f operator+(const Matrix4f &lhs, const Matrix4f &rhs)
		{
			return Matrix4f(
					lhs.m_00 + rhs.m_00,
					lhs.m_01 + rhs.m_01,
					lhs.m_02 + rhs.m_02,
					lhs.m_03 + rhs.m_03,
					lhs.m_10 + rhs.m_10,
					lhs.m_11 + rhs.m_11,
					lhs.m_12 + rhs.m_12,
					lhs.m_13 + rhs.m_13,
					lhs.m_20 + rhs.m_20,
					lhs.m_21 + rhs.m_21,
					lhs.m_22 + rhs.m_22,
					lhs.m_23 + rhs.m_23,
					lhs.m_30 + rhs.m_30,
					lhs.m_31 + rhs.m_31,
					lhs.m_32 + rhs.m_32,
					lhs.m_33 + rhs.m_33
					);
		}

		inline friend Matrix4f operator-(const Matrix4f &lhs, const Matrix4f &rhs)
		{
			return Matrix4f(
					lhs.m_00 - rhs.m_00,
					lhs.m_01 - rhs.m_01,
					lhs.m_02 - rhs.m_02,
					lhs.m_03 - rhs.m_03,
					lhs.m_10 - rhs.m_10,
					lhs.m_11 - rhs.m_11,
					lhs.m_12 - rhs.m_12,
					lhs.m_13 - rhs.m_13,
					lhs.m_20 - rhs.m_20,
					lhs.m_21 - rhs.m_21,
					lhs.m_22 - rhs.m_22,
					lhs.m_23 - rhs.m_23,
					lhs.m_30 - rhs.m_30,
					lhs.m_31 - rhs.m_31,
					lhs.m_32 - rhs.m_32,
					lhs.m_33 - rhs.m_33
						   );
		}

		inline friend Matrix4f operator*(const Matrix4f &lhs, const Matrix4f &rhs)
		{
			return Matrix4f(
					std::fmaf(lhs.m_00, rhs.m_00, std::fmaf(lhs.m_10, rhs.m_01, std::fmaf(lhs.m_20, rhs.m_02, lhs.m_30 * rhs.m_03))),
					std::fmaf(lhs.m_01, rhs.m_00, std::fmaf(lhs.m_11, rhs.m_01, std::fmaf(lhs.m_21, rhs.m_02, lhs.m_31 * rhs.m_03))),
					std::fmaf(lhs.m_02, rhs.m_00, std::fmaf(lhs.m_12, rhs.m_01, std::fmaf(lhs.m_22, rhs.m_02, lhs.m_32 * rhs.m_03))),
					std::fmaf(lhs.m_03, rhs.m_00, std::fmaf(lhs.m_13, rhs.m_01, std::fmaf(lhs.m_23, rhs.m_02, lhs.m_33 * rhs.m_03))),
					std::fmaf(lhs.m_00, rhs.m_10, std::fmaf(lhs.m_10, rhs.m_11, std::fmaf(lhs.m_20, rhs.m_12, lhs.m_30 * rhs.m_13))),
					std::fmaf(lhs.m_01, rhs.m_10, std::fmaf(lhs.m_11, rhs.m_11, std::fmaf(lhs.m_21, rhs.m_12, lhs.m_31 * rhs.m_13))),
					std::fmaf(lhs.m_02, rhs.m_10, std::fmaf(lhs.m_12, rhs.m_11, std::fmaf(lhs.m_22, rhs.m_12, lhs.m_32 * rhs.m_13))),
					std::fmaf(lhs.m_03, rhs.m_10, std::fmaf(lhs.m_13, rhs.m_11, std::fmaf(lhs.m_23, rhs.m_12, lhs.m_33 * rhs.m_13))),
					std::fmaf(lhs.m_00, rhs.m_20, std::fmaf(lhs.m_10, rhs.m_21, std::fmaf(lhs.m_20, rhs.m_22, lhs.m_30 * rhs.m_23))),
					std::fmaf(lhs.m_01, rhs.m_20, std::fmaf(lhs.m_11, rhs.m_21, std::fmaf(lhs.m_21, rhs.m_22, lhs.m_31 * rhs.m_23))),
					std::fmaf(lhs.m_02, rhs.m_20, std::fmaf(lhs.m_12, rhs.m_21, std::fmaf(lhs.m_22, rhs.m_22, lhs.m_32 * rhs.m_23))),
					std::fmaf(lhs.m_03, rhs.m_20, std::fmaf(lhs.m_13, rhs.m_21, std::fmaf(lhs.m_23, rhs.m_22, lhs.m_33 * rhs.m_23))),
					std::fmaf(lhs.m_00, rhs.m_30, std::fmaf(lhs.m_10, rhs.m_31, std::fmaf(lhs.m_20, rhs.m_32, lhs.m_30 * rhs.m_33))),
					std::fmaf(lhs.m_01, rhs.m_30, std::fmaf(lhs.m_11, rhs.m_31, std::fmaf(lhs.m_21, rhs.m_32, lhs.m_31 * rhs.m_33))),
					std::fmaf(lhs.m_02, rhs.m_30, std::fmaf(lhs.m_12, rhs.m_31, std::fmaf(lhs.m_22, rhs.m_32, lhs.m_32 * rhs.m_33))),
					std::fmaf(lhs.m_03, rhs.m_30, std::fmaf(lhs.m_13, rhs.m_31, std::fmaf(lhs.m_23, rhs.m_32, lhs.m_33 * rhs.m_33)))
					);
		}

		inline friend Vector3f operator*(const Matrix4f &lhs, const Vector3f &rhs)
		{
			return Vector3f(
					std::fmaf(lhs.m_00, rhs.x, std::fmaf(lhs.m_10, rhs.y, lhs.m_20 * rhs.z)),
					std::fmaf(lhs.m_01, rhs.x, std::fmaf(lhs.m_11, rhs.y, lhs.m_21 * rhs.z)),
					std::fmaf(lhs.m_02, rhs.x, std::fmaf(lhs.m_12, rhs.y, lhs.m_22 * rhs.z))
					);
		}

		inline friend Vector4f operator*(const Matrix4f &lhs, const Vector4f &rhs)
		{
			return Vector4f(
					std::fmaf(lhs.m_00, rhs.x, std::fmaf(lhs.m_10, rhs.y, std::fmaf(lhs.m_20, rhs.z, lhs.m_30 * rhs.w))),
					std::fmaf(lhs.m_01, rhs.x, std::fmaf(lhs.m_11, rhs.y, std::fmaf(lhs.m_21, rhs.z, lhs.m_31 * rhs.w))),
					std::fmaf(lhs.m_02, rhs.x, std::fmaf(lhs.m_12, rhs.y, std::fmaf(lhs.m_22, rhs.z, lhs.m_32 * rhs.w))),
					std::fmaf(lhs.m_03, rhs.x, std::fmaf(lhs.m_13, rhs.y, std::fmaf(lhs.m_23, rhs.z, lhs.m_33 * rhs.w)))
					);
		}

		inline friend bool operator==(const Matrix4f &lhs, const Matrix4f &rhs)
		{
			return lhs.m_00 == rhs.m_00
				   && lhs.m_01 == rhs.m_01
				   && lhs.m_03 == rhs.m_02
				   && lhs.m_03 == rhs.m_03
				   && lhs.m_10 == rhs.m_10
				   && lhs.m_11 == rhs.m_11
				   && lhs.m_12 == rhs.m_12
				   && lhs.m_13 == rhs.m_13
				   && lhs.m_20 == rhs.m_20
				   && lhs.m_21 == rhs.m_21
				   && lhs.m_22 == rhs.m_22
				   && lhs.m_23 == rhs.m_23
				   && lhs.m_30 == rhs.m_30
				   && lhs.m_31 == rhs.m_31
				   && lhs.m_32 == rhs.m_32
				   && lhs.m_33 == rhs.m_33;
		}

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

#endif //CEDAR_MATRIX4F_HPP
