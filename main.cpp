//3D game programming 2016
//lab2: 2D


#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <windows.h>
#include <GL/glut.h>
#endif

#include <stdlib.h>
#include <time.h>
#include <string.h>

#include "RGBpixmap.h"

// Global variables for measuring time (in milli-seconds)
int startTime;
int prevTime;
//Set windows
int screenWidth = 800, screenHeight = 600;

int i=0;
RGBApixmap pic[3];
//pic State
#define STAND 0
#define WALK 1
#define FLY 2
RGBApixmap bg;
int whichPic = 0; // which pixmap to display
int picX=100, picY=100;
int rectX=300, rectY=100;

float rotation_test=0;
float scale_test=0.3;

int jumpState=0;
#define RIGHT 0
#define LEFT 1
int directState=RIGHT;
int gameScore=0;

//  http://devmaster.net/forums/topic/7934-aabb-collision/
bool AABBtest(float ax1, float ay1, float ax2, float ay2, float bx1, float by1, float bx2, float by2)
{
    return
        ax1 > bx2 || ax2 < bx1 ||
        ay1 > by2 || ay2 < by1;
}

static void checkError(int line)
{
    GLenum err = glGetError();
    if (err)
    {
        printf("GL Error %s (0x%x) at line %d\n",
               gluErrorString(err), (int) err, line);
    }
}

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

void myDisplay(void)
{
    // Measure the elapsed time
    int currTime = glutGet(GLUT_ELAPSED_TIME);
    int timeSincePrevFrame = currTime - prevTime;
    int elapsedTime = currTime - startTime;
    prevTime = currTime;

    char fpsmss[30];
    sprintf(fpsmss, "Fps %.1f", 1000.0/timeSincePrevFrame);


    glClear(GL_COLOR_BUFFER_BIT);

    //draw background
    glRasterPos2i(50, 50);
    bg.blend();




    //change direction
    if(directState==0)
    {
        pic[whichPic].blendTex(picX, picY);

    }
    else
    {
        int offset = pic[whichPic].nCols;
        pic[whichPic].blendTex(picX+offset, picY, -1, 1);
    }

    //rotation test
    pic[whichPic].blendTexRotate(100, 250, 1, 1, rotation_test);

    //scale test
    pic[whichPic].blendTexRotate(250, 250, scale_test, scale_test);

    //bouding box outside test
    bool Hit = !AABBtest(picX, picY, picX + pic[whichPic].w(), picY + pic[whichPic].h(), rectX, rectY, rectX + 25, rectY + 25);
    if(Hit)
    {
        glColor3f(1.0f, 0.0f, 0.0f);
        gameScore -= 1;
    }
    else
    {
        glColor3f(0.0f, 1.0f, 0.0f);
    }
    glRectf(rectX, rectY, rectX + 25, rectY + 25);


    //Font
    char mss[30];
    sprintf(mss, "Score %d", gameScore);

    glColor3f(1.0, 0.0, 0.0);  //set font color
    glRasterPos2i(10, 550);    //set font start position
    for(int i=0; i<strlen(mss); i++)
    {
        glutBitmapCharacter(GLUT_BITMAP_9_BY_15, mss[i]);
    }

    glColor3f(0.0, 0.5, 0.3);  //set font color
    glRasterPos2i(screenWidth-100, 550);    //set font start position
    for(int i=0; i<strlen(fpsmss); i++)
    {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, fpsmss[i]);
    }

    checkError(__LINE__);

    glutSwapBuffers();
}

void jump(int i)
{
    whichPic=2;

    if(i<10)
    {
        if (i<5)
        {
            picY+=15;
        }
        else
        {
            picY-=15;
        }
        i++;
        glutTimerFunc( 100, jump, i);
    }
    else
    {
        whichPic=0;
        jumpState=0;
    }

    glutPostRedisplay();
}

void hit(int i)
{


    glutPostRedisplay();
}

void update(int i)
{
    double r = double(i)/50.0;

    rectX = 400 + 250*sin(r);

    rotation_test += 2;
    scale_test += 0.01;

    ++i;
    glutTimerFunc( 33, update, i);
    glutPostRedisplay();
}

void specialKeys(int key, int x, int y)
{
    switch(key)
    {
    case GLUT_KEY_LEFT:
        picX -= 5;
        if (whichPic==STAND) whichPic=WALK;
        else whichPic=STAND;
        directState=LEFT;
        break;
    case GLUT_KEY_RIGHT:
        picX += 5;
        if (whichPic==0) whichPic=1;
        else whichPic=0;
        directState=RIGHT;
        break;
    case GLUT_KEY_UP:
        if(jumpState==0)
        {
            jumpState=1;
            gameScore++;
            jump(0);
        }
        break;
        glutPostRedisplay();
    }
}
void asciiKeys(unsigned char key, int x, int y)
{
    switch(key)
    {
    case 27:        //Key ESC
        exit(0);
        break;
    case ' ':
        if(jumpState==0)
        {
            jumpState=1;
            gameScore++;
            jump(0);
        }
        break;
    case 'f':
        hit(0);
        break;
    }
    glutPostRedisplay();
}


void init()
{
    glutSpecialFunc(specialKeys);
    glutKeyboardFunc(asciiKeys);
    glutDisplayFunc(myDisplay);
    glutReshapeFunc(myReshape);
    glShadeModel(GL_SMOOTH);


    glClearColor(1.0f, 1.0f, 0.0f, 0.0f); //background color(1.0, 1.0, 1.0): white color
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(screenWidth, screenHeight);
    glutInitWindowPosition(50, 30);
    glutCreateWindow("Whack a mole");
    srand(time(0));

    init();

    cout<<"Reading sprite";
    pic[STAND].readBMPFile("image/stand.bmp");
    cout<<'.';
    pic[WALK].readBMPFile("image/walk.bmp");
    cout<<'.';
    pic[FLY].readBMPFile("image/fly.bmp");
    cout<<'.'<<endl;

    for (int i=0; i<3; i++) pic[i].setChromaKey(232, 248, 248);

    // Initialize the time variables
    startTime = glutGet(GLUT_ELAPSED_TIME);
    prevTime = startTime;

    update(0);
    glutMainLoop();

    return 0;
}

