#include "Label.h"
#include "Engine_Core.h"

namespace Smoke
{
	Label::Label()
	{
		// Set default values
		_text = "";
		_offsetPosition = Vector2(0, 0);
		if (g_Engine->GetActiveCamera())
			_cameraPrevPos = g_Engine->GetActiveCamera()->GetCurrentPos();
		else
			_cameraPrevPos = Vector2(0, 0);

		Renderer.SetX(0);
		Renderer.SetY(0);
	}


	Label::~Label()
	{
		// Nothing to release
	}


	void Label::Initialize(std::string fontName, int fontSize, 
		float offsetX, float offsetY, std::string text, 
		unsigned int textureID, D3DXCOLOR textColor)
	{
		// Set object type
		_objectType = UI_OBJECT_TYPES::UI_LABEL;

		// Create the font object
		_fontObject = Font(fontName, fontSize);

		// Set text parameters
		_text = text;
		_textColor = textColor;

		// Set offset amount
		_offsetPosition = Vector2(offsetX, offsetY);

		// Set dimensions
		float paddingX = 5.0f;
		float paddingY = paddingX * 0.75f;
		_width = _fontObject.getTextWidth(_text) + paddingX;
		_height = _fontObject.getTextHeight(_text) + paddingY;

		// Initialize Renderer
		switch (textureID)
		{
		case LABELTEXTURES::STANDARD_LABEL_TEXTURE:
			Renderer.Initialize(1.0f, 1.0f, _width, _height, 1, 0, 0, 0, 1,
				0.0f, _offsetPosition.x, _offsetPosition.y, "");
			break;

		default:
			debug << "\tLabel could not load texture because textureID out of range, reverted to default" << std::endl;
			break;
		}

		// Set camera original position (scaling handled by size of text)
		if (g_Engine->GetActiveCamera() != NULL)
			_cameraPrevPos = g_Engine->GetActiveCamera()->GetCurrentPos();
	}


	void Label::Update(float deltaTime)
	{

	}


	void Label::HandleEvent(IEvent *e)
	{

	}


	void Label::Render()
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

		// If a texture has been given to the Renderer, render it
		if (Renderer.HasTexture())
			Renderer.Render();

		// Calc text position
		float textX = (Renderer.GetPos().x + (_width / 2)) - (_fontObject.getTextWidth(_text) / 2);
		float textY = (Renderer.GetPos().y + (_height / 2)) - (_fontObject.getTextHeight(_text) / 2);

		// Print text to screen
		_fontObject.Print(textX, textY, _text, _textColor);
	}
}