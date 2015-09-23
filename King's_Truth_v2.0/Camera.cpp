/**********************************
*  Programmer: Austin Ivicevic
*  DirectX 9 Game Engine
*  Date Created: 06/02/2015
***********************************/
/** Note: This class is closely modeled
	after the book code from...
		Multi-Threaded Game Engine Design
		Copyright 2010 by Jonathan Harbour
**/
#include "Camera.h"

namespace Smoke
{
	Camera::Camera()
	{
		// Default position
		_positionX = 0.0f;
		_positionY = 0.0f;
		_positionZ = 0.0f;

		// Default rotation
		_rotationX = 0.0f;
		_rotationY = 0.0f;
		_rotationZ = 0.0f;
	}


	Camera::~Camera() {}


	void Camera::Render()
	{
		D3DXVECTOR3 up, position, lookAt;
		float yaw, pitch, roll;
		D3DXMATRIX rotationMatrix;

		// Setup the vector that points upwards
		up.x = 0.0f;
		up.y = 1.0f;
		up.z = 0.0f;

		// Setup the position of the camera
		position.x = _positionX;
		position.y = _positionY;
		position.z = _positionZ;

		// Setup where the camera is looking
		lookAt.x = 0.0f;
		lookAt.y = 0.0f;
		lookAt.z = 1.0f;

		// Set the yaw (Y axis), pitch (X axis), and roll (Z axis) rotations in radians
		pitch = _rotationX * 0.0174532925f;
		yaw = _rotationY * 0.0174532925f;
		roll = _rotationZ * 0.0174532925f;

		// Create the rotation matrix
		D3DXMatrixRotationYawPitchRoll(&rotationMatrix, yaw, pitch, roll);

		// Transform the lookAt and up vector by the rotation matrix
		D3DXVec3TransformCoord(&lookAt, &lookAt, &rotationMatrix);
		D3DXVec3TransformCoord(&up, &up, &rotationMatrix);

		// Translate the rotated camera position to the location of the viewer
		lookAt = position + lookAt;

		// Finally create the view matrix from the three updated vectors
		D3DXMatrixLookAtLH(&_viewMatrix, &position, &lookAt, &up);
	}


	void Camera::SetPosition(float x, float y, float z)
	{
		_positionX = x;
		_positionY = y;
		_positionZ = z;
	}


	void Camera::SetRotation(float x, float y, float z)
	{
		_rotationX = x;
		_rotationY = y;
		_rotationZ = z;
	}
}