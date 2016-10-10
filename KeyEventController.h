//
//  KeyEventController.h
//  2D Game Programming Tutorial
//
//  Created by UglyMan.nothinglo on 13/10/7.
//  Copyright (c) 2013¦~ UglyMan.nothinglo. All rights reserved.
//

#ifndef ___D_Game_Programming_Tutorial__KeyEventController__
#define ___D_Game_Programming_Tutorial__KeyEventController__

#include <iostream>

const unsigned int MAX_KEY_STATE = 256;
const unsigned int MAX_SPECIAL_KEY_STATE = 256;

class KeyEventController
{
private :
    bool keyState[MAX_KEY_STATE];
    bool specialKeyState[MAX_SPECIAL_KEY_STATE];
public :
    KeyEventController();
    void setKeyStateUp(const unsigned char k);
    void setSpecialKeyStateUp(const int k);
    void setKeyStateDown(const unsigned char k);
    void setSpecialKeyStateDown(const int k);
    const bool isKeyStateDown(const unsigned char k) const;
    const bool isSpecialKeyStateDown(const int k) const;
};

#endif /* defined(___D_Game_Programming_Tutorial__KeyEventController__) */
