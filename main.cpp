//
//  main.cpp
//  2D Game Programming Tutorial
//
//  Created by UglyMan.nothinglo on 13/10/7.
//  Copyright (c) 2013年 UglyMan.nothinglo. All rights reserved.
//



#ifdef __APPLE__
#include <GLUT/glut.h>
#pragma clang diagnostic ignored "-Wdeprecated-declarations"
#else
#include <windows.h>
//#include <GL/glew.h>
#include <GL/glut.h>
#endif

#include <vector>
#include "MainActor.h"
#include "KeyEventController.h"
#include "Timer.h"

const int GAME_ONE_SHOT_TIME = 33;

Actor* mainActor;
KeyEventController keyEC;
Timer timer;

int screenWidth = 800 , screenHeight = 600;

void myDisplay(void) {
    glClear(GL_COLOR_BUFFER_BIT);
        mainActor -> display();
    glutSwapBuffers();
}
void updateTheGame(int value) {
    static Timer timerForMainActor;
    timerForMainActor.update();
    if(timerForMainActor.elapsedTime > 1000 + rand() % 1000) {
        timerForMainActor.reset();
    }
        mainActor -> changeStateByKeyboard(keyEC);
    timer.update();
        mainActor -> action(timer.timeSincePrevFrame);
    glutPostRedisplay();
    glutTimerFunc(GAME_ONE_SHOT_TIME, updateTheGame, 0);
}
void loadActors() {
     mainActor = new MainActor(Vec3(), Vec3(232, 248, 248));


    /*string picPaths[] = {"image/stand.bmp", "image/walk.bmp", "image/fly.bmp"};
    vector<string> paths = vector<string>(picPaths,
                                          picPaths + sizeof(picPaths) / sizeof(string));
    RGBpixmapController().loadRGBpixmapAdvance(paths, Vec3(232, 248, 248));*/

}

void SpecialKeyUP(int key, int x, int y) {
    keyEC.setSpecialKeyStateUp(key);
}
void SpecialKeyDOWN(int key, int x, int y) {
    keyEC.setSpecialKeyStateDown(key);
}
void keyUP(unsigned char key, int x, int y) {
    keyEC.setKeyStateUp(key);
}
void keyDOWN(unsigned char key, int x, int y) {
    keyEC.setKeyStateDown(key);
}

void myReshape(int w, int h) {
    screenWidth  = w;
    screenHeight = h;
    glViewport(0, 0, screenWidth, screenHeight);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0, (GLfloat)screenWidth, 0.0, (GLfloat)screenHeight, -1.0, 1.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void init() {
    glutKeyboardUpFunc(keyUP);
    glutKeyboardFunc(keyDOWN);
    glutSpecialFunc(SpecialKeyDOWN);
    glutSpecialUpFunc(SpecialKeyUP);

    glutDisplayFunc(myDisplay);
    glutReshapeFunc(myReshape);
    glClearColor(1.0f, 1.0f, 0.0f, 0.0f);
}

int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(screenWidth, screenHeight);
    glutInitWindowPosition(50, 30);
    glutCreateWindow("Mock a Mole");
    init();

    loadActors();
    timer.reset();
    updateTheGame(0);
    glutMainLoop();
    return 0;
}

