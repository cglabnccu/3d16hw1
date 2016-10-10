#ifndef CREATURE_H_INCLUDED
#define CREATURE_H_INCLUDED

#include<iostream>
#include "RGBpixmap.h"
class creature{
    public:
        RGBApixmap pic;
        virtual void setPic(){;}

        double getX(){return x;}
        double getY(){return y;}
        void setXY(double xx,double yy){x=xx,y=yy;}
    protected:
        double x;
        double y;
};

#endif // CREATURE_H_INCLUDED




