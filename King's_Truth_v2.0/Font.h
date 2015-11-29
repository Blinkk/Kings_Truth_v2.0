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

#pragma once

#include "stdafx.h"

namespace Smoke 
{
    class Font 
	{
    private:
        LPD3DXFONT fontObj;

    public:
		Font();
        Font(std::string name, int size);
		~Font();
        void Print(int x, int y, std::string text, D3DCOLOR color);
        int getTextWidth(std::string text);
        int getTextHeight(std::string text);

    };

};


