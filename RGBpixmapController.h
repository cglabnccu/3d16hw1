//
//  RGBpixmapController.h
//  2D Game Programming Tutorial
//
//  Created by UglyMan.nothinglo on 13/10/7.
//  Copyright (c) 2013¦~ UglyMan.nothinglo. All rights reserved.
//

#ifndef ___D_Game_Programming_Tutorial__RGBpixmapController__
#define ___D_Game_Programming_Tutorial__RGBpixmapController__

#include <iostream>
#include <vector>
#include <map>
#include "RGBpixmap.h"
#include "Vec3.h"

using namespace std;

class RGBpixmapController {
public:
    void loadRGBpixmapAdvance(const vector<string> & paths,
                              const Vec3 chromaKey = Vec3(-1, -1, -1));
    RGBApixmap * getRGBpixmap(const char * path,
                              const Vec3 chromaKey = Vec3(-1, -1, -1));
    RGBApixmap * getRGBpixmap(const string path,
                              const Vec3 chromaKey = Vec3(-1, -1, -1));
    const bool isPixmapMatchPath(const RGBApixmap *pixmap, const char * path);
    const bool isPixmapMatchPath(const RGBApixmap *pixmap, const string path);
private:
    static RGBpixmapController* controllerInstance;
    static RGBpixmapController* Instance();
    map<string, RGBApixmap> database;
};

#endif /* defined(___D_Game_Programming_Tutorial__RGBpixmapController__) */
