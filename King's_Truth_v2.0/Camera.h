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
#ifndef CAMERA_H
#define CAMERA_H
#include "stdafx.h"

namespace Smoke
{
	class Camera
	{
	private:
		float _positionX, _positionY, _positionZ;
		float _rotationX, _rotationY, _rotationZ;
		D3DXMATRIX _viewMatrix;

	public:
		Camera();
		~Camera();
		void Render();									// Generates a view matrix

		//////////////////////////////
		// Accessor/Mutator functions
		//////////////////////////////
		void GetViewMatrix(D3DXMATRIX &viewMatrix) { viewMatrix = _viewMatrix; }
		void SetPosition(float x, float y, float z);	// Defined in .cpp
		void SetRotation(float x, float y, float z);	// Defined in .cpp

	};	// End of class
}	// End of namespace
#endif