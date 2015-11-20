/**********************************
*  Programmer: Austin Ivicevic
*  DirectX 9 Game Engine
*  Date Created: 06/02/2015
***********************************/
#include "Engine_Core.h"
#include "GameManager.h"
#include <vector>
using namespace std;
using namespace Smoke;

LRESULT CALLBACK WndProc(HWND hwnd, UINT message,
	WPARAM wParam, LPARAM lParam);

#define APPTITLE "King's Truth"

// Declare engine object pointer and game manager pointer
auto_ptr<Engine_Core> g_Engine(new Engine_Core);
auto_ptr<GameManager> g_Manager(new GameManager);


int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE prevInstance,
	LPWSTR cmdLine, int cmdShow)
{
	UNREFERENCED_PARAMETER(prevInstance);
	UNREFERENCED_PARAMETER(cmdLine); 

	////////////////////////////////////////
	// Create the window
	////////////////////////////////////////
	WNDCLASSEX wndClass = { 0 };
	wndClass.cbSize = sizeof(WNDCLASSEX);
	wndClass.style = CS_HREDRAW | CS_VREDRAW;
	wndClass.lpfnWndProc = WndProc;
	wndClass.hInstance = hInstance;
	wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndClass.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wndClass.lpszMenuName = NULL;
	wndClass.lpszClassName = APPTITLE;
	if (!RegisterClassEx(&wndClass))
	{
		debug << "\tFailed to register window class" << std::endl;
		return false;
	}

	RECT rc = { 0, 0, SCREENW, SCREENH };
	AdjustWindowRect(&rc, WS_OVERLAPPEDWINDOW, FALSE);

	g_Engine->GetWindowHandle() = CreateWindowA(APPTITLE, APPTITLE, WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT, rc.right - rc.left, rc.bottom - rc.top,
		NULL, NULL, hInstance, NULL);
	if (!g_Engine->GetWindowHandle())
	{
		debug << "\tFailed to create window" << std::endl;
		return false;
	}

	// Center the window
	GetWindowRect(g_Engine->GetWindowHandle(), &rc);
	int xPos = (GetSystemMetrics(SM_CXSCREEN) - rc.right) / 2;
	int yPos = (GetSystemMetrics(SM_CYSCREEN) - rc.bottom) / 2;

	SetWindowPos(g_Engine->GetWindowHandle(), 0, xPos, yPos, 0, 0, SWP_NOZORDER | SWP_NOSIZE);

	// Show Window
	ShowWindow(g_Engine->GetWindowHandle(), SW_SHOW);
	ShowCursor(true);

	/////////////////////
	// Initialize engine
	/////////////////////
	if (!g_Engine->Initialize(hInstance, false))	
	{
		debug << "Failed to initialize engine!" << std::endl;
		return -1;
	}

	/////////////////////
	// Initialize Game
	/////////////////////
	if (!g_Manager->Game_Init())
	{
		debug << "Failed to initialize game!" << std::endl;
		return -1;
	}

	double prevTime = g_Engine->GetGameTime();

	
	//////////////////////////////
	// Main Game Loop
	//////////////////////////////
	MSG msg = { 0 };
	while (!g_Manager->endProgram)
	{
		g_Engine->GetUIManager()->PurgeUIObjects();
		g_Manager->PurgeGameObjects();		// Remove all current game object
		g_Manager->LoadLevel();				// Load a new level ((*lvlPtr)())

		/////////////////////////////
		// Single Level Loop
		/////////////////////////////
		while (!g_Manager->gameOver)
		{
			if (PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}

			// Update if frame interval is ready (default: 60-70fps)
			double t = g_Engine->GetGameTime();
			if (t >= prevTime + ((float)1 / g_Manager->GetFrameInterval()) * 1000.0f)
			{
				float dt = (float)(t - prevTime) * 0.001f;	// Calculate deltaTime (time between frames)
				g_Manager->Update(dt);						// Update game (calls Engine_Core::Update())
				prevTime = t;								// Reset prevTime
			}

			g_Manager->Game_Render();				// Render game (Renders EVERYTHING in one scene)
			g_Engine->GetEventManager()->Update();	// Handle events
		}

		// Release level objects
		g_Manager->UnloadLevel();
	}
	
	// Release game objects
	g_Manager->Game_End();
	g_Engine->Shutdown();		// Shutdown engine cores

	return static_cast<int>(msg.wParam);
}


LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT paintStruct;
	HDC hDC;

	switch (message)
	{
	case WM_PAINT:
		hDC = BeginPaint(hwnd, &paintStruct);
		EndPaint(hwnd, &paintStruct);
		break;

	// When the 'X' is pressed, close game regardless of 
	// gameOver status (this can be changed later)
	case WM_CLOSE:
		if (!g_Manager->gameOver) g_Manager->gameOver = true;
		g_Manager->endProgram = true;
		break;

	default:
		return DefWindowProc(hwnd, message, wParam, lParam);
	}

	return 0;
}