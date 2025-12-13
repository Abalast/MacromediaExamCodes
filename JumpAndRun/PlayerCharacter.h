#pragma once
#include "ofMain.h"

class PlayerCharacter
{
    ofVec2f playerPos;
    ofVec2f playerVel;
    float gravity;
    bool isJumping;
    bool moveLeft, moveRight;
};

