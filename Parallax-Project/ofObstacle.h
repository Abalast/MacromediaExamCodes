#pragma once
#include "ofMain.h"

class ofObstacle
{
public: 
	ofRectangle rect; 
	float speed; 
	ofObstacle(float x, float y, float w, float h, float speed); 
	void update(); 
	void draw(); 
	bool isOffScreen();
};

