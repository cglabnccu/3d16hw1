
#include "creature.h"
class enemy : public creature{
    public:
        int life;

        void form();
        void die();
        enemy();
        enemy(double xx,double yy);

        RGBApixmap pic;
        void setPic();

        void action();
        int direct;//1:right 0:left

};


