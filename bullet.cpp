#include "bullet.h"

bullet::bullet()
{
    setXY(-100,-100);
    setPic(1,1);
    powerFlag=1;
}
bullet::bullet(double xx,double yy)
{
    setXY(xx,yy);
    setPic(1,1);
    powerFlag=1;
}
void bullet::setPic(int p,int flag)
{
    if(p==1)
    {
        switch(flag)
        {
            case 1:
                pic.readBMPFile("image/bullet1_1.bmp");
                break;
            case 2:
                pic.readBMPFile("image/bullet1_2.bmp");
                break;
        }
    }
    else if (p==2)
    {
        switch(flag)
        {
            case 1:
                pic.readBMPFile("image/bullet2_1.bmp");
                break;
            case 2:
                pic.readBMPFile("image/bullet2_2.bmp");
                break;
        }
    }
}

void bullet::action(){if(this->x!=-100)this->y+=4;}
void bullet::die(){x=-100,y=-100;}

//pcbullet
pcbullet::pcbullet()
{
    setXY(-100,-100);
    setPic();
}
pcbullet::pcbullet(double xx,double yy)
{
    setXY(xx,yy);
    setPic();
}
void pcbullet::setPic()
{
    pic.readBMPFile("image/pcbullet.bmp");
}

void pcbullet::action(){if(x!=-100) y-=1;}

void pcbullet::die(){x=-100,y=-100;}
