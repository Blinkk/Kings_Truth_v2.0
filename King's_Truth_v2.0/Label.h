#ifndef LABEL_H
#define LABEL_H
#include "Font.h"
#include "IUI_Object.h"
#include <string>

enum LABELTEXTURES
{
	STANDARD_LABEL_TEXTURE = 0,
};

namespace Smoke
{
	class Label : public IUI_Object
	{
	private:
		Font _fontObject;				// Main font object for label
		std::string _text;				// Text of label
		D3DXCOLOR _textColor;			// Color of label text

		// Dimensions
		float _width;
		float _height;

	public:
		Label();
		~Label();

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
			float offsetX, float offsetY, std::string text, 
			unsigned int textureID = 0, D3DXCOLOR textColor = D3DCOLOR_XRGB(255, 255, 255), std::string tagToUse = "");
	};
}

#endif