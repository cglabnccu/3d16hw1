//
//  KeyEventController.cpp
//  2D Game Programming Tutorial
//
//  Created by UglyMan.nothinglo on 13/10/7.
//  Copyright (c) 2013¦~ UglyMan.nothinglo. All rights reserved.
//

#include "KeyEventController.h"

KeyEventController::KeyEventController()
{
    for(unsigned int i = 0; i < MAX_KEY_STATE; ++i)
        keyState[i] = false;
    for(unsigned int i = 0; i < MAX_SPECIAL_KEY_STATE; ++i)
        specialKeyState[i] = false;
}
void KeyEventController::setKeyStateUp(const unsigned char k)
{
    keyState[k] = false;
}
void KeyEventController::setSpecialKeyStateUp(const int k)
{
    specialKeyState[k] = false;
}
void KeyEventController::setKeyStateDown(const unsigned char k)
{
    keyState[k] = true;
}
void KeyEventController::setSpecialKeyStateDown(const int k)
{
    specialKeyState[k] = true;
}
const bool KeyEventController::isKeyStateDown(const unsigned char k) const
{
    return keyState[k];
}
const bool KeyEventController::isSpecialKeyStateDown(const int k) const
{
    return specialKeyState[k];
}
