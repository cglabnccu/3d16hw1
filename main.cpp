//
//  main.cpp
//  2D Game Programming Tutorial
//
//  Created by UglyMan.nothinglo on 13/10/7.
//  Copyright (c) 2013ๅนด UglyMan.nothinglo. All rights reserved.
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
#include "mole.h"

int GAME_ONE_SHOT_TIME = 33;

Actor* mainActor;
KeyEventController keyEC;
Timer timer;
Timer timerForMoles;
Moles* moles;
int score = 0;
unsigned long timeLimit = 61000;
int initialHeight = 100;


int screenWidth = 800, screenHeight = 600;

void myDisplay(void)
{
	int timeRemained = timer.elapsedTime>timeLimit?0:timeLimit-timer.elapsedTime;
    glClear(GL_COLOR_BUFFER_BIT);
    moles->display(timer.elapsedTime);
    mainActor -> display();
	glRectf(0,0,screenWidth,initialHeight);
    char scoreText[30];
    /*Print Scroe Text*/
    sprintf(scoreText, "Score %d", score);
    glColor3f(1.0, 0.0, 0.0);  //set font color
    glRasterPos2i(10, 550);    //set font start position
    for(int i=0; i<strlen(scoreText); i++)
    {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, scoreText[i]);
    }

    char timeText[50];
    /*Print Scroe Text*/
    sprintf(timeText, "time %d", timeRemained/1000);
    glColor3f(1.0, 0.0, 0.0);  //set font color
    glRasterPos2i(300, 550);    //set font start position
    for(int i=0; i<strlen(timeText); i++)
    {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, timeText[i]);
    }

    glutSwapBuffers();
}
void updateTheGame(int value)
{
    if(mainActor->position.x>screenWidth)
        mainActor->position.x -= screenWidth;
    else if(mainActor->position.x<0)
        mainActor->position.x += screenWidth;

    static Timer timerForMainActor;
    timerForMainActor.update();
    if(timerForMainActor.elapsedTime > 1000 + rand() % 1000)
    {
        timerForMainActor.reset();
    }
    mainActor -> changeStateByKeyboard(keyEC);
    timer.update();
	timerForMoles.update();
    mainActor -> action(timer.timeSincePrevFrame);
    glutPostRedisplay();
    glutTimerFunc(GAME_ONE_SHOT_TIME, updateTheGame, 0);
}

void SpecialKeyUP(int key, int x, int y)/*{{{*/
{
    keyEC.setSpecialKeyStateUp(key);
}
void SpecialKeyDOWN(int key, int x, int y)
{
    keyEC.setSpecialKeyStateDown(key);
}
void keyUP(unsigned char key, int x, int y)
{
    keyEC.setKeyStateUp(key);
}
void keyDOWN(unsigned char key, int x, int y)
{
    keyEC.setKeyStateDown(key);
}/*}}}*/

void myReshape(int w, int h)/*{{{*/
{
    screenWidth  = w;
    screenHeight = h;
    glViewport(0, 0, screenWidth, screenHeight);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0, (GLfloat)screenWidth, 0.0, (GLfloat)screenHeight, -1.0, 1.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}/*}}}*/

void init()
{
    glutKeyboardUpFunc(keyUP);
    glutKeyboardFunc(keyDOWN);
    glutSpecialFunc(SpecialKeyDOWN);
    glutSpecialUpFunc(SpecialKeyUP);
    glutDisplayFunc(myDisplay);
    glutReshapeFunc(myReshape);
    glClearColor(1.0f, 1.0f, 0.0f, 0.0f);
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(screenWidth, screenHeight);
    glutInitWindowPosition(50, 30);
    glutCreateWindow("Whack a Mole");
    init();
    srand(timer.currentTime);
    mainActor = new MainActor(Vec3(0,initialHeight,0), Vec3(255, 255, 255));
	moles = new Moles();
	timerForMoles.reset();


    timer.reset();
    updateTheGame(0);
    glutMainLoop();
    return 0;
}

