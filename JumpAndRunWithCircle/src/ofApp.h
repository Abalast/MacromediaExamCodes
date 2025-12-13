#pragma once

#include "ofMain.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);

        //Collision
        void HandleWindowCollision();
		bool CheckCircleWithRectCollision(const ofRectangle& rect);
        void HandleCircleWithRectCollision(const ofRectangle& rect);

        float framerate = 60.0f;

        //Player 
        // Player Movement
        ofVec2f playerPos; //Player Position
        ofVec2f playerVel; //Player velocity
        float playerRadius = 25; // half of your old width/height
        bool isJumping;
        bool moveLeft, moveRight;
        bool onGround;
        float coyoteTime = 0.15f;   // 150 ms grace period
        float coyoteTimer = 0.0f;   // counts down when leaving ground


        //Player Animation
        ofImage playerSprite;
        bool facingLeft = false;


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
