//
//  MainActor.cpp
//  2D Game Programming Tutorial
//
//  Created by UglyMan.nothinglo on 13/10/7.
//  Copyright (c) 2013ๅนด UglyMan.nothinglo. All rights reserved.
//

#include "MainActor.h"

MainActor::MainActor(Vec3 pos, Vec3 key)
    : Actor(pos, key), isLeftDirection(false), nowPixmap(NULL)
{
    hitted = false;
    rotationParameter = 0;
}

void MainActor::display()
{
    RGBpixmapController controller;
    RGBpixmapController weaponController;
    static char walkBMPpath[]  = "image/hammer.bmp";
    nowPixmap = controller.getRGBpixmap(walkBMPpath, chromaKey);
    if(hitted)
    {
        if(rotationParameter > -90)
        {
            nowPixmap -> blendTexRotate(position.x, position.y,  1, 1,rotationParameter);
            rotationParameter-=6;
            speed.x=0;
        }
        else
        {
            rotationParameter =0;
            hitted = false;
        }

    }
    else
        nowPixmap -> blendTex(position.x, position.y, (isLeftDirection ? -1 : 1), 1);
}

void MainActor::action(unsigned long timeSincePrevFrame)
{
    if(speed.x != 0)
    {
        double resistanceAcceleration =
            (speed.y == 0 ? 6 : 3) * speed.x * speed.x * ((speed.x < 0) ? -1 : 1);
        double prevSpeed = speed.x;
        speed.x -= (resistanceAcceleration * timeSincePrevFrame/1000);
        if(fabs(speed.x) < 0.02) speed.x = 0;
        double displacementX = (prevSpeed + speed.x) * timeSincePrevFrame / 2;
        position.x += displacementX;
    }

}

void MainActor::changeStateByKeyboard(const KeyEventController & keyEC)
{
    if(nowPixmap == NULL) return;

    if(speed.y == 0)
    {
        int isKeyLeftDown = (keyEC.isSpecialKeyStateDown(GLUT_KEY_LEFT) ? -1 : 0);
        int isKeyRightDown = (keyEC.isSpecialKeyStateDown(GLUT_KEY_RIGHT) ? 1 : 0);
        int isKeySpaceHit = keyEC.isKeyStateDown(' ') ? 1:0;
        speed.x += (0.03 * (isKeyLeftDown + isKeyRightDown));
        if(isKeyLeftDown && !isLeftDirection)
        {
            position = Vec3(position.x + nowPixmap->nCols, position.y);
            isLeftDirection = true;
        }
        if(isKeyRightDown && isLeftDirection)
        {
            position = Vec3(position.x - nowPixmap->nCols, position.y);
            isLeftDirection = false;
        }
        if(speed.x != 0 &&
                !keyEC.isSpecialKeyStateDown(GLUT_KEY_LEFT) &&
                !keyEC.isSpecialKeyStateDown(GLUT_KEY_RIGHT))
        {
            speed.x -= (speed.x * 0.15);
        }
        if (isKeySpaceHit)
        {
            hitted = true;
        }

    }
}


