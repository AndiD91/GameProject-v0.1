#include "DirectXTemplatePCH.h"
#include "Camera.h"
using namespace DirectX;


Camera::Camera() :
m_eyePosition(XMVectorZero()),
m_focusPoint(XMVectorZero()),
m_upDirection(XMVectorZero()),
m_forwardDirection(XMVectorSet(0.0f, 0.0f, 1.0f, 0.0f)),
m_rightDirection(XMVectorSet(1.0f, 0.0f, 0.0f, 0.0f)),
DefaultForward(XMVectorSet(0.0f, 0.0f, 1.0f, 0.0f)),
DefaultRight(XMVectorSet(1.0f, 0.0f, 0.0f, 0.0f)),
m_ViewMatrix(XMMatrixIdentity()),
m_ProjectionMatrix(XMMatrixIdentity()),
m_RotationMatrix(XMMatrixIdentity()),
m_pitch(0),
m_yaw(0),
m_roll(0),
m_moveLeftRight(0),
m_moveBackForward(0)
{
}

Camera::Camera(DirectX::XMVECTOR eyePosition, DirectX::XMVECTOR focusPoint, DirectX::XMVECTOR upDirection, float AspectRatio, float FOVAngleY, float NearClippingPlane, float FarClippingPlane) :
m_eyePosition(XMVectorZero()),
m_focusPoint(XMVectorZero()),
m_upDirection(XMVectorZero()),
m_forwardDirection(XMVectorSet(0.0f, 0.0f, 1.0f, 0.0f)),
m_rightDirection(XMVectorSet(1.0f, 0.0f, 0.0f, 0.0f)),
DefaultForward(XMVectorSet(0.0f, 0.0f, 1.0f, 0.0f)),
DefaultRight(XMVectorSet(1.0f, 0.0f, 0.0f, 0.0f)),
m_ViewMatrix(XMMatrixIdentity()),
m_ProjectionMatrix(XMMatrixIdentity()),
m_RotationMatrix(XMMatrixIdentity()),
m_pitch(0),
m_yaw(0),
m_roll(0),
m_moveLeftRight(0),
m_moveBackForward(0),
m_projectionType(PERSPECTIVE)
{
	m_eyePosition = eyePosition;
	m_focusPoint = focusPoint;
	m_upDirection = upDirection;

	m_AspectRatio = AspectRatio;
	m_FOV = FOVAngleY;
	m_NearClippingPlane = NearClippingPlane;
	m_FarClippingPlane = FarClippingPlane;


	m_ProjectionMatrix = XMMatrixPerspectiveFovLH(m_FOV, m_AspectRatio, m_NearClippingPlane, m_FarClippingPlane);
}


void Camera::setOrthographic()
{
	m_projectionType = ORTHOGRAPHIC;
}

void Camera::setPerspective()
{
	m_projectionType = PERSPECTIVE;
}

void Camera::update()
{
	
	calculateRotation();
	calculateProjectionMatrix();
}

void Camera::calculateRotation()
{
	m_RotationMatrix = XMMatrixRotationRollPitchYaw(m_pitch, m_yaw, m_roll);
	m_focusPoint = XMVector3TransformCoord(DefaultForward, m_RotationMatrix);
	m_focusPoint = XMVector3Normalize(m_focusPoint);

	///////////////**************new**************////////////////////
	/*
	// First-Person Camera
	XMMATRIX RotateYTempMatrix;
	RotateYTempMatrix = XMMatrixRotationY(camYaw);

	camRight = XMVector3TransformCoord(DefaultRight, RotateYTempMatrix);
	camUp = XMVector3TransformCoord(camUp, RotateYTempMatrix);
	camForward = XMVector3TransformCoord(DefaultForward, RotateYTempMatrix);*/

	// Free-Look Camera
	m_rightDirection = XMVector3TransformCoord(DefaultRight, m_RotationMatrix);
	m_forwardDirection = XMVector3TransformCoord(DefaultForward, m_RotationMatrix);
	m_upDirection = XMVector3Cross(m_forwardDirection, m_rightDirection);
	///////////////**************new**************////////////////////

	m_eyePosition += m_moveLeftRight*m_rightDirection;
	m_eyePosition += m_moveBackForward*m_forwardDirection;

	m_moveLeftRight = 0.0f;
	m_moveBackForward = 0.0f;

	m_focusPoint = m_eyePosition + m_focusPoint;

	m_ViewMatrix = XMMatrixLookAtLH(m_eyePosition, m_focusPoint, m_upDirection);
}

void Camera::calculateProjectionMatrix()
{
	switch (m_projectionType)
	{
	case PERSPECTIVE:
		m_ProjectionMatrix = XMMatrixPerspectiveFovLH(m_FOV, m_AspectRatio, m_NearClippingPlane, m_FarClippingPlane);
		break;
	case ORTHOGRAPHIC://TODO: Werte für Höhe und Breite des Fensters fehlen
		m_ProjectionMatrix = XMMatrixOrthographicLH(1280, 720, m_NearClippingPlane, m_FarClippingPlane);
		break;
	default:
		m_ProjectionMatrix = XMMatrixPerspectiveFovLH(m_FOV, m_AspectRatio, m_NearClippingPlane, m_FarClippingPlane);
		break;
	}
}

XMVECTOR Camera::getPosition() const
{
	return m_eyePosition;
}

void Camera::setPosition(const XMVECTOR xmvector)
{
	m_eyePosition = xmvector;
}

XMVECTOR Camera::getfocusPoint() const
{
	return m_focusPoint;
}

void Camera::setfocusPoint(const XMVECTOR xmvector)
{
	m_focusPoint = xmvector;
}

XMVECTOR Camera::getupDirection() const
{
	return m_upDirection;
}

void Camera::setUpdirection(const XMVECTOR xmvector)
{
	m_upDirection = xmvector;
}

XMMATRIX Camera::getViewMatrix() const
{
	return m_ViewMatrix;
}

void Camera::setViewMatrix(const XMMATRIX xmmatrix)
{
	m_ViewMatrix = xmmatrix;
}

XMMATRIX Camera::getProjectionMatrix() const
{
	return m_ProjectionMatrix;
}

void Camera::setProjectionMatrix(const XMMATRIX xmmatrix)
{
	m_ProjectionMatrix = xmmatrix;
}

void Camera::pitch(const float value)
{
	m_pitch += value;
}

void Camera::yaw(const float value)
{
	m_yaw += value;
}

void Camera::roll(const float value)
{
	m_roll += value;
}

Camera::~Camera()
{
}
