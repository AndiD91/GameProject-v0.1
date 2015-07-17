#pragma once
#include "inc/DirectXTemplatePCH.h"


class Camera
{
public:
	Camera();
	explicit Camera(DirectX::XMVECTOR eyePosition, DirectX::XMVECTOR focusPoint, DirectX::XMVECTOR upDirection, float AspectRatio=1.0F/16.0F, float FOVAngleY = DirectX::XMConvertToRadians(45.0f), float NearClippingPlane=0.1F, float FarClippingPlane=100.0F);
	~Camera();

private:
	enum ProjectionType
	{
		ORTHOGRAPHIC,
		PERSPECTIVE
	};

	DirectX::XMVECTOR m_eyePosition;
	DirectX::XMVECTOR m_focusPoint;
	DirectX::XMVECTOR m_upDirection;
	DirectX::XMVECTOR m_forwardDirection;
	DirectX::XMVECTOR m_rightDirection;

	DirectX::XMVECTOR DefaultForward;
	DirectX::XMVECTOR DefaultRight;
	

	DirectX::XMMATRIX m_ViewMatrix;
	DirectX::XMMATRIX m_ProjectionMatrix;

	DirectX::XMMATRIX m_RotationMatrix;

	float m_pitch;
	float m_yaw;
	float m_roll;

	float m_moveLeftRight;
	float m_moveBackForward;

	float m_AspectRatio;
	float m_FOV;
	float m_NearClippingPlane;
	float m_FarClippingPlane;

	ProjectionType m_projectionType;

public:
	float getAspectRatio() const
	{
		return m_AspectRatio;
	}

	void setAspectRatio(float value)
	{
		m_AspectRatio = value;
	}

	float getFOV() const
	{
		return m_FOV;
	}

	void setFOV(float value)
	{
		m_FOV = value;
	}

	float getNearClippingPlane() const
	{
		return m_NearClippingPlane;
	}

	void setNearClippingPlane(float value)
	{
		m_NearClippingPlane = value;
	}

	float getfarClippingPlane() const
	{
		return m_FarClippingPlane;
	}

	void setFarClippingPlane(float value)
	{
		m_FarClippingPlane = value;
	}

	void update();

	void setOrthographic();
	void setPerspective();
private:
	void calculateRotation();
	void calculateProjectionMatrix();


public:
	DirectX::XMVECTOR getPosition() const;
	void setPosition(const DirectX::XMVECTOR xmvector);

	DirectX::XMVECTOR getfocusPoint() const;
	void setfocusPoint(const DirectX::XMVECTOR xmvector);

	DirectX::XMVECTOR getupDirection() const;
	void setUpdirection(const DirectX::XMVECTOR xmvector);


	DirectX::XMMATRIX getViewMatrix() const;
	void setViewMatrix(const DirectX::XMMATRIX xmvector);

	DirectX::XMMATRIX getProjectionMatrix() const;
	void setProjectionMatrix(const DirectX::XMMATRIX xmvector);

	void pitch(const float value);
	void yaw(const float value);
	void roll(const float value);
	
	
};

