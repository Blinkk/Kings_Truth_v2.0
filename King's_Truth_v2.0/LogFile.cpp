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
#include "LogFile.h"

std::ofstream out("debug.txt");

namespace Smoke 
{
    LogFile::LogFile() {}
    LogFile::~LogFile()
    {
        if (out.good()) out.close();
    }
    void LogFile::Print(std::string s)
    {
        out << s << std::endl;
    }
    void LogFile::Print(char c[])
    {
		out << c << std::endl;
    }
    std::ofstream& LogFile::operator<<(char c[])
    {
        out << c;
        return out;
    }
	std::ofstream& LogFile::operator<<(std::string s)
    {
        out << s;
        return out;
    }
    std::ofstream& LogFile::operator<<(double d)
    {
        out << d;
        return out;
    }
    std::ofstream& LogFile::operator<<(float f)
    {
        out << f;
        return out;
    }
    std::ofstream& LogFile::operator<<(int i)
    {
        out << i; 
        return out;
    }
    std::ofstream& LogFile::operator<<(bool b)
    {
        if (b) out << "True";
        else out << "False";
        return out;
    }
};
