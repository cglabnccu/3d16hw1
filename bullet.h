
#include "creature.h"
class bullet : public creature{
    public:
        int powerFlag;
        bullet();
        bullet(double xx,double yy);
        void setPic(int,int);
        RGBApixmap pic;

        void action();
        void die();

};

class pcbullet : public creature{
    public:
        pcbullet();
        pcbullet(double xx,double yy);
        void setPic();
        RGBApixmap pic;
        void action();
        void die();
};
