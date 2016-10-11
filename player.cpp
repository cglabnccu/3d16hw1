#include<iostream>

#include "player.h"
#include "RGBpixmap.h"

player::player()
{
    setXY(-100,-100);
    no=1;
    slowMotion=0;
    for(int i=0;i<4;i++) directXY[i]=0;
    shooting=0;
    setPic(no);
    hearts=5;
    power=0;
}
player::player(double xx,double yy)
{
    setXY(xx,yy);
    no=1;
    slowMotion=0;
    for(int i=0;i<4;i++) directXY[i]=0;
    shooting=0;
    setPic(no);
    hearts=5;
    power=0;
}

void player::setPic(int no)
{
    switch(no)
    {
        case 1:
            pic.readBMPFile("image/player1.bmp");  cout<<'.';
            break;
        case 2:
            pic.readBMPFile("image/player2.bmp");  cout<<'.';
            break;
    }
}

void player::setPosition()
{

    if(directXY[0]==1)
        y+=(2-1*slowMotion);
    if(directXY[1]==1)
        y-=(2-1*slowMotion);
    if(directXY[2]==1)
        x-=(2-1*slowMotion);
    if(directXY[3]==1)
        x+=(2-1*slowMotion);
    if(x<=4)x=4;
    else if(x>=764)x=764;

    if(y<=0)y=0;
    else if(y>536)y=536;
}


