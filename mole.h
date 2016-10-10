#ifndef _MOLE_H
#define _MOLE_H

#include "RGBpixmapController.h"
#include "Vec3.h"
#include "RGBpixmap.h"
#include <vector>
#include "Timer.h"
extern int screenWidth ;
extern int screenHeight ;
extern int initialHeight;
extern int GAME_ONE_SHOT_TIME;


class Mole{
	public :
		Vec3 position;
		Vec3 chromaKey;
		RGBApixmap* pixMap;
		RGBApixmap* state[3];
        unsigned long startTime;
		unsigned long maxAppearTime;
		bool hitted;
		bool isFlower;

		Mole();
		void display(unsigned long);
		void reset(unsigned long time);
		~Mole();

};
class Moles{
private:

    int maxMole;
public:
    vector<Mole> member;
		void display(unsigned long);
    Moles();
    ~Moles();
};


#endif
