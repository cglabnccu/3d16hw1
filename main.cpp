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
#include <string>
#include "MainActor.h"
#include "KeyEventController.h"
#include "timer.h"
#include "mole.h"



int GAME_ONE_SHOT_TIME = 20;

MainActor* mainActor;
KeyEventController keyEC;
RGBpixmapController controller;
RGBApixmap* text;
Vec3 chromaKey(255,255,255);
Timer timer;
Moles* moles;
int score ;
unsigned long timeLimit = 61000;
int initialHeight = 100;
bool isGameOver = false;
int screenWidth = 800, screenHeight = 600;
float fgColor[3]= {248.0/255,219.0/255,14.0/255};
float bgColor[4]= {11.0/255,251.0/255,251.0/255,1.0};


void updateTheGame(int value);
void reset();

void printMyNumberFont(char* numbers, int x, int y, float scale){
    char numberFont[20]  ;
    RGBApixmap* numbersPic[10];
    int i=0;
    for(i; i<10; i++)
    {
        sprintf(numberFont,"image/Fonts/%d.bmp",i);
        numbersPic[i] = controller.getRGBpixmap(numberFont,chromaKey);
    }
    i = 0;
    while(numbers[i] != '\0')
    {
        numbersPic[numbers[i]-48]->blendTex(x+scale*67.0*i, y,scale,scale);
        i++;
    }
}

void gameOver( int u =0)
{
    isGameOver = true;
    char scoreText[10];
    sprintf(scoreText,"%d",score);
    glColor3f(0.0f, 1.0f, 0.0f);//background
    glRectf(0, 0, screenWidth, screenHeight );



    /*Print GameOver*/

    text = controller.getRGBpixmap("image/Fonts/go.bmp",chromaKey);
    text->blendTex(168, 255,1,1); //GMAEOVER
    text = controller.getRGBpixmap("image/Fonts/score.bmp",chromaKey);
    text->blendTex(168+30, 255+130,1,1); //SCORE :
    text = controller.getRGBpixmap("image/Fonts/restart.bmp",chromaKey);
    text->blendTex(168+20, 255-100,1,1);//Press R to restart

    printMyNumberFont(scoreText,168+30+180, 255+130,0.6);

    glutSwapBuffers();

    /*Restart*/
    if(keyEC.isKeyStateDown('r'))
    {
        score = 0;
        delete mainActor;
        delete moles;
        mainActor = new MainActor(Vec3(0,initialHeight-15,0), Vec3(255, 255, 255));
        moles = new Moles();
        reset();
        updateTheGame(0);
        return;
    }
    glutTimerFunc(10,gameOver, 0);

}

void myDisplay(void)
{
    unsigned long timeRemained = timer.elapsedTime>timeLimit?0:timeLimit-timer.elapsedTime;
    glClear(GL_COLOR_BUFFER_BIT);
    moles->display(timer.elapsedTime);
    mainActor -> display();
    glColor3f(fgColor[0],fgColor[1],fgColor[2]);
    glRectf(0,0,screenWidth,initialHeight);

    /*Print Score */
    text = controller.getRGBpixmap("image/Fonts/score.bmp",chromaKey);
    text->blendTex(20, 550,0.4,0.4);
    char scoreText[10];
        sprintf(scoreText,"%d",score);
    printMyNumberFont(scoreText,20+179*0.4+5,550-10,0.4);



    /*Print Time*/
    text = controller.getRGBpixmap("image/Fonts/time.bmp",chromaKey);
    text->blendTex(20+300, 535,0.8,0.8);
       char timeText[20];
        sprintf(timeText,"%d",timeRemained/1000);
    printMyNumberFont(timeText,20+300+146*0.8+5,535-10,0.6);

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

void updateTheGame(int value)
{
    if(timer.elapsedTime>timeLimit)
        gameOver();
    else
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
        mainActor -> action(timer.timeSincePrevFrame);
        getHowMuchScore(moles,mainActor);
        glutPostRedisplay();
        glutTimerFunc(GAME_ONE_SHOT_TIME, updateTheGame, 0);
    }
}

void init()
{
    glutKeyboardUpFunc(keyUP);
    glutKeyboardFunc(keyDOWN);
    glutSpecialFunc(SpecialKeyDOWN);
    glutSpecialUpFunc(SpecialKeyUP);
    glutDisplayFunc(myDisplay);
    glutReshapeFunc(myReshape);
    glClearColor(bgColor[0],bgColor[1],bgColor[2],bgColor[3]);
}

void reset()
{
    mainActor = new MainActor(Vec3(0,initialHeight-15,0), Vec3(255, 255, 255));
    moles = new Moles();
    timer.reset();

    score = 0;
    isGameOver = false;
    timer.reset();
    timer.update();

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



    reset();
    updateTheGame(0);
    glutMainLoop();
    return 0;
}

