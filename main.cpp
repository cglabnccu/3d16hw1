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
bool win=false,lose=false;
char gameModeString[40] = "800x600";

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

int i=0;
RGBApixmap pic[3]; // create two (empty) global pixmaps
RGBApixmap bg,frog_win,frog_lose;
RGBApixmap car[5]; 
int whichPic = 0; // which pixmap to display
int picX=100, picY=0;
//int rectX=300, rectY=100;
int rectX[5],rectY[5];///////////////////////
float rotation_test=0;
float scale_test=0.3;
int jumpState=0;
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
	glViewport(0,0, screenWidth, screenHeight);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	glOrtho(0.0, (GLfloat)screenWidth,0.0, (GLfloat)screenHeight, -1.0, 1.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}
void frogHit(){
rotation_test += 2;
	char mss[50];
	frog_lose.blendTexRotate(picX, picY,1,1,rotation_test);
	sprintf(mss, "GAME OVER...QQ... enter 'r' to restart~~", Gamescore);
	glColor3f(0,0.0, 1);  //set font color
	glRasterPos2i(220, 550);    //set font start position
	for(int i=0; i<strlen(mss); i++) {
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, mss[i]);
	}
	lose=true;
}
void clear(){
	char mss[50];
	frog_win.blendTex(picX,picY);
	sprintf(mss, "CLEAR~ enter 'r' to restart~~", Gamescore);
	glColor3f(0.0, 0, 1);  //set font color
	glRasterPos2i(220, 550);    //set font start position
	for(int i=0; i<strlen(mss); i++) {
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, mss[i]);
	}
	win = true;

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
	glColor3f(1,1,1);
	glRectf(0,540,800,530);
	glColor3f(1,1,1);
	glRectf(0,450,800,440);
	glColor3f(1,1,1);
	glRectf(0,360,800,350);
	glColor3f(1,1,1);
	glRectf(0,270,800,260);
	glColor3f(1,1,1);
	glRectf(0,180,800,170);
	glColor3f(1,1,1);
	glRectf(0,90,800,80);

	//draw background
	glRasterPos2i(50, 50);
	bg.blend();
	//change direction
if(!win&&!lose){
	if(DirectState==0) {
		pic[whichPic].blendTex(picX, picY);

	}else {
		int offset = pic[whichPic].nCols;
		pic[whichPic].blendTex(picX+offset, picY, -1, 1);
	}
}
//else if(lose){
//	frog_lose.blendTex(picX, picY);

//}
	//rotation test
//			pic[0].blendTexRotate(100, 250, 1, 1, rotation_test);
	//scale test
	//	pic[0].blendTex(250, 250);

	//bouding box outside test
	bool Hit = !AABBtest(picX, picY, picX + pic[whichPic].w(), picY + pic[whichPic].h(), rectX[0], rectY[0], rectX[0] + 25, rectY[0] + 25);

	if(Hit) {
		frogHit();		
		glColor3f(1.0f, 0.0f, 0.0f);
		Gamescore -= 1;
		//	picX=10;picY=0; 
	}else {
		car[0].blendTex(rectX[0],rectY[0]);

	}
	Hit = !AABBtest(picX, picY, picX + pic[whichPic].w(), picY + pic[whichPic].h(), rectX[1], rectY[1], rectX[1] + 25, rectY[1] + 25);

	if(Hit) {
		frogHit();		
		glColor3f(1.0f, 0.0f, 0.0f);
		Gamescore -= 1;
		//	picX=10;picY=0;
	}else{
		car[1].blendTex(rectX[1],rectY[1]);

	}
	Hit = !AABBtest(picX, picY, picX + pic[whichPic].w(), picY + pic[whichPic].h(), rectX[2], rectY[2], rectX[2] + 25, rectY[2] + 25);

	if(Hit) {
		frogHit();		
		glColor3f(1.0f, 0.0f, 0.0f);
		Gamescore -= 1;	
		//picX=10;picY=0;
		lose = true;
	}else{
		car[2].blendTex(rectX[2],rectY[2]);
	}

	Hit = !AABBtest(picX, picY, picX + pic[whichPic].w(), picY + pic[whichPic].h(), rectX[3], rectY[3], rectX[3] + 25, rectY[3] + 25);

	if(Hit) {
		frogHit();		
		glColor3f(1.0f, 0.0f, 0.0f);
		Gamescore -= 1;	
		//picX=10;picY=0;
		lose = true;

	}else{
		car[3].blendTex(rectX[3],rectY[3]);
	}
	Hit = !AABBtest(picX, picY, picX + pic[whichPic].w(), picY + pic[whichPic].h(), rectX[4], rectY[4], rectX[4] + 25, rectY[4] + 25);

	if(Hit) {
		frogHit();		
		glColor3f(1.0f, 0.0f, 0.0f);
		Gamescore -= 1;	//picX=10;picY=0;
		lose = true;

	}else{
		car[4].blendTex(rectX[4],rectY[4]);
	}
	if(picY>rectY[4]){ 
		//Font
		clear();
		char mss[30];
		//	sprintf(mss, "CLEAR~", Gamescore);

		//	glColor3f(1.0, 0.0, 0.0);  //set font color
		//	glRasterPos2i(200, 300);    //set font start position
		//	for(int i=0; i<strlen(mss); i++) {
		//		glutBitmapCharacter(GLUT_BITMAP_9_BY_15, mss[i]);
		//	}

		//	glColor3f(0.0, 0.5, 0.3);  //set font color
		//	glRasterPos2i(screenWidth-100, 550);    //set font start position
		//	for(int i=0; i<strlen(fpsmss); i++) {
		//		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, fpsmss[i]);
		//	}

	}
	CheckError(__LINE__);

	glutSwapBuffers();
}

