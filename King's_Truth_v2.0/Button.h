#ifndef BUTTON_H
#define BUTTON_H
#include "Font.h"
#include "IUI_Object.h"
#include <string>

enum BUTTONTEXTURES
{
	MENU_BUTTON_TEXTURE = 0
};

enum BUTTONTYPES
{
	START_BUTTON = 0,
	EXIT_BUTTON,
	MENU_BUTTON
};

namespace Smoke
{
	class Button : public IUI_Object
	{
	private:
		Font _fontObject;			// Font object to show text on button
		std::string _text;			// Text to display on button
		D3DXCOLOR _textColor;		// Color of button text
		unsigned int _buttonType;	// Type of button

		// Dimensions
		float _width;
		float _height;

		/*
			This RECT will act as the collider for each button
			and be used to check against mouse position to determine
			whether or not the button should be activated on click.
		*/
		RECT _collider;

		/*
			Private functions to manipulate/update collider internally

			Note: These functions just serve to disallow access to modify
			the collider from any outside source.
		*/
		void UpdateCollider();

	public:
		Button();
		~Button();

		////////////////////////
		// Overridden functions
		////////////////////////
		void Update(float deltaTime) override;
		void HandleEvent(IEvent* e) override;
		void Render() override;

		////////////////////////
		// Unique functions
		////////////////////////
		/*
			UI Objects are placed by default in the center of the camera view
			and must be "offset" in order to place them in specific positions.
			Determine how far from the center you want the element to be and pass
			in those values for the offsetX and offsetY.
		*/
		void Initialize(std::string fontName, int fontSize,
			float offsetX, float offsetY,float bWidth, float bHeight,
			std::string text, unsigned int buttonType, unsigned int textureID = 0, D3DXCOLOR textColor = D3DCOLOR_XRGB(255,255,255));

	};
}

#endif