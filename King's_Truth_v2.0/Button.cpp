#include "Button.h"
#include "Engine_Core.h"

namespace Smoke
{
	Button::Button()
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


	Button::~Button()
	{
		
	}


	void Button::Initialize(std::string fontName, int fontSize,
		float offsetX, float offsetY, float bWidth, float bHeight, 
		std::string text, unsigned int buttonType, unsigned int textureID, D3DXCOLOR textColor)
	{
		// Set object type
		_objectType = UI_OBJECT_TYPES::UI_BUTTON;

		// Set button type
		_buttonType = buttonType;

		// Set offset amount
		_offsetPosition = Vector2(offsetX, offsetY);

		// Set dimensions
		_width = bWidth;
		_height = bHeight;

		// Set up the collider RECT
		_collider.top = 0;
		_collider.left = 0;
		_collider.right = _collider.left + bWidth;
		_collider.bottom = _collider.top + bHeight;

		// Create the font object
		_fontObject = Font(fontName, fontSize);

		// Set text parameters
		_text = text;
		_textColor = textColor;

		// Initialize Renderer
		switch (textureID)
		{
		case BUTTONTEXTURES::MENU_BUTTON_TEXTURE:
			Renderer.Initialize(1.0f, 1.0f, 200, 64.5f, 1, 0, 1, 0, 1, 0.0f,
				_offsetPosition.x, _offsetPosition.y, "menu_button.png");
			break;

		default:
			debug << "\tButton could not load texture because textureID out of range, reverted to default" << std::endl;
			break;
		}

		// Set camera original position and scaling factor for UI Objects
		if (g_Engine->GetActiveCamera() != NULL)
		{
			_cameraPrevPos = g_Engine->GetActiveCamera()->GetCurrentPos();

			// Determine scaling
			float scaleX = _width / Renderer.GetAdjustedWidth();
			float scaleY = _height / Renderer.GetAdjustedHeight();

			Renderer.SetScaleX(scaleX * g_Engine->GetActiveCamera()->GetZoomFactor());
			Renderer.SetScaleY(scaleY * g_Engine->GetActiveCamera()->GetZoomFactor());
		}

		// Register with event system
		g_Engine->GetEventManager()->RegisterListener(this, Events::CLICK_DOWN);
		g_Engine->GetEventManager()->RegisterListener(this, Events::CLICK_UP);
	}



	void Button::Update(float deltaTime)
	{
		// Update the collider
		UpdateCollider();
	}


	void Button::HandleEvent(IEvent *e)
	{
		if (e->Event_Type == Events::CLICK_DOWN)
		{
			ClickDownEvent *pTemp = static_cast<ClickDownEvent*>(e);

			// If cast was successful
			if (pTemp)
			{
				// If left mouse button was clicked
				if (pTemp->left)
				{
					// Check if mouse position was within the button collider
					if ((pTemp->mousePosX < Renderer.GetPos().x + _width
						&& pTemp->mousePosX > Renderer.GetPos().x)
						&& (pTemp->mousePosY < Renderer.GetPos().y + _height
						&& pTemp->mousePosY > Renderer.GetPos().y))
					{
						// Change button frame to show it has been clicked
						Renderer.SetCurrentFrame(1);
					}
				}
			}
			else
			{
				debug << "\tFailed to process CLICK_DOWN event" << std::endl;
				return;
			}
		}
		else if (e->Event_Type == Events::CLICK_UP)
		{
			ClickUpEvent *pTemp = static_cast<ClickUpEvent*>(e);

			// If cast was successful
			if (pTemp)
			{
				// If left mouse button was clicked
				if (pTemp->left)
				{
					// Check if mouse position was within the button collider
					if ((pTemp->mousePosX < Renderer.GetPos().x + _width
						&& pTemp->mousePosX > Renderer.GetPos().x)
						&& (pTemp->mousePosY < Renderer.GetPos().y + _height
						&& pTemp->mousePosY > Renderer.GetPos().y))
					{
						// Reset button frame to default
						Renderer.SetCurrentFrame(0);

						// Carry out an action....
						switch (_buttonType)
						{
						case BUTTONTYPES::START_BUTTON:
						{
							// Launch an event
							EndLevelEvent* pEvent = new EndLevelEvent();
							pEvent->newLevel = GAME_LEVELS::GAME_LEVEL_ONE;

							g_Engine->GetEventManager()->DispatchEvent(pEvent);
							break;
						}
							

						case BUTTONTYPES::EXIT_BUTTON:
						{
							 EndProgramEvent* pEvent = new EndProgramEvent();

							 g_Engine->GetEventManager()->DispatchEvent(pEvent);
							 break;
						}

						default:
							debug << "\tFailed to carry out action because buttonType is out of range" << std::endl;
							break;
						}
					}
					else
					{
						// Reset frame to default no matter what
						Renderer.SetCurrentFrame(0);	
					}
				}
			}
			else
			{
				debug << "\tFailed to process CLICK_UP event" << std::endl;
				return;
			}
		}
	}


	void Button::Render()
	{
		Vector2 currentCameraPos;
		Camera2D *pTemp = g_Engine->GetActiveCamera();
		currentCameraPos = pTemp->GetCurrentPos();

		// If the camera has moved, move UI_objects too
		if ((currentCameraPos.x - _cameraPrevPos.x != 0) || (currentCameraPos.y - _cameraPrevPos.y != 0))
		{
			// Get the change in camera position
			Vector2 deltaPos = Vector2((currentCameraPos.x - _cameraPrevPos.x), (currentCameraPos.y - _cameraPrevPos.y));

			// Apply the change in camera position to the label
			Renderer.ModifyX(deltaPos.x);
			Renderer.ModifyY(deltaPos.y);

			// Reset previous camera position
			_cameraPrevPos = pTemp->GetCurrentPos();
		}

		// If a texture has been given to the Renderer, render it
		if (Renderer.GetHasTextureFlag())
			Renderer.Render();

		// Calc text position
		float textX = (Renderer.GetPos().x + (_width / 2)) - (_fontObject.getTextWidth(_text) / 2);
		float textY = (Renderer.GetPos().y + (_height / 2)) - (_fontObject.getTextHeight(_text) / 2);

		// Print text to screen
		_fontObject.Print(textX, textY, _text, _textColor);
	}


	//////////////////////////////
	// Private collider functions
	//////////////////////////////
	void Button::UpdateCollider()
	{
		// Update collider position to match the location of the button
		_collider.top = Renderer.GetPos().y;
		_collider.left = Renderer.GetPos().x;
		_collider.right = _collider.left + _width;
		_collider.bottom = _collider.top + _height;
	}
}

