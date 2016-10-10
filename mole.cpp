#include "mole.h"
#include <ctime>
#include <cstdlib>

Mole::Mole()
{
    position.x = rand()%screenWidth;position.y = 0;
    chromaKey.x = 255;chromaKey.y=255;chromaKey.z=255;
    maxAppearTime= 5000+rand()%2000;
    vector<char*> molePicLocation ;
    #define ALIVE 0
    #define DEAD 1
    molePicLocation.push_back("image/mole1.bmp");
    molePicLocation.push_back("image/mole2.bmp");
    RGBpixmapController controller ;
    state[DEAD] = controller.getRGBpixmap(molePicLocation[DEAD],chromaKey);
    state[ALIVE] = controller.getRGBpixmap(molePicLocation[ALIVE],chromaKey);
     pixMap= state[ALIVE];
    startTime = 0;
    hitted=false;
};

void Mole::display(unsigned long currentTime)
{
    int i = currentTime - startTime ;
    const int shrinkSpeed = 500; //(ms)
     // cout << "|cur : " << currentTime << " |start :  " << startTime << " | i :" << i << " | (x,y) :( " << position.x <<" , " << position.y << " ) " <<std::endl;

    if(i<0)
    {
        cout <<"ERROR : Moles i <0  " <<endl;
        reset(currentTime);
    }
    else if(hitted){
       pixMap =  state[DEAD];
        if (position.y >0 )
            position.y-=3;
        else{
     reset(currentTime);
        }

    }
    else  if (position.y <100 && i <  maxAppearTime-shrinkSpeed)
        position.y+=2;
    else if ( position.y > 0 && i >  maxAppearTime-shrinkSpeed)
        position.y -=4;
    else if( position.y <= 0 || i >  maxAppearTime)
        reset(currentTime);
    pixMap->blendTex(position.x,position.y,1,1);
};

Moles::Moles()
{
    maxMole = 6;
    for (int i = 0; i < maxMole; ++i)
        member.push_back(Mole());
}
void Mole::reset(unsigned long time)
{
    hitted=false;
    pixMap =  state[ALIVE];
    position.y = 0;;
    position.x = rand()%screenWidth;
    startTime = time;
}


void Moles::display(unsigned long currentTime)
{
    for (int i = 0; i < member.size(); ++i)
    {
      //  cout << "moles : " << i << "  " ;
        member.at(i).display(currentTime);

    }
   //   cout  <<"========== \n";
}
Mole::~Mole(){
    	//delete pixMap;
	//	delete []  state;
}

Moles::~Moles(){
member.clear();
}

