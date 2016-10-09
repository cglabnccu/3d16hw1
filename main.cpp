//3D game programming 2013
//lab2: 2D


#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <windows.h>
//#include <GL/glew.h>
#include <GL/glut.h>
#endif

#include <stdlib.h>
#include <time.h>
#include <string.h>

#include "RGBpixmap.h"

// Global variables for measuring time (in milli-seconds)
int startTime;
int prevTime;

//  http://devmaster.net/forums/topic/7934-aabb-collision/
static void CheckError(int line)
{
    GLenum err = glGetError();
    if (err)
    {
        printf("GL Error %s (0x%x) at line %d\n",
               gluErrorString(err), (int) err, line);
    }
}

//Set windows
int screenWidth = 800 , screenHeight = 400;

int i=0;
RGBApixmap night, wall, wall1;
RGBApixmap bat[2];
int whichPic = 0; // which pixmap to display
int picX=screenWidth/15, picY=screenHeight/2;
int wallX[3], wallY[3];
int speed = 3;
int w[6],index;
int energy = 0;

int rectX=300, rectY=100;

int Gamescore=0;
bool play = true,score = false,useEnergy = false;
int wallWidth = 400;

void init();

//myReshape
void myReshape(int w, int h)
{
    /* Save the new width and height */
    screenWidth  = w;
    screenHeight = h;

    /* Reset the viewport... */
    glViewport(0, 0, screenWidth, screenHeight);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    glOrtho(0.0, (GLfloat)screenWidth, 0.0, (GLfloat)screenHeight, -1.0, 1.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

//myDisplay
void myDisplay(void)
{
    if(play)
    {
        glClear(GL_COLOR_BUFFER_BIT);

        //draw background
        night.blendTex(0, 0, 1, 1);

        bat[whichPic].blendTex(picX , picY , 0.3, 0.3);
        wall.blendTex(wallX[0],wallY[0]);
        wall.blendTex(wallX[0],wallY[0] - bat[whichPic].h() * 0.9 - wall.h());
        wall.blendTex(wallX[1],wallY[1]);
        wall.blendTex(wallX[1],wallY[1] - bat[whichPic].h() * 0.9 - wall.h());
        wall1.blendTex(wallX[2],wallY[2]);
        wall1.blendTex(wallX[2],wallY[2] - bat[whichPic].h() * 0.9 - wall.h());

        //bouding box outside test
        if(picY < 0)
        {
            picY = 0;
        }
        else if(picY > screenHeight - bat[whichPic].h()*0.3)
        {
            picY = screenHeight - bat[whichPic].h()*0.3;
        }

        if(wallX[0] < picX + bat[whichPic].w()*0.3 && wallX[0] + wall.w() > picX)
        {
            if(useEnergy)
            {
                score = true;
            }
            else if(picY + bat[whichPic].h()*0.3 > wallY[0] || picY < wallY[0] - bat[whichPic].h() * 0.9)
            {
                play = false;
            }
            else
            {
                score = true;
            }
        }
        else if(wallX[1] < picX + bat[whichPic].w()*0.3 && wallX[1] + wall.w() > picX)
        {
            if(useEnergy)
            {
                score = true;
            }
            else if(picY + bat[whichPic].h()*0.3 > wallY[1] || picY < wallY[1] - bat[whichPic].h() * 0.9)
            {
                play = false;
            }
            else
            {
                score = true;
            }
        }
        else if(wallX[2] < picX + bat[whichPic].w()*0.3 && wallX[2] + wall.w() > picX)
        {
            if(useEnergy)
            {
                score = true;
            }
            else if(picY + bat[whichPic].h()*0.3 > wallY[2] || picY < wallY[2] - bat[whichPic].h() * 0.9)
            {
                play = false;
            }
            else
            {
                score = true;
            }
        }
        else
        {
            if(score)
            {
                Gamescore++;
                score = false;
                speed = 3 + Gamescore/3;
                if(Gamescore%8 == 0 && Gamescore != 0)
                    wallWidth += 100;
            }
        }
        if(useEnergy)
        {
            play = true;
            energy -= 8;
            if(3 + Gamescore/3 > 25){
                speed = (3 + Gamescore/3)*2;
            }
            else{
                speed = 30;
            }
            if(energy < 100){
                speed /= 2;
            }
            if(energy <= 0)
            {
                useEnergy = false;
                speed = 3 + Gamescore/3;
                energy = 0;
            }
        }
        if(play == false)
        {
            char gameOver[10];
            char point[30];
            sprintf(gameOver,"Game Over!");
            sprintf(point,"You Got %d Point",Gamescore);
            glColor3f(1.0, 1.0, 1.0);
            glRasterPos2i(screenWidth/2 - 50, screenHeight/2 + 20);
            for(int i=0; i<strlen(gameOver); i++)
            {
                glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, gameOver[i]);
            }
            glRasterPos2i(screenWidth/2 - 70, screenHeight/2 - 20);
            for(int i=0; i<strlen(point); i++)
            {
                glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, point[i]);
            }
        }
    }

    //Font
    char mss[30];
    sprintf(mss, "Score: %d", Gamescore);

    glColor3f(1.0, 0.0, 0.0);  //set font color
    glRasterPos2i(10, 380);    //set font start position
    for(int i=0; i<strlen(mss); i++)
    {
        glutBitmapCharacter(GLUT_BITMAP_9_BY_15, mss[i]);
    }

    glRasterPos2i(10, 360);    //set font start position
    char en[100];
    sprintf(en, "Energy: %d", energy);
    for(int i=0; i<strlen(en); i++)
    {
        glutBitmapCharacter(GLUT_BITMAP_9_BY_15, en[i]);
    }

    energy++;

    CheckError(__LINE__);

    glutSwapBuffers();
}



