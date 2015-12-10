#include "Engine_Core.h"
#include "2DRenderManager.h"

namespace Smoke
{
	TwoDRenderManager::TwoDRenderManager()
	{
		// Default values
		_scaleX = 1.0f;
		_scaleY = 1.0f;
		_frameW = 100.0f;
		_frameH = 100.0f;
		_numCol = 1;
		_curFrame = 0;
		_startFrame = 0;
		_endFrame = 0;
		_delay = 0;
		_ST = g_Engine->GetGameTime();
		_direction = 1;
		_rotation = 0;
		_animate = false;
		_hasTexture = false;
	}

	
	TwoDRenderManager::~TwoDRenderManager() {}


	///////////////////////////////
	// Initialize all values for
	// animation and transformation
	///////////////////////////////
	void TwoDRenderManager::Initialize(float scaleX, float scaleY, unsigned int frameWidth,
		unsigned int frameHeight, unsigned int numCol, unsigned int startFrame, unsigned int endFrame,
		unsigned int delay, int animDirection, float rotationInRadians, float newX, float newY,	std::string textureToUse)
	{
		_scaleX = scaleX;
		_scaleY = scaleY;
		_frameW = frameWidth;
		_frameH = frameHeight;
		_numCol = numCol;
		_startFrame = startFrame;
		_endFrame = endFrame;
		_delay = delay;
		_direction = animDirection;
		_rotation = rotationInRadians;
		_ST = g_Engine->GetGameTime();
		
		_posVector.x = newX;
		_posVector.y = newY;

		// Get the texture from the texture manager
		if (textureToUse != "")
			_texture = g_Engine->GetTextureManager()->RetrieveTexture(textureToUse);

		_curFrame = _startFrame;	// Set current frame to the start frame

		if (_texture != nullptr)
			_hasTexture = true;
	}


	///////////////////////////////
	// Set new animation variables
	///////////////////////////////
	void TwoDRenderManager::Initialize(unsigned int newFrameWidth, unsigned int newFrameHeight,
		unsigned int newStartFrame, unsigned int newEndFrame, unsigned int newDelay)
	{
		_frameW = newFrameWidth;
		_frameH = newFrameHeight;
		_startFrame = newStartFrame;
		_endFrame = newEndFrame;
		_delay = newDelay;
	}


	void TwoDRenderManager::Update()
	{
		// If animate flag is true, increment frame
		if (_animate)
			Animate();
	}


	void TwoDRenderManager::Render()
	{
		// Set matrix vectors
		Vector2 scale(_scaleX, _scaleY);
		Vector2 center((float)(_frameW * _scaleX) / 2.0f, (float)(_frameH * _scaleY) / 2.0f);
		Vector2 translation(_posVector.x, _posVector.y);

		// Create the matrix
		D3DXMATRIX transform;
		D3DXMatrixTransformation2D(&transform, nullptr, 0, &scale.ToD3DXVECTOR2(),
			&center.ToD3DXVECTOR2(), _rotation, &translation.ToD3DXVECTOR2());

		// Set our transform matrix
		g_Engine->GetSpriteObj()->SetTransform(&transform);

		// Get a RECT for current frame
		RECT rect;
		rect.left = (_curFrame % _numCol) * _frameW;
		rect.right = rect.left + _frameW;
		rect.top = (_curFrame / _numCol) * _frameH;
		rect.bottom = rect.top + _frameH;

		// Draw to screen
		g_Engine->GetSpriteObj()->Draw(_texture, &rect, nullptr, nullptr, D3DCOLOR_XRGB(255, 255, 255));

		// Reset transform to identity matrix
		D3DXMATRIX mat;
		D3DXMatrixIdentity(&mat);
		g_Engine->GetSpriteObj()->SetTransform(&mat);
	}


	void TwoDRenderManager::Animate()
	{
		// Check if delay requirement is met
		if ((int)g_Engine->GetGameTime() > (_ST + _delay))
		{
			// Reset starttime
			_ST = g_Engine->GetGameTime();

			// Increment current frame
			_curFrame += _direction;

			// If end of animation, reset
			if (_curFrame > _endFrame)
				_curFrame = _startFrame;

			if (_curFrame < _startFrame)
				_curFrame = _startFrame;
		}
	}


	//////////////////////////
	// Complex Get() / Set()
	//////////////////////////
	const RECT TwoDRenderManager::GetBoundingBox()
	{
		RECT boundingBox;

		boundingBox.left = _posVector.x;
		boundingBox.right = _posVector.x + GetAdjustedWidth();
		boundingBox.top = _posVector.y;
		boundingBox.bottom = _posVector.y + GetAdjustedHeight();

		return boundingBox;
	}


	void TwoDRenderManager::SetNewTexture(std::string newTexture)
	{
		_texture = g_Engine->GetTextureManager()->RetrieveTexture(newTexture);

		// Set the init flag to true if texture is not nullptr
		if (_texture != nullptr)
			_hasTexture = true;
		else
			_hasTexture = false;
	}

	////////////////
	// Modifiers
	////////////////
	void TwoDRenderManager::ModifyX(float deltaX)
	{
		_posVector.x += (deltaX);
	}


	void TwoDRenderManager::ModifyY(float deltaY)
	{
		_posVector.y += (deltaY);
	}


	void TwoDRenderManager::ModifyScaleX(float deltaSX)
	{
		_scaleX += deltaSX;
	}


	void TwoDRenderManager::ModifyScaleY(float deltaSY)
	{
		_scaleY += deltaSY;
	}


	void TwoDRenderManager::ModifyRotation(float deltaRot)
	{
		_rotation += deltaRot;
	}
}