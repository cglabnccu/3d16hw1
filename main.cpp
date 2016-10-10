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
#define PICNUM 2
#define DIRNUM 6
#define RLTNUM 4

// Global variables for measuring time (in milli-seconds)
int manholeDisappear;
int dirIndex = -1;
int rltIndex = 0;
float scale=0.1;
int heart = 6;
int hit=0;
int stage=0;
int timer=1000;
int hitCeiling = 10;
//int getInTimer =0;
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
int screenWidth = 800 , screenHeight = 600;

bool stop = false;
RGBApixmap pic[PICNUM]; // create two (empty) global pixmaps
RGBApixmap dirPic[DIRNUM];
RGBApixmap rltPic[RLTNUM];
RGBApixmap bg;

int picX=100, picY=100;

int rectX=300, rectY=100;
int Gamescore=0;

void init();
void update(int i);

//<<<<<<<<<<<<<<<<<<<<<<<<< myMouse >>>>>>>>>>>>>>>>>>>>>>>>
void myMouse(int button, int state, int mx, int my)
{ // set raster position with a left click
	/*	if(button == GLUT_LEFT_BUTTON )
		{
		stop = false;
		glutPostRedisplay();
		}
	 */
}
//<<<<<<<<<<<<<<<<<<<<<<<<< mouseMove >>>>>>>>>>>>>>>>>
/*void mouseMove(int x, int y)
  {// set raster position with mouse motion
//rasterPos.x = x; rasterPos.y = screenHeight - y;
//glRasterPos2i(rasterPos.x, rasterPos.y);
glutPostRedisplay();
}*/

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

void update(int i)
{
	if(!stop){
		dirIndex = -1;
		int last = manholeDisappear;
		do{
			manholeDisappear = rand()%9;
		}while(manholeDisappear == last);	// produce new hole
		i=-1;
	}
	else{
		manholeDisappear = -1;
		if(i == 0){
			int last = dirIndex;
			do{
				dirIndex = rand() % DIRNUM;
			}while(dirIndex == last);
		}
		else if(i >= 10){
			stop = false;
			scale = 0.1;
			hit = 0;
			dirIndex = -1;
			heart-=1;
		}
		else if(hit >= hitCeiling){
			heart++;
			if(heart>=6)	heart=6;
			rltIndex = (++rltIndex)%RLTNUM;
			if(rltIndex == 0){
				stage++;
				timer-=200;
				hitCeiling+=10;
			}
			stop = false;
			scale = 0.1;
			hit = 0;
			dirIndex = -1;
		}
	}
	glutPostRedisplay();
	glutTimerFunc( timer, update, ++i);
}

//myDisplay
void myDisplay(void)
{
	// Measure the elapsed time
	//	currTime = glutGet(GLUT_ELAPSED_TIME);
	//	int timeSincePrevFrame = currTime - prevTime;
	//	elapsedTime = currTime - startTime;
	//	prevTime = currTime;

	if(heart == 0)
		exit(0);
	/*	char fpsmss[30];
		sprintf(fpsmss, "Fps %.1f", 1000.0/timeSincePrevFrame);*/


	glClear(GL_COLOR_BUFFER_BIT);

	//draw background
	glRasterPos2i(50, 50);
	bg.blend();
	if(!stop){
		int posXCltr=-90, posYCltr=-130;
		for(int i=0; i<9; i++){
			if( i != manholeDisappear )	pic[0].blendTex( screenWidth/3+posXCltr, screenHeight/3+posYCltr, 0.3, 0.3 );
			posXCltr += 145;
			if( i%3==2 && i!=0 ){
				posXCltr = -90;
				posYCltr += 145;
			}
		}
	}
	else{
		rltPic[rltIndex].blendTex(1, 1, scale,scale);
		dirPic[dirIndex].blendTex( 100, 400, 0.5, 0.5);
	}
	int x = 0;
	for(int i=0; i<heart; i++){
		pic[1].blendTex( 300+x,500,0.5,0.5);
		x+=80;
	}
	//Font
	char mss[30];
	sprintf(mss, "Hit %d", hit);

	glColor3f(1.0, 0.0, 0.0);  //set font color
	glRasterPos2i(10, 550);    //set font start position
	for(int i=0; i<strlen(mss); i++) {
		glutBitmapCharacter(GLUT_BITMAP_9_BY_15, mss[i]);
	}

	glColor3f(0.0, 0.5, 0.3);  //set font color
	glRasterPos2i(screenWidth-100, 550);    //set font start position
	//	for(int i=0; i<strlen(fpsmss); i++) {
	//		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, fpsmss[i]);
	//	}

	CheckError(__LINE__);

	glutSwapBuffers();
}

