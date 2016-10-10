
#include "creature.h"
class player : public creature{
    public:
        player();
        player(double xx,double yy);

        int no;
        void setPic(int n);


        //move
        int directXY[4];//up down left right
        int slowMotion;
        int shooting;
        void setPosition();

        int hearts;
        int power;
};



