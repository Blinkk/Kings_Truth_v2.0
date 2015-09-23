#include "Collider.h"


Collider::Collider()
{
	_boundingBox = NULL;
}


Collider::~Collider()
{
	if (_boundingBox)
	{
		delete _boundingBox;
		_boundingBox = NULL;
	}
}


void Collider::Initialize(long xPosition, long yPosition, long width, long height)
{
	// Create a new rect if one does not already exist
	if (!_boundingBox)
		_boundingBox = new RECT();

	// Store width / height for later calculations
	_prevWidth = width;
	_prevHeight = height;

	// Set up box dimensions
	_boundingBox->left = xPosition;
	_boundingBox->right = _boundingBox->left + width;
	_boundingBox->top = yPosition;
	_boundingBox->bottom = _boundingBox->top + height;
}


void Collider::UpdateCollider(long xPosition, long yPosition)
{
	if (_boundingBox)
	{
		// Store current width in temp variables
		long tempWidth = _boundingBox->right - _boundingBox->left;
		long tempHeight = _boundingBox->bottom - _boundingBox->top;

		_boundingBox->left = xPosition;
		_boundingBox->right = _boundingBox->left + tempWidth;
		_boundingBox->top = yPosition;
		_boundingBox->bottom = _boundingBox->top + tempHeight;
	}
	else
		debug << "\tFailed to update bounding box, box not found." << std::endl;
}


///////////////
// Modifiers
///////////////
void Collider::ModifyWidth(float widthMultiplier)
{
	// If a box exists, modify its width based on multiplier
	if (_boundingBox)
		_boundingBox->right = _boundingBox->left + (_prevWidth * widthMultiplier);
	else
		debug << "\tFailed to update bounding box, box not found." << std::endl;
}


void Collider::ModifyHeight(float heightMultiplier)
{
	// If a box exists, modify its width based on multiplier
	if (_boundingBox)
		_boundingBox->bottom = _boundingBox->top + (_prevHeight * heightMultiplier);
	else
		debug << "\tFailed to update bounding box, box not found." << std::endl;
}


void Collider::ResetBox()
{
	if (_boundingBox)
	{
		// Set up box dimensions
		_boundingBox->right = _boundingBox->left + _prevWidth;
		_boundingBox->bottom = _boundingBox->top + _prevHeight;
	}
	else
		debug << "\tFailed to update bounding box, box not found." << std::endl;
}


////////////////////////
// Accessors / Mutators
////////////////////////
void Collider::SetBoxWidth(long width)
{
	if (_boundingBox)
	{
		_prevWidth = width;
		_boundingBox->right = _boundingBox->left + width;
	}
	else
		debug << "\tFailed to update bounding box, box not found." << std::endl;
}


void Collider::SetBoxHeight(long height)
{
	if (_boundingBox)
	{
		_prevHeight = height;
		_boundingBox->bottom = _boundingBox->top + height;
	}
	else
		debug << "\tFailed to update bounding box, box not found." << std::endl;
}


const RECT Collider::GetBoundingBox()
{
	// If a box exists, return a dereference version of it
	if (_boundingBox)
		return (*_boundingBox);

	// Otherwise, create an empty RECT and return that
	else
	{
		RECT emptyRect;
		emptyRect.left = 0;
		emptyRect.right = 0;
		emptyRect.top = 0;
		emptyRect.bottom = 0;

		return emptyRect;
	}
}
