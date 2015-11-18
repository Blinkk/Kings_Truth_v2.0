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
#include "Player.h"

namespace Smoke
{
	class Camera2D
	{
	private:
		Vector2 _position;
		float _rotationX, _rotationY, _rotationZ;
		float _zoomFactor;
		D3DXMATRIX _projMatrix;

	public:
		Camera2D();
		~Camera2D();

		/*
			This function generates a projection 
			matrix for 2D rendering. This is updated
			every time the main Render() call is made
		*/
		void Render();

		//////////////////////////////
		// Accessor/Mutator functions
		//////////////////////////////
		Vector2 GetCurrentPos() { return _position; }
		float GetZoomFactor() { return _zoomFactor; }
		void SetZoomFactor(float zoom) { _zoomFactor = zoom; }
		void GetProjMatrix(D3DXMATRIX &projMatrix) { projMatrix = _projMatrix; }	
		void SetRotation(float x, float y, float z);	

	};	// End of class
}	// End of namespace
#endif