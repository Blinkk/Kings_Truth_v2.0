/**********************************
*  Programmer: Austin Ivicevic
*  DirectX 9 Game Engine
*  Date Created: 06/02/2015
***********************************/
#ifndef DIRECTX_H
#define DIRECTX_H
#include "stdafx.h"


//////////////////////////////
// Note: This code leaks both
// the d3dDevice and Context
// and needs to be fixed.
//////////////////////////////

namespace Smoke
{
	class Direct3D
	{
	private:
		D3D_DRIVER_TYPE _driverType;				// Graphics card driver type
		D3D_FEATURE_LEVEL _featureLevel;			// Feature level for D3D
		D3DXMATRIX _projMatrix;						// Projection matrix
		D3DXMATRIX _worldMatrix;					// World matrix
		D3DXMATRIX _orthoMatrix;					// Orthagraphic matrix (for 2D)

		Direct3D();

	public:
		static Direct3D& GetInstance()
		{
			Direct3D *pInstance = NULL;

			if (!pInstance)
			{
				pInstance = new Direct3D();
			}

			return (*pInstance);
		}

		~Direct3D();
		bool Initialize(HINSTANCE hInstance, 
			bool fullScrn, float screenDepth, float screenNear);
		void Shutdown();

		//////////////////////
		// Utility functions
		//////////////////////


		//////////////////////////////
		// Accessor/Mutator functions
		//////////////////////////////
		void GetWorldMatrix(D3DXMATRIX &wm) { wm = _worldMatrix; }
		void GetProjMatrix(D3DXMATRIX &pm) { pm = _projMatrix; }
		void GetOrthoMatrix(D3DXMATRIX &om) { om = _orthoMatrix; }
	};
}

#endif