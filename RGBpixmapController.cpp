//
//  RGBpixmapController.cpp
//  2D Game Programming Tutorial
//
//  Created by UglyMan.nothinglo on 13/10/7.
//  Copyright (c) 2013¦~ UglyMan.nothinglo. All rights reserved.
//

#include "RGBpixmapController.h"

RGBpixmapController * RGBpixmapController::controllerInstance = NULL;

RGBpixmapController * RGBpixmapController::Instance()
{
    if(controllerInstance == NULL)
    {
        controllerInstance = new RGBpixmapController;
    }
    return controllerInstance;
}

void RGBpixmapController::loadRGBpixmapAdvance(const vector<string> & paths, const Vec3 chromaKey)
{
    for(unsigned int i = 0; i < paths.size(); ++i)
    {
        getRGBpixmap(paths[i], chromaKey);
    }
}
RGBApixmap * RGBpixmapController::getRGBpixmap(const char * path, Vec3 chromaKey)
{
    return getRGBpixmap(string(path), chromaKey);
}
RGBApixmap * RGBpixmapController::getRGBpixmap(const string path, Vec3 chromaKey)
{
    map<string, RGBApixmap> & data = Instance() -> database;
    map<string, RGBApixmap>::iterator it = data.find(path);
    if (it == data.end())
    {
        RGBApixmap pixmap;
        pixmap.readBMPFile(path);
        if(chromaKey.x != -1)
        {
            pixmap.setChromaKey(chromaKey.x, chromaKey.y, chromaKey.z);
        }
        data.insert(make_pair(path, pixmap));
        return &data[path];
    }
    else
    {
        return &(it -> second);
    }
}
const bool RGBpixmapController::isPixmapMatchPath(const RGBApixmap *pixmap, const char * path)
{
    return (pixmap == getRGBpixmap(path));
}
const bool RGBpixmapController::isPixmapMatchPath(const RGBApixmap *pixmap, const string path)
{
    return (pixmap == getRGBpixmap(path));
}
