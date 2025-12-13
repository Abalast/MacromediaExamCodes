#pragma once

#include "ofMain.h"
#include "ofSoundPlayer.h"
#include "ofImage.h"

class PlayerCharacter
{
public:
    //Player 
    // Player Movement
    ofVec2f playerPos; //Player Position
    ofVec2f playerVel; //Player velocity
    bool isJumping;
    bool moveLeft, moveRight;

    //Player Animation
    ofImage playerSprite;
    bool facingLeft = false;

    //PlayerCollision
    float playerWidth = 50;
    float playerHeight = 50;
    ofRectangle playerCollision = ofRectangle(playerPos.x, playerPos.y, playerWidth, playerHeight);

};

class ofApp : public ofBaseApp{

	public:
        void setup();
        void update();
        void draw();
        void keyPressed(int key);
        void keyReleased(int key);

        //Collision
        bool CheckVerticalCollision(const ofRectangle& rect);
        void HandleVerticalCollision(const ofRectangle& rect);

        bool CheckHorizontalCollision(const ofRectangle& rect);
        void HandleHorizontalCollision(const ofRectangle& rect);

        void HandleWindowCollision();

        float framerate = 60.0f;

        //Player 
        // Player Movement
        ofVec2f playerPos; //Player Position
        ofVec2f playerVel; //Player velocity
        bool isJumping;
        bool moveLeft, moveRight;
        bool onGround;
        float coyoteTime = 0.15f;   // 150 ms grace period
        float coyoteTimer = 0.0f;   // counts down when leaving ground


        //Player Animation
        ofImage playerSprite;
        bool facingLeft = false;

        //PlayerCollision
        float playerWidth = 50;
        float playerHeight = 50;
        ofRectangle playerCollision = ofRectangle(playerPos.x, playerPos.y, playerWidth, playerHeight);

        // Level Physic

        // Set the ground rectangle...
        // x y width height
        ofRectangle ground_rect, ground_col;
        float gravity;
        float groundY;

        // Level Elements
        //Possible Respawn for the player.
        ofVec2f playerRespawn;
        ofRectangle platform;
        std::vector<ofRectangle> platforms;

        // Sound
        ofSoundPlayer jumpSound;
        ofSoundPlayer landSound;

};


