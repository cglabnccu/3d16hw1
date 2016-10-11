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
#include <vector>

#include "RGBpixmap.h"
#include "creature.h"
#include "player.h"
#include "enemy.h"
#include "bullet.h"
#include "power.h"

// Global variables for measuring time (in milli-seconds)
int startTime;
int prevTime;

//  http://devmaster.net/forums/topic/7934-aabb-collision/

bool AABBtest(float ax1, float ay1, float ax2, float ay2, float bx1, float by1, float bx2, float by2)
{
    return
        ax1 > bx2 || ax2 < bx1 ||
        ay1 > by2 || ay2 < by1;
}

static void CheckError(int line)
{
   GLenum err = glGetError();
   if (err) {
      printf("GL Error %s (0x%x) at line %d\n",
             gluErrorString(err), (int) err, line);
   }
}

//Set windows
int screenWidth = 1000 , screenHeight = 600;

int i=0;
player p(380,4);
RGBApixmap playerHearts;

enemy pc;

int playerBullet=40;
int pcBullet=1000;
bullet pBulletList[40];
pcbullet pcBulletList[1000];
power powerCubeList[40];
int pauseFlag=0;//record whether to pulse

RGBApixmap bg;

int flag=0;


void setSpecialKeyStateUp(int key,int x,int y)
{
    switch(key)
    {
        case GLUT_KEY_UP:
            p.directXY[0]=0;
            break;
        case GLUT_KEY_DOWN:
            p.directXY[1]=0;
            break;
        case GLUT_KEY_LEFT:
            p.directXY[2]=0;
            break;
        case GLUT_KEY_RIGHT:
            p.directXY[3]=0;
            break;
    }
}
void setSpecialKeyStateDown(int key,int x,int y)
{
    switch(key)
    {
        case GLUT_KEY_UP:
            p.directXY[0]=1;
            break;
        case GLUT_KEY_DOWN:
            p.directXY[1]=1;
            break;
        case GLUT_KEY_LEFT:
            p.directXY[2]=1;
            break;
        case GLUT_KEY_RIGHT:
            p.directXY[3]=1;
            break;
    }
}
//int rectX=380, rectY=550;


int DirectState=0;  //0:right  1:left
int Gamescore=0;

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
	// Measure the elapsed time
	int currTime = glutGet(GLUT_ELAPSED_TIME);
	int timeSincePrevFrame = currTime - prevTime;
	int elapsedTime = currTime - startTime;
	prevTime = currTime;

	char fpsmss[30];
	sprintf(fpsmss, "Fps %.1f", 1000.0/timeSincePrevFrame);


	glClear(GL_COLOR_BUFFER_BIT);
