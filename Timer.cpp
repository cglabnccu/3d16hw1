//
//  Timer.cpp
//  2D Game Programming Tutorial
//
//  Created by UglyMan.nothinglo on 13/10/7.
//  Copyright (c) 2013¦~ UglyMan.nothinglo. All rights reserved.
//

#include "Timer.h"

Timer::Timer() : elapsedTime(0)
{
    startTime = prevTime = glutGet(GLUT_ELAPSED_TIME);
}
void Timer::reset()
{
    startTime = prevTime = glutGet(GLUT_ELAPSED_TIME);
}
void Timer::update()
{
    currentTime = glutGet(GLUT_ELAPSED_TIME);
    timeSincePrevFrame = currentTime - prevTime;
    elapsedTime = currentTime - startTime;
    prevTime = currentTime;
}
Timer::~Timer(){};