void SpecialKeys(int key, int x, int y)
{
	// this string keeps the last good setting for the game mode
	//char gameModeString[40] = "800x600";

	switch(key) {
			case GLUT_KEY_LEFT:
				if(dirIndex == 0 || dirIndex == 2){
					scale+=0.1;
					hit += 1;
				}
				else{
					scale-=0.1;
					if(stop)	hit -=1;
					heart -= 1;
				}
				break;
			case GLUT_KEY_RIGHT:
				if(dirIndex == 1 || dirIndex == 3){
					scale+=0.1;
					hit += 1;
				}
				else{
					scale-=0.1;
					if(stop)	hit -= 1;
					heart -= 1;
				}
				break;
			case GLUT_KEY_UP:
				if(dirIndex == 4 || dirIndex == 5){
					scale+=0.1;
					hit += 1;
				}
				else{
					scale-=0.1;
					if(stop)	hit -= 1;
					heart -= 1;
				}
				break;
			case GLUT_KEY_DOWN:
				if(dirIndex != -1){
					scale-=0.1;
					if(stop)	hit -= 1;
					heart -= 1;
				}
				break;
				/*		case GLUT_KEY_F1:
				// define resolution, color depth
				glutGameModeString("640x480:32");
				// enter full screen
				if (glutGameModeGet(GLUT_GAME_MODE_POSSIBLE)) {
				glutEnterGameMode();
				sprintf(gameModeString,"640x480:32");
				// register callbacks again
				// and init OpenGL context
				init();
				}
				else
				glutGameModeString(gameModeString);
				break;

				case GLUT_KEY_F2:
				glutFullScreen();
				break;
				case GLUT_KEY_F6:
				// return to default window
				if (glutGameModeGet(GLUT_GAME_MODE_ACTIVE) != 0)
				glutLeaveGameMode();
				break;*/
	}
	glutPostRedisplay();
}

//<<<<<<<<<<<<<<<<<<<<<<<< myKeys >>>>>>>>>>>>>>>>>>>>>>
void myKeys(unsigned char key, int x, int y)
{
	switch(key)
	{
		case 'Z':
		case 'z':
			if(manholeDisappear == 0){
				stop = true; }
			else{
				heart -= 1;}
			break;

		case 'X':
		case 'x':
			if(manholeDisappear == 1){
				stop = true; }
			else{
				heart -= 1;}
			break;

		case 'C':
		case 'c':
			if(manholeDisappear == 2){
				stop = true; }
			else{
				heart -= 1;}
			break;

		case 'A':
		case 'a':
			if(manholeDisappear == 3){
				stop = true; }
			else{
				heart -= 1;}
			break;

		case 'S':
		case 's':
			if(manholeDisappear == 4){
				stop = true; }
			else{
				heart -= 1;}
			break;

		case 'D':
		case 'd':
			if(manholeDisappear == 5){
				stop = true; }
			else{
				heart -= 1;}
			break;

		case 'Q':
		case 'q':
			if(manholeDisappear == 6){
				stop = true; }
			else{
				heart -= 1;}
			break;

		case 'W':
		case 'w':
			if(manholeDisappear == 7){
				stop = true; }
			else{
				heart -= 1;}
			break;

		case 'E':
		case 'e':
			if(manholeDisappear == 8){
				stop = true; }
			else{
				heart -= 1;}
			break;
	} //switch(key)

	glutPostRedisplay();
}

void init()
{
	//GLenum err = glewInit();
	//if (GLEW_OK != err)
	//{
	//  // Problem: glewInit failed, something is seriously wrong.
	//  fprintf(stderr, "Error: %s\n", glewGetErrorString(err));
	//}

	glutSpecialUpFunc(SpecialKeys);
	glutKeyboardUpFunc(myKeys);
	glutMouseFunc(myMouse);
	glutDisplayFunc(myDisplay);
	glutReshapeFunc(myReshape);

	glShadeModel(GL_SMOOTH); 

	glClearColor(255.0f, 255.0f, 255.0f, 1.0f); //background color(1.0, 1.0, 1.0): white color

	manholeDisappear = rand()%9;
}

int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(screenWidth, screenHeight);
	glutInitWindowPosition(50, 30);
	glutCreateWindow("2D World");

	init();

	srand(time(NULL));  //rand seed

	cout<<"Reading sprite";
	pic[0].readBMPFile("image/manhole.bmp");	cout <<".";
	pic[1].readBMPFile("image/heart.bmp");	cout<<".";
	dirPic[0].readBMPFile("image/dirL1.bmp");	cout <<".";
	dirPic[1].readBMPFile("image/dirR1.bmp");	cout <<".";
	dirPic[2].readBMPFile("image/dirL2.bmp");	cout <<".";
	dirPic[3].readBMPFile("image/dirR2.bmp");	cout <<".";
	dirPic[4].readBMPFile("image/dirU1.bmp");	cout <<".";
	dirPic[5].readBMPFile("image/dirU2.bmp");	cout <<".";
	rltPic[0].readBMPFile("image/rlt1.bmp");	cout <<".";
	rltPic[1].readBMPFile("image/rlt2.bmp");	cout <<".";
	rltPic[2].readBMPFile("image/rlt3.bmp");	cout <<".";
	rltPic[3].readBMPFile("image/rlt4.bmp");	cout <<".";
	cout <<endl;

	for (int i=0; i<PICNUM; i++) pic[i].setChromaKey(255, 255, 255);
	for (int i=0; i<DIRNUM; i++) dirPic[i].setChromaKey(255,255,255);
	for(int i=0; i<RLTNUM; i++) rltPic[i].setChromaKey(255,255,255);

	//	cout<<"Reading Backgroud........"<<endl;
	//	bg.readBMPFile("image/sun1.bmp");
	update(0);
	glutMainLoop();

	return 0;
}

