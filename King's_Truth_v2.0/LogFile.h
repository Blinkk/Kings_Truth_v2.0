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
#include <fstream>
#include <string>

namespace Smoke 
{
    class LogFile 
    {
    public:
        LogFile();
        ~LogFile();
        void Print(std::string s);
        void Print(char c[]);
        std::ofstream& operator<<(char c[]);
        std::ofstream& operator<<(std::string s);
        std::ofstream& operator<<(double d);
        std::ofstream& operator<<(float f);
        std::ofstream& operator<<(int i);
        std::ofstream& operator<<(bool b);
    };
};

static Smoke::LogFile debug;
