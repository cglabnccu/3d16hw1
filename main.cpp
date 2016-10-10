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
#include <cmath>
#include "MainActor.h"
#include "KeyEventController.h"
#include "Timer.h"
#include "mole.h"



int GAME_ONE_SHOT_TIME = 20;

MainActor* mainActor;
KeyEventController keyEC;
Timer timer;
Moles* moles;
int score = 0;
unsigned long timeLimit = 61000;
int initialHeight = 100;



int screenWidth = 800, screenHeight = 600;
void gameOver(int i ){
       // glColor3f(0.0f, 1.0f, 0.0f);
	//glRectf(0, 0, screenWidth, screenHeight );
}
void myDisplay(void)
{
    unsigned long timeRemained = timer.elapsedTime>timeLimit?0:timeLimit-timer.elapsedTime;
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

        /*Print Scroe Text*/
        cout <<"ms Per Frame : " << timer.timeSincePrevFrame << "  | FPS : " <<1000.0/timer.timeSincePrevFrame<<endl;
     glutSwapBuffers();
}

bool AABBtest(float px, float py, float rx1, float ry1, float rx2, float ry2)
{
    return px >= rx1 && py >= ry1 && px <=rx2 && py<=ry2;
}

void getHowMuchScore( Moles* moles, const MainActor* mainActor)
{
#define PI 3.14159265
#define ACTORWIDTH  100
#define  ACTORHEIGHT  140
#define HAMMERHEIGHT 54
#define  _R1 52.49761899 //sqrt(pow(16,2)+pow(ACTORWIDTH/2,2) //
#define  _R2 86.02325267 //sqrt(pow(70,2)+pow(ACTORWIDTH/2,2) //
#define ANGLE1 1.261093382 //asin(50/_R1)
#define ANGLE2 0.620249486 //asin(50/_R2)
#define BASEX (mainActor->position.x+ACTORWIDTH/2)
#define BASEY (mainActor->position.y+70)
#define ROTATIONANGLE ((-1)*mainActor->rotationParameter*PI/180)

    for(int i =0; i< moles->member.size(); i++)
    {
        if(moles->member.at(i).hitted)
            continue;
        double newX1=BASEX+_R1*sin(ANGLE1+ROTATIONANGLE);
        double newY1=BASEY+_R1*cos(ANGLE1+ROTATIONANGLE);
        double newX2 = BASEX + _R1*sin(ANGLE1+ROTATIONANGLE);
        double newY2 = BASEY + _R1*cos(ANGLE1+ROTATIONANGLE);

        if(AABBtest(newX1, newY1,moles->member.at(i).position.x,moles->member.at(i).position.y,moles->member.at(i).position.x+70,moles->member.at(i).position.y+67)
                || AABBtest(newX2, newY2,moles->member.at(i).position.x,moles->member.at(i).position.y,moles->member.at(i).position.x+70,moles->member.at(i).position.y+67))
        {
            // cout <<"HAMMER | Angle : " <<(-1)*mainActor->rotationParameter << " |X,Y : (" <<newX << " , " << newY<< ")"<<endl;
            //   cout <<"MOLE : ( " <<moles->member.at(i).position.x+70<<" , " << moles->member.at(i).position.y +67<< " ) \n=====================================\n" ;

            score+=100;
            moles->member.at(i).hitted=true;
        }
    }

}
void updateTheGame(int value)
{   if(timer.elapsedTime>timeLimit)
gameOver(0);
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
    mainActor -> action(timer.timeSincePrevFrame);
    getHowMuchScore(moles,mainActor);
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
    mainActor = new MainActor(Vec3(0,initialHeight-15,0), Vec3(255, 255, 255));
    moles = new Moles();


    timer.reset();
    updateTheGame(0);
    glutMainLoop();
    return 0;
}

