#include "Matrix4x4f.h"
#include <assert.h>
#include <memory.h>



namespace Math
{
	Matrix4x4f::Matrix4x4f()
	{
		SetIdentity();
	}

	Matrix4x4f::~Matrix4x4f()
	{

	}

	void Matrix4x4f::SetM(const float f[SIZE_ARRAY][SIZE_ARRAY])
	{
		m_matrix[0][0] = f[0][0];
		m_matrix[0][1] = f[0][1];
		m_matrix[0][2] = f[0][2];
		m_matrix[0][3] = f[0][3];
		m_matrix[1][0] = f[1][0];
		m_matrix[1][1] = f[1][1];
		m_matrix[1][2] = f[1][2];
		m_matrix[1][3] = f[1][3];
		m_matrix[2][0] = f[2][0];
		m_matrix[2][1] = f[2][1];
		m_matrix[2][2] = f[2][2];
		m_matrix[2][3] = f[2][3];
		m_matrix[3][0] = f[3][0];
		m_matrix[3][1] = f[3][1];
		m_matrix[3][2] = f[3][2];
		m_matrix[3][3] = f[3][3];
	}

	float Matrix4x4f::Get(const int row, const int col) const
	{
		assert(row >= 0 && row < SIZE_ARRAY);
		assert(col >= 0 && col < SIZE_ARRAY);

		return this->m_matrix[row][col];
	}

	float** Matrix4x4f::GetM()
	{

		float res[4][4];
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				res[i][j] = m_matrix[i][j];
			}
		}

		return reinterpret_cast<float**>(res);
	}

	void Matrix4x4f::Set(const int row, const int col, const float value)
	{
		assert(row >= 0 && row < SIZE_ARRAY);
		assert(col >= 0 && col < SIZE_ARRAY);

		this->m_matrix[row][col] = value;

	}


	void Matrix4x4f::SetIdentity()
	{
		memset(&this->m_matrix, 0, sizeof(float) * SIZE_ARRAY * SIZE_ARRAY);
		this->m_matrix[0][0] = 1.0f;
		this->m_matrix[1][1] = 1.0f;
		this->m_matrix[2][2] = 1.0f;
		this->m_matrix[3][3] = 1.0f;


	}

	Matrix4x4f Matrix4x4f::initTranslation(const float x, const float y, const float z)
	{
		Matrix4x4f result = Matrix4x4f();

		result.Set(0, 3, x);
		result.Set(1, 3, y);
		result.Set(2, 3, z);

		return result;


	}

	Matrix4x4f Matrix4x4f::initRotation(const float x, const float y, const float z)
	{

		Matrix4x4f result = Matrix4x4f();
		Matrix4x4f rx = Matrix4x4f();
		Matrix4x4f ry = Matrix4x4f();
		Matrix4x4f rz = Matrix4x4f();
	
		float xRad = static_cast<float>(Math::ToRadians(x));
		float yRad = static_cast<float>(Math::ToRadians(y));
		float zRad = static_cast<float>(Math::ToRadians(z));

		rz.m_matrix[0][0] = static_cast<float>(cos(zRad));
		rz.m_matrix[0][1] = -static_cast<float>(sin(zRad));
		rz.m_matrix[1][0] = static_cast<float>(sin(zRad));
		rz.m_matrix[1][1] = static_cast<float>(cos(zRad));

		rx.m_matrix[1][1] = static_cast<float>(cos(xRad));
		rx.m_matrix[1][2] = -static_cast<float>(sin(xRad));
		rx.m_matrix[2][1] = static_cast<float>(sin(xRad));
		rx.m_matrix[2][2] = static_cast<float>(cos(xRad));

		ry.m_matrix[0][0] = static_cast<float>(cos(yRad));
		ry.m_matrix[0][2] = -static_cast<float>(sin(yRad));
		ry.m_matrix[2][0] = static_cast<float>(sin(yRad));
		ry.m_matrix[2][2] = static_cast<float>(cos(yRad));

		result.SetM((rz.Multiply(ry.Multiply(rx)).m_matrix));
		return result;
	}

	Matrix4x4f Matrix4x4f::initScale(const float x, const float y, const float z)
	{
		Matrix4x4f result = Matrix4x4f();
		result.Set(0, 0, x);
		result.Set(1, 1, y);
		result.Set(2, 2, z);
		result.Set(3, 3, 1.0f);
		return result;

	}

	Matrix4x4f Matrix4x4f::Multiply(const Matrix4x4f& m)
	{
		Matrix4x4f result = Matrix4x4f();

		for (int i = 0; i < SIZE_ARRAY; i++)
		{
			for (int j = 0; j < SIZE_ARRAY; j++)
			{
				result.Set(i, j, m_matrix[i][0] * m.Get(0, j) +
					m_matrix[i][1] * m.Get(1, j) +
					m_matrix[i][2] * m.Get(2, j) +
					m_matrix[i][3] * m.Get(3, j));
			}
		}

		return result;

	}
}
//Matrix4x4f Matrix4x4f::InitProjection(const float fov, const float width, const float height, const float zNear, const float zFar)
//{
//	Matrix4x4f result = Matrix4x4f();
//	float aspectRatio = width / height;
//	float tanHalfFOV = static_cast<float>(tan(Math::ToRadians(fov / 2)));
//	float zRange = zNear - zFar;
//
//	result.Set(0, 0, 1.0f / (tanHalfFOV * aspectRatio));
//	result.Set(1, 1, 1.0f / tanHalfFOV);
//	result.Set(2, 2, (-zNear - zFar) / zRange);
//	result.Set(2, 3, 2 * zFar * zNear / zRange);
//	result.Set(3, 2, 1);
//	result.Set(3, 3, 0);
//	 								
//	return result;
//	
//}
//
//Matrix4x4f Matrix4x4f::InitCamera(Vector3f forward, Vector3f up)
//{
//	Matrix4x4f result = Matrix4x4f();
//
//	Vector3f f = forward.Normalized();
//	Vector3f right = up.Normalized();
//	right = right.Cross(f);
//
//	Vector3f u = f.Cross(right);
//
//	result.Set(0,0,right.GetX());
//	result.Set(0, 1, right.GetY());
//	result.Set(0, 2, right.GetZ());
//	result.Set(1, 0, u.GetX());
//	result.Set(1, 1, u.GetY());
//	result.Set(1, 2, u.GetZ());
//	result.Set(2, 0, f.GetX());
//	result.Set(2, 1, f.GetY());
//	result.Set(2, 2, f.GetZ());
//	
//
//
//	return result;
//}