void SpecialKeys(int key, int x, int y)
{
    // this string keeps the last good setting for the game mode
    //char gameModeString[40] = "800x600";
    if(play)
    {
        switch(key)
        {
        case GLUT_KEY_UP:
            picY += 7;
            if (whichPic==0) whichPic=1;
            else whichPic=0;
            break;
        case GLUT_KEY_RIGHT:
            if(energy >= 100)
            {
                useEnergy = true;
            }
            break;
        case GLUT_KEY_DOWN:
            picY -= 1;
            whichPic = 0;
            break;
        }
        glutPostRedisplay();
    }
}

void update(int i)
{
    if(play)
    {
        if(wallX[0] < 0 - wall.w())
        {
            wallY[0] = w[index];
            index++;
            if(index > 5)
            {
                index = 0;
            }
            wallX[0] = wallX[2] + wallWidth;
        }
        if(wallX[1] < 0 - wall.w())
        {
            wallY[1] = w[index];
            index++;
            if(index > 5)
            {
                index = 0;
            }
            wallX[1] = wallX[0] + wallWidth;
        }
        if(wallX[2] < 0 - wall.w())
        {
            wallY[2] = w[index];
            index++;
            if(index > 5)
            {
                index = 0;
            }
            wallX[2] = wallX[1] + wallWidth;
        }

        picY -= 3;
        wallX[0] -= speed;
        wallX[1] -= speed;
        wallX[2] -= speed;

        ++i;
        glutTimerFunc( 33, update, i);
        glutPostRedisplay();
    }
}


//<<<<<<<<<<<<<<<<<<<<<<<< myKeys >>>>>>>>>>>>>>>>>>>>>>
void myKeys(unsigned char key, int x, int y)
{
    switch(key)
    {
    case 'Q':
    case 'q':
        exit(0);
        break;
    } //switch(key)

    glutPostRedisplay();
}


void init()
{
    glutSpecialFunc(SpecialKeys);
    glutKeyboardFunc(myKeys);
    glutDisplayFunc(myDisplay);
    glutReshapeFunc(myReshape);
    glShadeModel(GL_SMOOTH);

    glClearColor(1.0f, 1.0f, 1.0f, 0.0f); //background color(1.0, 1.0, 1.0): white color

    w[0] = 300;
    w[1] = 100;
    w[2] = 200;
    w[3] = 350;
    w[4] = 150;
    w[5] = 400;
    index = 0;
    wallX[0] = screenWidth/2 - 100;
    wallY[0] = w[index];
    index++;
    wallX[1] = screenWidth/2 + 300;
    wallY[1] = w[index];
    index++;
    wallX[2] = screenWidth/2 + 700;
    wallY[2] = w[index];
    index++;
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(screenWidth, screenHeight);
    glutInitWindowPosition(50, 30);
    glutCreateWindow("2D World");

    init();

    srand(time(0));  //rand seed

    cout<<"Reading sprite";
    night.readBMPFile("image/night.bmp");
    bat[0].readBMPFile("image/flydown.bmp");
    bat[1].readBMPFile("image/flyup.bmp");
    wall.readBMPFile("image/wall.bmp");
    wall1.readBMPFile("image/wall1.bmp");

    //night.setChromaKey(232, 248, 248);
    for (int i=0; i<2; i++) bat[i].setChromaKey(232, 248, 248);
    night.setChromaKey(232,248,248);
    wall.setChromaKey(232,248,248);

    // Initialize the time variables
    startTime = glutGet(GLUT_ELAPSED_TIME);
    prevTime = startTime;

    update(0);
    glutMainLoop();

    return 0;
}

