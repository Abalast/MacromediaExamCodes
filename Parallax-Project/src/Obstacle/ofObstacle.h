#include "ofMain.h"
#pragma once
class ofObstacle
{
public: 
	ofRectangle rect; 
	float speed; 
	bool active; // Tracks if the obstacle is active

	ofObstacle(float x, float y, float w, float h, float newSpeed); 
	void update(); 
	void draw(); 
	bool isOffScreen();

	// New methods for pooling
	bool isActive() const;
	void activate(float x, float y, float newSpeed);
	void deactivate();
	void reset();
};

