//
//  Actor.h
//  2D Game Programming Tutorial
//
//  Created by UglyMan.nothinglo on 13/10/7.
//  Copyright (c) 2013¦~ UglyMan.nothinglo. All rights reserved.
//

#ifndef ___D_Game_Programming_Tutorial__Actor__
#define ___D_Game_Programming_Tutorial__Actor__

#include <iostream>
#include "Vec3.h"
#include "KeyEventController.h"

class Actor {
    public :
    Actor(Vec3 pos = Vec3(), Vec3 key = Vec3(-1, -1, -1));
    Vec3 position;
    Vec3 chromaKey;
    virtual void display() = 0;
    virtual void action(unsigned long timeSincePrevFrame = 0) = 0;
    virtual void changeStateByKeyboard(const KeyEventController & keyEC) = 0;
};

#endif /* defined(___D_Game_Programming_Tutorial__Actor__) */
