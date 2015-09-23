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

    Timer::Timer(void)
    {
        Reset();
		_timer.restart();
    }

    Timer::~Timer(void) {}

    double Timer::GetElapsed()
    {
        double elapsed = _timer.elapsed() * 1000;
        return elapsed;
    }

    void Timer::Rest(double ms)
    {
        double start = GetElapsed();
        while (start + ms > GetElapsed()) 
        {
            Sleep(1);
        }
    }

    void Timer::Reset()
    {
        _stopwatchStart = GetElapsed();
    }

    bool Timer::Stopwatch(double ms)
    {
        if (GetElapsed() > _stopwatchStart + (double)ms) 
        {
            Reset();
            return true;
        }
        else return false;
    }

};
