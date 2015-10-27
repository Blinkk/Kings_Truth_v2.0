/**********************************
*  Programmer: Austin Ivicevic
*  DirectX 9 Game Engine
*  Date Created: 06/02/2015
***********************************/
#include "Engine_Core.h"

namespace Smoke
{
	Camera2D::Camera2D()
	{
		// Default position	(start in center for now)
		_position = Vector2(0, 0);

		// Default rotation
		_rotationX = 0.0f;
		_rotationY = 0.0f;
		_rotationZ = 0.0f;

		// Zoom
		_zoomFactor = 0.35f;
	}


	Camera2D::~Camera2D() {}


	void Camera2D::Render()
	{
		// Update position
		_position = _pFollow->GetCurrentPos();

		// Set up view Matrix
		D3DXMATRIX viewMatrix = D3DXMATRIX(
			1, 0, 0, 0,
			0, 1, 0, 0,
			0, 0, 1, 0,
			(FLOAT)(-(_position.x)), (FLOAT)(-(_position.y)), 0, 1);

		// Create matrices
		D3DXMatrixOrthoLH(&_projMatrix, (FLOAT)SCREENW * _zoomFactor, (FLOAT)-SCREENH * _zoomFactor, SCREEN_NEAR, SCREEN_DEPTH);
		D3DXMATRIX identityMatrix;
		D3DXMatrixIdentity(&identityMatrix);

		// Set matrices
		g_Engine->GetDevice()->SetTransform(D3DTS_PROJECTION, &_projMatrix);
		g_Engine->GetDevice()->SetTransform(D3DTS_WORLD, &identityMatrix);
		g_Engine->GetDevice()->SetTransform(D3DTS_VIEW, &viewMatrix);
	}


	void Camera2D::SetRotation(float x, float y, float z)
	{
		_rotationX = x;
		_rotationY = y;
		_rotationZ = z;
	}


	void Camera2D::SetPlayerFollow(Player &player)
	{
		_pFollow = &player;

		if (_pFollow == NULL)
		{
			debug << "\tFailed to set player to follow" << std::endl;
			return;
		}
	}
}