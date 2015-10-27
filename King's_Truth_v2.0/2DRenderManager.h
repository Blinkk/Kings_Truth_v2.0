#ifndef TWODRENDERMANAGER_H
#define TWODRENDERMANAGER_H
#pragma warning (disable : 4244)
#include "Vector.h"

///////////////////////////////////////
// Handles all animation and rendering
// for entities and renderable objects
///////////////////////////////////////

namespace Smoke
{
	class TwoDRenderManager
	{
	private:
		bool _animate;
		Vector2 _posVector;
		LPDIRECT3DTEXTURE9 _texture;
		float _scaleX;
		float _scaleY;
		unsigned int _frameW;
		unsigned int _frameH;
		unsigned int _numCol;
		unsigned int _curFrame;
		unsigned int _startFrame;
		unsigned int _endFrame;
		unsigned int _delay;
		unsigned int _ST;
		int _direction;
		float _rotation;

		///////////////////////////////////
		// Increment frame when flag is
		// set to true. Loop around when
		// animation is finished
		// Called in Update();
		///////////////////////////////////
		void Animate();

	public:
		TwoDRenderManager();

		~TwoDRenderManager();

		///////////////////////////////
		// Overloaded init function
		// to change animation set
		// within the same spritesheet
		///////////////////////////////
		void Initialize(unsigned int newFrameWidth, unsigned int newFrameHeight,
			unsigned int newStartFrame, unsigned int newEndFrame, unsigned int newDelay);

		////////////////////////////////
		// Initialize all variables
		// needed to handled animations
		// and transformations of the
		// renderable object.
		////////////////////////////////
		void Initialize(float scaleX, float scaleY, unsigned int frameWidth,
			unsigned int frameHeight, unsigned int numCol,
			unsigned int startFrame, unsigned int endFrame,
			unsigned int delay, int animDirection,
			float rotationInRadians, float newX, float newY,
			std::string textureToUse);

		////////////////////////
		// Animate if necessary
		////////////////////////
		void Update();

		//////////////////////////////
		// Create a transform matrix
		// and render to screen.
		//////////////////////////////
		void Render();


		//////////////////////////
		// Accessor / Mutators
		//////////////////////////
		Vector2 GetPos() { return _posVector; }
		const float GetAdjustedWidth() { return _frameW * _scaleX; }
		const float GetAdjustedHeight() { return _frameH * _scaleY; }
		const unsigned int GetCurrentFrame() { return _curFrame; }
		const unsigned int GetEndFrame() { return _endFrame; }
		const float GetRotation() { return _rotation; }		
		const float GetScaleX() { return _scaleX; }
		const float GetScaleY() { return _scaleY; }
		const RECT GetBoundingBox();
		
		void SetX(float value) { _posVector.x = value; }
		void SetY(float value) { _posVector.y = value; }
		void SetScaleX(float value) { _scaleX = value; }
		void SetScaleY(float value) { _scaleY = value; }
		void SetStartFrame(unsigned int value) { _startFrame = value; }
		void SetEndFrame(unsigned int value) { _endFrame = value; }
		void SetFrameWidth(float value) { _frameW = value; }
		void SetFrameHeight(float value) { _frameH = value; }
		void SetDelay(unsigned int value) { _delay = value; }
		void SetAnimateFlag(bool value) { _animate = value; }
		void SetCurrentFrame(unsigned int value) { _curFrame = value; }
		void SetRot(int value) { _rotation = value; }	// In radians	

		///////////////////////////
		// Modifier Functions
		///////////////////////////
		void ModifyX(float deltaX);
		void ModifyY(float deltaY);
		void ModifyScaleX(float deltaSX);
		void ModifyScaleY(float deltaSY);
		void ModifyRotation(float deltaRot);			// In radians

		//////////////////////////////
		// Load new texture, but does
		// not update any other info
		// for the renderer
		//////////////////////////////
		void SetNewTexture(std::string);
	};
}

#endif
