#include "creature.h"

class power:public creature{
public:
    power();
    power(double,double);
    double speedY;
    void setPic();
    void action();
    void die();
    void form(double,double);

};
