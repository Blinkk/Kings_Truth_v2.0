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
	class Camera2D
	{
	private:
		float _positionX, _positionY, _rotationZ;
		float _rotationX, _rotationY;
		D3DXMATRIX _viewMatrix;

	public:
		Camera2D();
		~Camera2D();

		/*
			This function generates a View Matrix that 
			is then used to determine the camera's
			viewport. This is updated every frame.
		*/
		void Render();

		//////////////////////////////
		// Accessor/Mutator functions
		//////////////////////////////
		void GetViewMatrix(D3DXMATRIX &viewMatrix) { viewMatrix = _viewMatrix; }
		void SetPosition(float x, float y);		
		void SetRotation(float x, float y, float z);		

	};	// End of class
}	// End of namespace
#endif