void SpecialKeys(int key, int x, int y)
{
	// this string keeps the last good setting for the game mode
	//char gameModeString[40] = "800x600";

	switch(key) {
		case GLUT_KEY_UP:
			if(picY<=510&&!lose&&!win)
				picY += 90;
			break;
		case GLUT_KEY_DOWN:
			if(picY>=90&&!lose&&!win)
				picY -= 90;
			break;
		case GLUT_KEY_LEFT:
			if(picX>=20&&!lose&&!win)
				picX -= 40;
			if (whichPic==0) whichPic=1;
			else whichPic=0;
			DirectState=1;
			break;
		case GLUT_KEY_RIGHT:
			if(picX<=720&&!lose&&!win)
				picX += 40;
			if (whichPic==0) whichPic=1;
			else whichPic=0;
			DirectState=0;
			break;

		case'r':case'R':
			if(win||lose){
				glClearColor(0.0f, 0.9f, 0.8f, 0.0f); 
				win=false;
				lose=false;
				picX=10;picY=0;
			}
			break;	
			//		   case GLUT_KEY_F1:
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
			break;



	}
	glutPostRedisplay();
}


void update(int i)
{

	if(rectX[0]<0) rectX[0]=810;
	if(!lose&&!win)	
		rectX[0]-=10;
	if(!lose&&!win)
		rectX[1]+=15;
	if(rectX[1]>800) rectX[1]=-20;
	if(!lose&&!win)
		rectX[2]-=20;
	if(rectX[2]<0) rectX[2]=825;
	if(!lose&&!win)
		rectX[3]+=25;
	if(rectX[3]>800) rectX[3]=-30;	
	if(!lose&&!win)
		rectX[4]-=28;
	if(rectX[4]<0) rectX[4]=830;
	++i;
	glutTimerFunc( 33, update, i);
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

	glutSpecialFunc(SpecialKeys);
	//glutKeyboardFunc(myKeys);
	//	glutMouseFunc(myMouse);
	//	glutMotionFunc(mouseMove);
	glutDisplayFunc(myDisplay);
	glutReshapeFunc(myReshape);

	glShadeModel(GL_SMOOTH); 
	//glEnable(GL_DEPTH_TEST);
	glClearColor(0.0f, 0.9f, 0.8f, 0.0f); //background color(1.0, 1.0, 1.0): white color


}

int main(int argc, char **argv)
{
	glutInit(&argc, argv);     //ok
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB); //ok
	glutInitWindowSize(screenWidth, screenHeight);///ok
	glutInitWindowPosition(50, 30);/////////
	glutCreateWindow("2D World");/////
	rectX[0]=100;rectX[1]=200;rectX[2]=300;rectX[3]=400;rectX[4]=500;
	rectY[0]=100;rectY[1]=190;rectY[2]=280;rectY[3]=370;rectY[4]=460;
	init();
	srand(time(0));  //rand seed
	car[0].readBMPFile("image/car2.bmp");
	car[1].readBMPFile("image/car1.bmp");
	car[2].readBMPFile("image/car4.bmp");
	car[3].readBMPFile("image/car3.bmp");
	car[4].readBMPFile("image/car5.bmp");

	frog_win.readBMPFile("image/win.bmp");
	frog_lose.readBMPFile("image/lose.bmp");
	cout<<"Reading sprite";
	pic[0].readBMPFile("image/frog.bmp");  cout<<'.';
	pic[1].readBMPFile("image/frog.bmp");  cout<<'.';
	pic[2].readBMPFile("image/fly.bmp");  cout<<'.'<<endl;
	for (int i=0; i<5; i++) car[i].setChromaKey(232, 248, 248);
	for(int i=0;i<2;i++) pic[i].setChromaKey(232,248,248);
	frog_win.setChromaKey(232,248,248);
	frog_lose.setChromaKey(232,248,248);
	//cout<<"Reading Backgroud........"<<endl;
	//	bg.readBMPFile("image/images.png");////////////////////

	// Initialize the time variables
	//	startTime = glutGet(GLUT_ELAPSED_TIME);
	//	prevTime = startTime;
	update(0);
	glutMainLoop();

	return 0;
}

