#ifndef COLLIDER_H
#define COLLIDER_H
#include "stdafx.h"

class Collider
{
private:
	long _prevWidth;		// Allow for temporary change in width
	long _prevHeight;		// Allow for temporary change in height
	RECT *_boundingBox;

public:
	Collider();
	~Collider();

	///////////////////////////////////////////
	// Create a bounding box around the object
	// with passed parameters
	///////////////////////////////////////////
	void Initialize(long xPosition, long yPosition, long width, long height);

	//////////////////////////////////////
	// General update allows box to move
	// with the object it is around
	//////////////////////////////////////
	void UpdateCollider(long xPosition, long yPosition);

	///////////////
	// Modifiers
	///////////////
	/*
		Note: Modifies original width/height values
		stored in _prevWidth / _prevHeight and not any
		previously modified value
	*/
	void ModifyWidth(float widthMultiplier);
	void ModifyHeight(float heightMultiplier);

	/*
		Resets box to original dimensions based
		off of the values in _prevWidth / _prevHeight
	*/
	void ResetBox();

	////////////////////////
	// Accessors / Mutators
	////////////////////////
	void SetBoxWidth(long width);
	void SetBoxHeight(long height);
	const RECT GetBoundingBox();
};


#endif