#include "mole.h"
#include <ctime>
#include <cstdlib>

Mole::Mole()
{

    chromaKey.x = 255;
    chromaKey.y=255;
    chromaKey.z=255;
    vector<char*> molePicLocation ;
#define ALIVE 0
#define DEAD 1
#define FLOWER 2
    molePicLocation.push_back("image/mole1.bmp");
    molePicLocation.push_back("image/mole2.bmp");
    molePicLocation.push_back("image/flower.bmp");
    RGBpixmapController controller ;
    state[ALIVE] = controller.getRGBpixmap(molePicLocation[ALIVE],chromaKey);
    state[DEAD] = controller.getRGBpixmap(molePicLocation[DEAD],chromaKey);
    state[FLOWER] = controller.getRGBpixmap(molePicLocation[FLOWER],chromaKey);

    reset(0);
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
    else if(hitted)
    {
        if(!isFlower)
            pixMap =  state[DEAD];
        if (position.y >0 )
            position.y-=3;
        else
            reset(currentTime);
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
    maxAppearTime= 5000+rand()%2000;
    hitted=false;
    if(rand()%6==2)
    {
        pixMap= state[FLOWER];
        isFlower = true;
    }
    else
    {
        pixMap= state[ALIVE];
        isFlower = false;
    }
    position.y = 0;;
    position.x = rand()%(screenWidth-70);
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
Mole::~Mole() {}


Moles::~Moles()
{
    member.clear();
}