// if gameover

    //draw background
    glRasterPos2i(0, 0);
    bg.blend();
    if(p.hearts==0)
    {

        glRasterPos2i(0,0);
        glColor3f(1.0,0.0,0.0);
        char endmss[10]="Game Over";
        glRasterPos2f(340,300);
        for(int i=0; i<strlen(endmss); i++) {
            glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, endmss[i]);
        }
        char endmss2[30];
        sprintf(endmss2, "Score %d", Gamescore);

        glColor3f(1.0,0.3,0.0);  //set font color
        glRasterPos2i(360, 250);    //set font start position
        for(int i=0; i<strlen(endmss2); i++) {
            glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, endmss2[i]);
        }
        glutSwapBuffers();
        Sleep(2000);
        exit(0);
    }
    //bullets by player
    if(pc.life>0)
    {
        for(int i=0;i<playerBullet;i++)
        {
            if(pBulletList[i].getX()!=-100)
            {
                if(!AABBtest(pBulletList[i].getX(),
                    pBulletList[i].getY(),
                    pBulletList[i].getX()+pBulletList[i].pic.w(),
                    pBulletList[i].getY()+pBulletList[i].pic.h(),
                    pc.getX(),pc.getY(),pc.getX()+pc.pic.w(),pc.getY()+pc.pic.h()) )
                {
                    pBulletList[i].die();
                    pc.life--;
                    Gamescore+=50;
                }
                else if( pBulletList[i].getY()>792)
                {
                    pBulletList[i].die();
                }
                else
                {
                    pBulletList[i].pic.blendTex(pBulletList[i].getX(),pBulletList[i].getY());
                }
            }
        }
    }
    else
    {
        for(int i=0;i<5;i++)
        {
            for(int j=0;j<40;j++)
            {
                if(powerCubeList[j].getX()==-100)
                {
                    powerCubeList[j].form(pc.getX(),pc.getY());
                    break;
                }
            }
        }
        pc.form();
    }
    //bullets by pc
    for(int i=0;i<pcBullet;i++)
    {
        if(!AABBtest(pcBulletList[i].getX(),
                     pcBulletList[i].getY(),
                     pcBulletList[i].getX()+pcBulletList[i].pic.w(),
                     pcBulletList[i].getY()+pcBulletList[i].pic.h(),
                     p.getX()+8,p.getY()+24,p.getX()+23,p.getY()+39))
        {
            pcBulletList[i].die();
            p.hearts--;
            //Gamescore-=100;
        }
        else if(pcBulletList[i].getY()+pcBulletList[i].pic.h()<=0)
        {
            pcBulletList[i].die();
        }
        else pcBulletList[i].pic.blendTex(pcBulletList[i].getX(),pcBulletList[i].getY());
    }

    //powerCube action
    for(int i=0;i<40;i++)
    {
        if(!AABBtest(powerCubeList[i].getX(),powerCubeList[i].getY(),
                     powerCubeList[i].getX()+powerCubeList[i].pic.w(),
                     powerCubeList[i].getY()+powerCubeList[i].pic.h(),
                     p.getX(),p.getY(),p.getX()+p.pic.w(),p.getY()+p.pic.h()))
        {
            powerCubeList[i].die();
            p.power=p.power+2+rand()%2;
        }
        else if(powerCubeList[i].getY()<0)
        {
            powerCubeList[i].die();
        }
        else powerCubeList[i].pic.blendTex(powerCubeList[i].getX(),powerCubeList[i].getY());
    }

    p.pic.blendTex(p.getX(),p.getY());
    pc.pic.blendTex(pc.getX(),pc.getY());

    //record player's life
    char lifemss[6]={"LIFE:"};
    glColor3f(0.62,1.0,1.0);
    glRasterPos2i(805,400);
    for(int i=0;i<strlen(lifemss);i++)
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18,lifemss[i]);
    for(int i=0;i<p.hearts;i++)
        playerHearts.blendTex(850+20*i,400,1,1);
    char powermss[15];
    sprintf(powermss, "POWER: %d",p.power);
    glColor3f(0.62,1.0,1.0);
    glRasterPos2i(805,350);
    for(int i=0;i<strlen(powermss);i++)
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18,powermss[i]);
	char mss[30];
	sprintf(mss, "Score %d", Gamescore);

	glColor3f(0.8,0.3,0.8);  //set font color
    glRasterPos2i(10, 550);    //set font start position
	for(int i=0; i<strlen(mss); i++) {
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, mss[i]);
	}

	glColor3f(0.0, 0.5, 0.3);  //set font color
    glRasterPos2i(screenWidth-100, 550);    //set font start position
	for(int i=0; i<strlen(fpsmss); i++) {
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_10, fpsmss[i]);
	}

	CheckError(__LINE__);

	glutSwapBuffers();
}






