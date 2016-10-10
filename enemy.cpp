#include "enemy.h"
enemy::enemy()
{
    setXY(-100,-100);
    direct=0;
    life=50;
    setPic();
}
enemy::enemy(double xx,double yy)
{
    setXY(xx,yy);
    direct=0;
    life=50;
    setPic();
}
void enemy::setPic()
{
    pic.readBMPFile("image/enemy.bmp");
}

void enemy::action()
{

    /*int n=rand();
    if(rand()%10==0) direct=(direct==0)?1:0;
    x=(direct==0)?x-2*( (n%1000)/200 +1):x+2*( (n%1000)/200 +1);
    if(x<=50)x=0;
    else if(x>=750)x=750;
    setXY(x,y);*/
}
void enemy::die()
{
    x=-100,y=-100;
}
void enemy::form()
{
    x=rand()%761;
    y=rand()%201+360;
    life=rand()%40;
}
