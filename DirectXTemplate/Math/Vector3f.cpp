#include "Vector3f.h"
#include "Quaternion.h"


namespace Math
{
	Vector3f::Vector3f()
	{
		m_x = m_y = m_z = 0.0f;
	}

	Vector3f::Vector3f(const float x, const float y, const float z)
	{

		m_x = x;
		m_y = y;
		m_z = z;

	}

	Vector3f::Vector3f(Vector3f* v)
	{
		m_x = v->GetX();
		m_y = v->GetY();
		m_z = v->GetZ();
	}


	Vector3f::~Vector3f()
	{

	}


	Vector3f Vector3f::Rotate(const float angle, const Vector3f& axis)
	{
		const float sinHalfAngle = static_cast<float>(sin(Math::ToRadians(angle / 2)));
		const float cosHalfAngle = static_cast<float>(cos(Math::ToRadians(angle / 2)));

		const float rX = axis.GetX() * sinHalfAngle;
		const float rY = axis.GetY()* sinHalfAngle;
		const float rZ = axis.GetZ()* sinHalfAngle;
		const float rW = cosHalfAngle;

		Quaternion rotation = Quaternion(rX, rY, rZ, rW);
		Quaternion conjugate = rotation.Conjugate();

		Quaternion w = rotation.Multiply(this).Multiply(conjugate);

		return Vector3f(w.GetX(), w.GetY(), w.GetZ());
	}

	float Vector3f::Length()
	{
		return sqrt(m_x * m_x + m_y * m_y + m_z * m_z);
	}

	float Vector3f::Dot(const Vector3f& v)
	{
		return m_x * v.GetX() + m_y * v.GetY() + m_z * v.GetZ();
	}

	Vector3f Vector3f::Abs()
	{
		return Vector3f(abs(m_x), abs(m_y), abs(m_z));
	}

	Vector3f Vector3f::Normalized()
	{
		const float length = Length();
		return Vector3f(m_x / length, m_y / length, m_z / length);

	}



	Vector3f Vector3f::Plus(const Vector3f& v)
	{
		return Vector3f(m_x + v.GetX(), m_y + v.GetY(), m_z + v.GetZ());
	}

	Vector3f Vector3f::Plus(const float f)
	{
		return Vector3f(m_x + f, m_y + f, m_z + f);
	}


	Vector3f Vector3f::Minus(const Vector3f& v)
	{
		return Vector3f(m_x - v.GetX(), m_y - v.GetY(), m_z - v.GetZ());
	}

	Vector3f Vector3f::Minus(const float f)
	{
		return Vector3f(m_x - f, m_y - f, m_z - f);
	}

	Vector3f Vector3f::Times(const Vector3f& v)
	{
		return Vector3f(m_x * v.GetX(), m_y * v.GetY(), m_z * v.GetZ());
	}

	Vector3f Vector3f::Times(const float f)
	{
		return Vector3f(m_x * f, m_y * f, m_z * f);
	}

	Vector3f Vector3f::DividedBy(const Vector3f& v)
	{
		return Vector3f(m_x / v.GetX(), m_y / v.GetY(), m_z / v.GetZ());
	}

	Vector3f Vector3f::DividedBy(const float f)
	{
		return Vector3f(m_x / f, m_y / f, m_z / f);
	}

	Vector3f Vector3f::Cross(const Vector3f& v)
	{
		const float _x = m_y * v.GetZ() - m_z * v.GetY();
		const float _y = m_z * v.GetX() - m_x * v.GetZ();
		const float _z = m_x * v.GetY() - m_y * v.GetX();

		return Vector3f(_x, _y, _z);
	}
}