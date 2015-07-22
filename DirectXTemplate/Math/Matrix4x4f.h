#ifndef MATRIX4X4F_H
#define MATRIX4X4F_H

#define SIZE_ARRAY 4
#include "../Math/MathHelper.h"

namespace Math
{
	class Matrix4x4f
	{
	public:
		Matrix4x4f();
		~Matrix4x4f();

		void SetM(const float f[SIZE_ARRAY][SIZE_ARRAY]);
		float Get(const int row, const int col) const;
		float** GetM();
		void Set(const int row, const int col, const float value);
		void SetIdentity();
		static Matrix4x4f initTranslation(const float x, const float y, const float z);
		static Matrix4x4f initRotation(const float x, const float y, const float z);
		static Matrix4x4f initScale(const float x, const float y, const float z);
		Matrix4x4f Multiply(const Matrix4x4f& m);
		//static Matrix4x4f InitProjection(const float fov, const float width, const float height, const float zNear, const float zFar);
		//static Matrix4x4f InitCamera(Vector3f forward, Vector3f up);
	private:
		const int arraysize = 4;
		float m_matrix[SIZE_ARRAY][SIZE_ARRAY];

	};
}


#endif