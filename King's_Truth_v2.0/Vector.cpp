/**********************************
*  Programmer: Austin Ivicevic
*  DirectX 9 Game Engine
*  Date Created: 06/02/2015
***********************************/
/** Note: This class is closely modeled
	after the book code from...
		Multi-Threaded Game Engine Design
		Copyright 2010 by Jonathan Harbour
**/
#include "Engine_Core.h"

namespace Smoke
{
	// Create a new default (0,0) vector
	Vector2::Vector2()
	{
		x = y = 0;
	}

	// Create a copy of another Vector2
	Vector2::Vector2(const Vector2& V)
	{
		*this = V;
	}

	// Create a vector with specified position (double)
	Vector2::Vector2(double x, double y)
	{
		Set(x, y);
	}

	// Create a vector with specified position (int)
	Vector2::Vector2(int x, int y)
	{
		Set((double)x, (double)y);
	}

	// Create a copy of a D3DXVECTOR2 as a Vector2
	Vector2::Vector2(const D3DXVECTOR2& dv)
	{
		x = dv.x; y = dv.y;
	}


	///////////////////////////
	// Manipulation functions
	///////////////////////////
	void Vector2::Set(double x1, double y1)
	{
		x = x1; y = y1;
	}

	void Vector2::Set(const Vector2& V)
	{
		x = V.x; y = V.y;
	}

	void Vector2::Move(double mx, double my)
	{
		x += mx; y += my;
	}


	////////////////////////
	// Operator definitions
	////////////////////////
	// Set another Vector2 equal to *this
	Vector2& Vector2::operator=(const Vector2& V)
	{
		Set(V);
		return *this;
	}

	// Add another Vector2 to *this
	void Vector2::operator+=(const Vector2& V)
	{
		x += V.x; y += V.y;
	}

	// Subtract another Vector2 from *this
	void Vector2::operator-=(const Vector2& V)
	{
		x -= V.x; y -= V.y;
	}

	// Multiply another Vector2 by *this
	void Vector2::operator*=(const Vector2& V)
	{
		x *= V.x; y *= V.y;
	}

	// Divide another Vector2 by *this
	void Vector2::operator/=(const Vector2& V)
	{
		x /= V.x; y /= V.y;
	}

	// Divide two Vector2's by each other
	Vector2 Vector2::operator/(const double& d)
	{
		Vector2 v(x / d, y / d);
		return v;
	}

	// Equality operator comparison includes double rounding
	bool Vector2::operator==(const Vector2& V) const
	{
		return (
			(((V.x - 0.0001f) < x) && (x < (V.x + 0.0001f))) &&
			(((V.y - 0.0001f) < y) && (y < (V.y + 0.0001f))));
	}

	// Inequality operator
	bool Vector2::operator!=(const Vector2& V) const
	{
		return (!(*this == V));
	}


	////////////////////////
	// Conversion functions
	////////////////////////
	D3DXVECTOR3 Vector2::ToD3DXVECTOR3()
	{
		return D3DXVECTOR3((float)x, (float)y, 0.0f);
	}

	D3DXVECTOR2 Vector2::ToD3DXVECTOR2()
	{
		return D3DXVECTOR2((float)x, (float)y);
	}
}