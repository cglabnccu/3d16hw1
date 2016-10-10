//
//  Timer.h
//  2D Game Programming Tutorial
//
//  Created by UglyMan.nothinglo on 13/10/7.
//  Copyright (c) 2013¦~ UglyMan.nothinglo. All rights reserved.
//

#ifndef ___D_Game_Programming_Tutorial__Timer__
#define ___D_Game_Programming_Tutorial__Timer__

#include <iostream>
#ifdef __APPLE__
#include <GLUT/glut.h>
#pragma clang diagnostic ignored "-Wdeprecated-declarations"
#else
#include <windows.h>
//#include <GL/glew.h>
#include <GL/glut.h>
#endif

class Timer
{
public :
    unsigned long timeSincePrevFrame;
    unsigned long elapsedTime;
    unsigned long currentTime;
    unsigned long prevTime;
    unsigned long startTime;
    Timer();
    ~Timer();
    void reset();
    void update();
};

#endif /* defined(___D_Game_Programming_Tutorial__Timer__) */
