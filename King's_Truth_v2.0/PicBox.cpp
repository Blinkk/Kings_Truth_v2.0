#include "Engine_Core.h"
#include "PicBox.h"

namespace Smoke
{
	PicBox::PicBox()
	{
		_width = 0;
		_height = 0;
		_active = false;
	}


	PicBox::~PicBox()
	{

	}


	void PicBox::Initialize(float width, float height, float offsetX,
		float offsetY, bool active, std::string textureToUse)
	{
		// Set object type
		_objectType = UI_OBJECT_TYPES::UI_PICBOX;

		// Set offset amount
		_offsetPosition = Vector2(offsetX, offsetY);

		// Set active flag
		_active = active;

		// Set dimensions
		if (width > 0)
			_width = width;
		if (height > 0)
			_height = height;

		// Initialize Renderer
		Renderer.Initialize(1.0f, 1.0f, _width, _height, 1, 0, 0, 0, 1,
			0.0f, _offsetPosition.x, _offsetPosition.y, textureToUse);

		if (!Renderer.HasTexture())
			debug << "\tPicBox could not load texture because texture was not found" << std::endl;

		// Set camera original position (scaling handled by size of text)
		if (g_Engine->GetActiveCamera() != NULL)
		{
			_cameraPrevPos = g_Engine->GetActiveCamera()->GetCurrentPos();

			// Determine scaling
			float scaleX = _width / Renderer.GetAdjustedWidth();
			float scaleY = _height / Renderer.GetAdjustedHeight();

			Renderer.SetScaleX(scaleX * g_Engine->GetActiveCamera()->GetZoomFactor());
			Renderer.SetScaleY(scaleY * g_Engine->GetActiveCamera()->GetZoomFactor());
		}
	}


	void PicBox::Update(float deltaTime)
	{

	}


	void PicBox::HandleEvent(IEvent* e)
	{

	}


	void PicBox::Render()
	{
		Vector2 currentCameraPos;
		Camera2D *pTemp = g_Engine->GetActiveCamera();
		currentCameraPos = pTemp->GetCurrentPos();

		// If the camera has moved, move UI_objects too
		if ((currentCameraPos.x - _cameraPrevPos.x != 0)
			|| (currentCameraPos.y - _cameraPrevPos.y != 0))
		{
			// Get the change in camera position
			Vector2 deltaPos = Vector2((currentCameraPos.x - _cameraPrevPos.x),
				(currentCameraPos.y - _cameraPrevPos.y));

			// Apply the change in camera position to the label
			Renderer.ModifyX(deltaPos.x);
			Renderer.ModifyY(deltaPos.y);

			// Reset previous camera position
			_cameraPrevPos = pTemp->GetCurrentPos();
		}

		// If a texture has been given to the Renderer, and the pic
		// box is active, render it to the screen
		if (Renderer.HasTexture() && this->IsActive())
			Renderer.Render();
		else
			debug << "\tFailed to render texture for PicBox, ID = " << this->ID << std::endl;
	}
}