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
#ifndef VECTOR_H
#define VECTOR_H
#include "stdafx.h"

namespace Smoke
{
	class Vector2
	{
	public:
		double x, y;

		virtual ~Vector2() {}
		Vector2();
		Vector2(const Vector2& V);
		Vector2(double x, double y);
		Vector2(int x, int y);
		Vector2(const D3DXVECTOR2& dv);
		Vector2(const D3DXVECTOR3& dv);

		///////////////////////////
		// Manipulation functions
		///////////////////////////
		void Set(double x1, double y1);
		void Set(const Vector2& V);
		double GetX() { return x; }
		void SetX(double value) { x = value; }
		double GetY() { return y; }
		void SetY(double value) { y = value; }
		void Move(double mx, double my);

		////////////////////////
		// Operator definitions
		////////////////////////
		Vector2& operator=(const Vector2& V);
		void operator+=(const Vector2& V);
		void operator-=(const Vector2& V);
		void operator*=(const Vector2& V);
		void operator/=(const Vector2& V);
		Vector2 operator/(const double& d);
		bool operator==(const Vector2& V) const;
		bool operator!=(const Vector2& V) const;

		////////////////////////
		// Conversion functions
		////////////////////////
		D3DXVECTOR3 ToD3DXVECTOR3();
		D3DXVECTOR2 ToD3DXVECTOR2();
	};
}

#endif