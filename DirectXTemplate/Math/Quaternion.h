#ifndef QUATERNION_H
#define QUATERNION_H
#include "Vector3f.h"
#include "../Math/MathHelper.h"
#include <utility>

namespace Math
{

	class Quaternion
	{
	public:
		Quaternion();
		Quaternion(const float x, const float y, const float z, const float w);
		Quaternion(Quaternion* q);
		~Quaternion();
		float Length();
		Quaternion Normalized();
		Quaternion Conjugate();
		Quaternion Multiply(const Quaternion& r);

		Quaternion Multiply(const Vector3f& r);


		float GetX() const{ return m_x; }
		float GetY() const{ return m_y; }
		float GetZ() const{ return m_z; }
		float GetW() const{ return m_w; }
		void SetX(float x){ m_x = x; }
		void SetY(float y){ m_y = y; }
		void SetZ(float z){ m_z = z; }
		void SetW(float w){ m_w = w; }
	private:
		float m_x;
		float m_y;
		float m_z;
		float m_w;


	};

}

#endif