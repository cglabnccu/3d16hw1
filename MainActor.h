//
//  MainActor.h
//  2D Game Programming Tutorial
//
//  Created by UglyMan.nothinglo on 13/10/7.
//  Copyright (c) 2013¦~ UglyMan.nothinglo. All rights reserved.
//

#ifndef ___D_Game_Programming_Tutorial__MainActor__
#define ___D_Game_Programming_Tutorial__MainActor__

#include <iostream>
#include "Actor.h"
#include "RGBpixmapController.h"

class MainActor : public Actor
{
public :
    MainActor(Vec3 pos = Vec3(), Vec3 key = Vec3(-1, -1, -1));
    void display();
    void action(unsigned long timeSincePrevFrame = 0);
    void changeStateByKeyboard(const KeyEventController & keyEC);
    void hit();

    bool isLeftDirection;
    RGBApixmap * nowPixmap;
    RGBApixmap * weapon;
    Vec3 speed;
    float rotationParameter;
private:
    bool hitted;
    bool hammerBacked;

};

#endif /* defined(___D_Game_Programming_Tutorial__MainActor__) */
