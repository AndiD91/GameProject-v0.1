#ifndef VECTOR2F_H
#define VECTOR2F_H
#include "../Math/MathHelper.h"

namespace Math
{
	class Vector2f
	{
	public:
		Vector2f();
		Vector2f(const float x, const float y);
		explicit Vector2f(Vector2f* v);
		~Vector2f();

		float GetX() const{ return m_x; }
		float GetY() const{ return m_y; }
		void SetX(float x){ m_x = x; }
		void SetY(float y){ m_y = y; }

		float Length();
		float Dot(const Vector2f& v);
		Vector2f Abs();
		Vector2f Normalized();
		Vector2f Rotate(const float angle);
		Vector2f Plus(const Vector2f& v);
		Vector2f Plus(const float f);
		Vector2f Minus(const Vector2f& v);
		Vector2f Minus(const float f);
		Vector2f Times(const Vector2f& v);
		Vector2f Times(const float f);
		Vector2f DividedBy(const Vector2f& v);
		Vector2f DividedBy(const float f);



	private:
		float m_x;
		float m_y;

	};
}

#endif
