#include"power.h"
power::power()
{
    x=-100,y=-100;
    speedY=3;
    setPic();
}
power::power(double xx,double yy)
{
    x=xx,y=yy;
    speedY=3;
    setPic();
}
void power::setPic()
{
    pic.readBMPFile("image/power.bmp");
}
void power::action()
{
    if(x!=-100)
    {
        y+=(speedY+speedY-0.05)*0.008/2;
        speedY-=0.8;
    }
}
void power::die()
{
    x=-100,y=-100;
}
void power::form(double xx,double yy)
{
    speedY=3;
    x=xx+rand()%201-100;
    y=yy+rand()%201-100;
    if(x>785)x=785;
    if(x<5)x=5;
    if(y>585)y=585;
}

