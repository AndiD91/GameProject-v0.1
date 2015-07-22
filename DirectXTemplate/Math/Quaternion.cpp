#include "Quaternion.h"


namespace Math
{
	Quaternion::Quaternion()
	{
		m_x = m_y = m_z = m_w = 0.0f;
	}

	Quaternion::~Quaternion()
	{ 

	}

	Quaternion::Quaternion(const float x, const float y, const float z, const float w)
	{
		m_x = x;
		m_y = y;
		m_z = z;
		m_w = w;
	}

	Quaternion::Quaternion(Quaternion* q)
	{
		m_x = q->GetX();
		m_y = q->GetY();
		m_z = q->GetZ();
		m_w = q->GetW();
	}

	float Quaternion::Length()
	{
		return static_cast<float>(sqrt(m_x * m_x + m_y * m_y + m_z * m_z + m_w * m_w));
	}

	Quaternion Quaternion::Normalized()
	{
		float length = Length();
		return Quaternion(m_x / length, m_y / length, m_z / length, m_w / length);

	}

	Quaternion Quaternion::Conjugate()
	{
		return Quaternion(-m_x, -m_y, -m_z, m_w);
	}


	Quaternion Quaternion::Multiply(const Quaternion& r)
	{
		float _w = m_w * r.GetW() - m_x * r.GetX() - m_y * r.GetY() - m_z * r.GetZ();
		float _x = m_x * r.GetW() + m_w * r.GetX() + m_y * r.GetZ() - m_z * r.GetY();
		float _y = m_y * r.GetW() + m_w * r.GetY() + m_z * r.GetX() - m_x * r.GetZ();
		float _z = m_z * r.GetW() + m_w * r.GetZ() + m_x * r.GetY() - m_y * r.GetX();

		return Quaternion(_x, _y, _z, _w);
	}

	Quaternion Quaternion::Multiply(const Vector3f& r)
	{
		float _w = -m_x * r.GetX() - m_y * r.GetY() - m_z * r.GetZ();
		float _x = m_w * r.GetX() + m_y * r.GetZ() - m_z * r.GetY();
		float _y = m_w * r.GetY() + m_z * r.GetX() - m_x * r.GetZ();
		float _z = m_w * r.GetZ() + m_x * r.GetY() - m_y * r.GetX();

		return Quaternion(_x, _y, _z, _w);
	}
}