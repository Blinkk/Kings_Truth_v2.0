/**********************************
*  Programmer: Austin Ivicevic
*  DirectX 9 Game Engine
*  Date Created: 06/02/2015
***********************************/
#include "Engine_Core.h"

namespace Smoke
{
	Direct3D::Direct3D()
	{

	}


	Direct3D::~Direct3D() {}


	bool Direct3D::Initialize(HINSTANCE hINstance, bool fullScrn, float screenDepth, float screenNear)
	{
		////////////////////////////////////////
		// Initialize Direct3D 9
		////////////////////////////////////////
		HRESULT result;

		g_Engine->GetContext() = Direct3DCreate9(D3D_SDK_VERSION);
		if (!g_Engine->GetContext())
		{
			debug << "\t unable to create D3DContext" << std::endl;
			return false;
		}

		// Get system desktop color depth
		D3DDISPLAYMODE dm;
		g_Engine->GetContext()->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &dm);

		// Set Direct3D presentation parameters
		D3DPRESENT_PARAMETERS d3dpp;
		ZeroMemory(&d3dpp, sizeof(d3dpp));
		d3dpp.Windowed = (!fullScrn);
		d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
		d3dpp.EnableAutoDepthStencil = 1;
		d3dpp.AutoDepthStencilFormat = D3DFMT_D24S8;
		d3dpp.Flags = D3DPRESENTFLAG_DISCARD_DEPTHSTENCIL;
		d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;
		d3dpp.BackBufferFormat = dm.Format;
		d3dpp.BackBufferCount = 1;
		d3dpp.BackBufferWidth = SCREENW;
		d3dpp.BackBufferHeight = SCREENH;
		d3dpp.hDeviceWindow = g_Engine->GetWindowHandle();
		d3dpp.MultiSampleType = D3DMULTISAMPLE_NONE;

		// Create Direct3D device
		result = g_Engine->GetContext()->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, g_Engine->GetWindowHandle(),
			D3DCREATE_HARDWARE_VERTEXPROCESSING, &d3dpp, &g_Engine->GetDevice());
		if (result != D3D_OK)
		{
			debug << "\tUnable to create D3DDevice" << std::endl;
			return false;
		}

		// Get a pointer to the back buffer surface
		result = g_Engine->GetDevice()->GetBackBuffer(0, 0, D3DBACKBUFFER_TYPE_MONO, &g_Engine->GetBackBuffer());
		if (result != D3D_OK)
		{
			debug << "\tUnable to get pointer to the backbuffer" << std::endl;
			return false;
		}

		// Create sprite object
		result = D3DXCreateSprite(g_Engine->GetDevice(), &g_Engine->GetSpriteObj());
		if (result != D3D_OK)
		{
			debug << "\tUnable to create spriteObj" << std::endl;
			return false;
		}

		/////////////////////
		// Set up matrices
		/////////////////////
		// Setup the projection matrix.
		int fieldOfView = (float)D3DX_PI / 4.0f;
		int screenAspect = (float)SCREENW / (float)SCREENH;

		// Create the projection matrix for 3D rendering
		D3DXMatrixPerspectiveFovLH(&_projMatrix, fieldOfView, screenAspect, screenNear, screenDepth);

		// Initialize the world matrix to identity
		D3DXMatrixIdentity(&_worldMatrix);

		// Create an orthographic projection matrix for 2D rendering
		D3DXMatrixOrthoLH(&_orthoMatrix, (float)SCREENW, (float)SCREENH, screenNear, screenDepth);

		return true;
	}


	void Direct3D::Shutdown()
	{
		///////////////////////////////
		// Currently, no buffers
		// or any other components
		// need to be handled here
		// since the device, context,
		// backbuffer and spriteObj
		// are handled in the g_Engine
		///////////////////////////////
		debug << "\tDirect3D shutting down..." << std::endl;

		
		debug << "\tDirect3D shutdown successfully" << std::endl;
	}


	//////////////////////
	// Utility functions
	//////////////////////

}