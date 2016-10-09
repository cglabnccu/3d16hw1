//
//  MainActor.cpp
//  2D Game Programming Tutorial
//
//  Created by UglyMan.nothinglo on 13/10/7.
//  Copyright (c) 2013ๅนด UglyMan.nothinglo. All rights reserved.
//

#include "MainActor.h"

MainActor::MainActor(Vec3 pos, Vec3 key)
    : Actor(pos, key), isLeftDirection(false), nowPixmap(NULL) {
}

void MainActor::display() {
    RGBpixmapController controller;
    RGBpixmapController weaponController;
    static char standBMPpath[] = "image/hammer.bmp";
    static char walkBMPpath[]  = "image/hammer.bmp";
    static char flyBMPpath[]   = "image/fly.bmp";
	static char weaponPath[] = "image/sun1.bmp";
    if(speed.x != 0) {
        if(controller.isPixmapMatchPath(nowPixmap, standBMPpath)) {
            nowPixmap = controller.getRGBpixmap(walkBMPpath, chromaKey);
        } else {
            nowPixmap = controller.getRGBpixmap(standBMPpath, chromaKey);
        }
    } else {
        nowPixmap = controller.getRGBpixmap(standBMPpath, chromaKey);
    }
	/*
     *if(speed.y != 0) {
     *    nowPixmap = controller.getRGBpixmap(flyBMPpath, chromaKey);
     *}
	 */
    nowPixmap -> blendTex(position.x, position.y, (isLeftDirection ? -1 : 1), 1);
}

void MainActor::action(unsigned long timeSincePrevFrame) {
    if(speed.x != 0) {
        double resistanceAcceleration =
            (speed.y == 0 ? 6 : 3) * speed.x * speed.x * ((speed.x < 0) ? -1 : 1);
        double prevSpeed = speed.x;
        speed.x -= (resistanceAcceleration * timeSincePrevFrame/1000);
        if(fabs(speed.x) < 0.02) speed.x = 0;
        double displacementX = (prevSpeed + speed.x) * timeSincePrevFrame / 2;
        position.x += displacementX;
    }
	/*
     *if(speed.y != 0) {
     *    static double gravityAcceleration = 2;
     *    double prevSpeed = speed.y;
     *    speed.y -= (gravityAcceleration * timeSincePrevFrame/1000);
     *    double displacementY = (prevSpeed + speed.y) * timeSincePrevFrame / 2;
     *    position.y += displacementY;
     *    if(position.y < 0) {
     *        position.y = speed.y = 0;
     *    }
     *}
	 */
}

void MainActor::changeStateByKeyboard(const KeyEventController & keyEC) {
    if(nowPixmap == NULL) return;
	/*
     *if(keyEC.isSpecialKeyStateDown(GLUT_KEY_UP) && position.y == 0) {
     *    speed.y = 1;
     *}
	 */
    if(speed.y == 0) {
        int isKeyLeftDown = (keyEC.isSpecialKeyStateDown(GLUT_KEY_LEFT) ? -1 : 0);
        int isKeyRightDown = (keyEC.isSpecialKeyStateDown(GLUT_KEY_RIGHT) ? 1 : 0);
		int isKeySpaceHit = keyEC.isKeyStateDown(' ') ? 1:0;
        speed.x += (0.03 * (isKeyLeftDown + isKeyRightDown));
        if(isKeyLeftDown && !isLeftDirection) {
            position = Vec3(position.x + nowPixmap->nCols, position.y);
            isLeftDirection = true;
        }
        if(isKeyRightDown && isLeftDirection) {
            position = Vec3(position.x - nowPixmap->nCols, position.y);
            isLeftDirection = false;
        }
        if(speed.x != 0 &&
           !keyEC.isSpecialKeyStateDown(GLUT_KEY_LEFT) &&
           !keyEC.isSpecialKeyStateDown(GLUT_KEY_RIGHT)) {
            speed.x -= (speed.x * 0.15);
        }
		if (isKeySpaceHit) {
			hit();
		}

    }
}

void MainActor::hit(){

}
