#ifndef VECTOR3F_H
#define VECTOR3F_H
#include "../Math/MathHelper.h"

namespace Math
{
	class Vector3f
	{
	public:
		Vector3f();
		Vector3f(const float x, const float y, const float z);
		Vector3f(Vector3f* v);
		~Vector3f();

		float GetX() const{ return m_x; }
		float GetY() const{ return m_y; }
		float GetZ() const{ return m_z; }
		void SetX(const float x){ m_x = x; }
		void SetY(const float y){ m_y = y; }
		void SetZ(const float z){ m_z = z; }
		float Length();
		float Dot(const Vector3f& v);
		Vector3f Abs();
		Vector3f Normalized();
		Vector3f Rotate(const float angle, const Vector3f& axis);
		Vector3f Plus(const Vector3f& v);
		Vector3f Plus(const float f);
		Vector3f Minus(const Vector3f& v);
		Vector3f Minus(const float f);
		Vector3f Times(const Vector3f& v);
		Vector3f Times(const float f);
		Vector3f DividedBy(const Vector3f& v);
		Vector3f DividedBy(const float f);
		Vector3f Cross(const Vector3f& v);


	private:
		float m_x;
		float m_y;
		float m_z;


	};
}

#endif
