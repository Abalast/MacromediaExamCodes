#pragma once

#include "ofMain.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		//Possible Player character
		ofVec2f posPlayer;
		float playerRadius = 30;
		float velocityX = 1;
		float velocityY;

		//circle
		ofVec2f posB;
		float radiusB = 40;

		//Debug colors
		bool changeColor = false;
		bool changeRectColor = false;

		//For bouncing against shapes
		ofRectangle rectLeft;
		ofRectangle rectRight;

		//For checking if something is in shape
		ofVec2f mouse;
		ofRectangle rect;

		// My collision Handling codes
		bool CheckCollisionWithRectangle(ofVec2f pos, float posRadius, ofRectangle rect);
		bool CustomCollisionCheckWithTwoVectors(ofVec2f positionA, ofVec2f positionB, float radiusA, float radiusB);
		bool CheckWindowCollision(ofVec2f pos, float radius);
};
