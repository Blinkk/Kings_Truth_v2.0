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
#ifndef TIMER_H
#define TIMER_H

#include "stdafx.h"

namespace Smoke 
{
    class Timer 
    {
    private: 
        boost::timer _timer;
        double _timerStart;
        double _stopwatchStart;

    public:
        Timer(void);
        ~Timer(void);
        double GetElapsed();		// Return elapsed time in milliseconds
        void Rest(double ms);
        void Reset(); 
        bool Stopwatch(double ms);
    };
};

#endif
