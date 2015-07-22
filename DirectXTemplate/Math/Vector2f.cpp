#include "Vector2f.h"


namespace Math
{
	Vector2f::Vector2f()
	{
		m_x = m_y = 0.0f;
	}

	Vector2f::Vector2f(const float x, const float y)
	{

		m_x = x;
		m_y = y;

	}

	Vector2f::Vector2f(Vector2f* v)
	{
		m_x = v->GetX();
		m_y = v->GetY();
	}


	Vector2f::~Vector2f()
	{

	}


	float Vector2f::Length()
	{
		return sqrt(m_x * m_x + m_y * m_y);
	}

	float Vector2f::Dot(const Vector2f& v)
	{
		return m_x * v.GetX() + m_y * v.GetY();
	}

	Vector2f Vector2f::Abs()
	{
		return Vector2f(abs(m_x), abs(m_y));
	}

	Vector2f Vector2f::Normalized()
	{
		float length = Length();
		return Vector2f(m_x / length, m_y / length);

	}

	Vector2f Vector2f::Rotate(float angle)
	{
		double radius = angle* M_PI / 180.0;
		double cosinus = cos(radius);
		double sinus = sin(radius);

		return Vector2f(static_cast<float>(m_x * cosinus - m_y * sinus), static_cast<float>(m_x * sinus + m_y * cosinus));



	}

	Vector2f Vector2f::Plus(const Vector2f& v)
	{
		return Vector2f(m_x + v.GetX(), m_y + v.GetY());
	}

	Vector2f Vector2f::Plus(const float f)
	{
		return Vector2f(m_x + f, m_y + f);
	}


	Vector2f Vector2f::Minus(const Vector2f& v)
	{
		return Vector2f(m_x - v.GetX(), m_y - v.GetY());
	}

	Vector2f Vector2f::Minus(const float f)
	{
		return Vector2f(m_x - f, m_y - f);
	}

	Vector2f Vector2f::Times(const Vector2f& v)
	{
		return Vector2f(m_x * v.GetX(), m_y * v.GetY());
	}

	Vector2f Vector2f::Times(const float f)
	{
		return Vector2f(m_x * f, m_y * f);
	}

	Vector2f Vector2f::DividedBy(const Vector2f& v)
	{
		return Vector2f(m_x / v.GetX(), m_y / v.GetY());
	}

	Vector2f Vector2f::DividedBy(const float f)
	{
		return Vector2f(m_x / f, m_y / f);
	}
}





//
//void func1(int value)
//{
//}
//
//void func2(void(*func)(int), int value)
//{
//	func(value);
//}
//
//void loop()
//{
//	func2(func1, 1234);
//}