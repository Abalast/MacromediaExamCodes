#pragma once

#include "ofMain.h"

class ofApp : public ofBaseApp{

public:
	void setup();
	void update();
	void draw();

	void keyPressed(int key);
	void keyReleased(int key);

	//Pong variable

	// Ball values
	ofVec2f ballPos; 
	ofVec2f ballVel;
	float ballRadius;

	//Paddle
	float paddleWidth, paddleHeight;
	ofRectangle leftPaddle, rightPaddle;
	ofVec2f leftPaddlePos, rightPaddlePos;
	float paddleSpeed;

	//Score
	int leftScore, rightScore;

	//controls
	bool wPressed, sPressed;
	bool upPressed, downPressed;

	//Collision Function
	void HandleCollision();
	bool CheckCollisionWithRectangle(ofVec2f pos, float posRadius, ofRectangle rect);
	bool CheckWindowCollision(ofVec2f pos, float radius);
		
};