void update(int i)
{
    if(pauseFlag==1)Sleep(8);
    else{
        double r = double(i)/200.0;
        pc.action();
        p.setPosition();
        for(int i=0;i<40;i++)
            powerCubeList[i].action();
        for(int i=0;i<playerBullet;i++)
            pBulletList[i].action();
        for(int i=0;i<pcBullet;i++)
            pcBulletList[i].action();

        if(i%8==0 && p.shooting==1)
        {
            for(int i=0;i<playerBullet;i++)
            {
                if(p.power>50&&pBulletList[i].powerFlag==1)
                {
                    pBulletList[i].powerFlag=2;
                    pBulletList[i].setPic(p.no,pBulletList[i].powerFlag);
                    pBulletList[i].pic.setChromaKey(255,255,255);
                }
                if(pBulletList[i].getY()==-100)
                {
                    pBulletList[i].setXY(p.getX() + 0.5*p.pic.w() - 0.5*pBulletList[i].pic.w(),p.getY()+p.pic.h());
                    break;
                }
            }
        }
        if(i%10==0)//per 72ms a pcbullet appear
        {
            for(int i=0;i<pcBullet;i++)
            {
                if(pcBulletList[i].getY()==-100)
                {
                    pcBulletList[i].setXY(rand()%784,580);
                    break;
                }
            }
        }

	//rectY = 300 + 250*sin(r);
    }
	++i;
	glutTimerFunc( 8, update, i);
	glutPostRedisplay();
}

void setKeyStateUp(unsigned char key,int x,int y)
{
    switch(key)
    {
        case 'z':case 'Z':
            p.slowMotion=0;
            break;
        case ' ':
            p.shooting=0;
            break;
        default:
            break;
    }
}
void setKeyStateDown(unsigned char key,int x,int y)
{
    switch(key)
    {
        case '1':
            if(p.no==2)
            {
                p.setPic(1);
                p.pic.setChromaKey(0,0,0);
                p.no=1;
                for(int i=0;i<playerBullet;i++)
                {
                    pBulletList[i].die();
                    pBulletList[i].setPic(p.no,(p.power>50)?2:1);
                    pBulletList[i].pic.setChromaKey(255,255,255);
                }
            }
            break;
        case '2':
            if(p.no==1)
            {
                p.setPic(2);
                p.pic.setChromaKey(0,0,0);
                p.no=2;
                for(int i=0;i<playerBullet;i++)
                {
                    pBulletList[i].die();
                    pBulletList[i].setPic(p.no,(p.power>50)?2:1);
                    pBulletList[i].pic.setChromaKey(255,255,255);
                }
            }
            break;
        case 'z':case 'Z':
            p.slowMotion=1;
            break;
        case 'q':case 'Q':
            exit(0);
            break;
        case ' ':
            p.shooting=1;
            break;
        case 27:
            pauseFlag=(pauseFlag==1)?0:1;
            break;
    }
}


void init()
{

    glutSpecialFunc(setSpecialKeyStateDown);
    glutSpecialUpFunc(setSpecialKeyStateUp);
    glutKeyboardFunc(setKeyStateDown);
    glutKeyboardUpFunc(setKeyStateUp);

	glutDisplayFunc(myDisplay);
	glutReshapeFunc(myReshape);

	glShadeModel(GL_SMOOTH);
	//glEnable(GL_DEPTH_TEST);
    glClearColor(0.007f, 0.627f, 1.0f, 1.0f); //background color(1.0, 1.0, 1.0): white color
    //背景的預設是默認不透明
}

int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(screenWidth, screenHeight);
	glutInitWindowPosition(0, 0);//從左上角開始算
	//↑我的螢幕是1920*1080，然後我是放大1.5倍，所以是1280*720
	//(如果要將視窗貼右下角的話則Position(480,120)
	glutCreateWindow("103703027HW1");

	init();

	srand(time(0));  //rand seed
	bg.readBMPFile("image/bg.bmp");
    p.pic.setChromaKey(0,0,0);
    playerHearts.readBMPFile("image/hearts.bmp");
    playerHearts.setChromaKey(255,255,255);

    pc.pic.setChromaKey(255,255,255);
    pc.form();
    for(int i=0;i<playerBullet;i++)
        pBulletList[i].pic.setChromaKey(255,255,255);
    for(int i=0;i<pcBullet;i++)
        pcBulletList[i].pic.setChromaKey(255,255,255);


	startTime = glutGet(GLUT_ELAPSED_TIME);
	prevTime = startTime;

	update(0);
	glutMainLoop();

	return 0;
}


