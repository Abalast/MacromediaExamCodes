#pragma once

#include "ofMain.h"
#include "Obstacle/ofObstacle.h"

class ofApp : public ofBaseApp{

public: 
	void setup(); 
	void update(); 
	void draw(); 
	void spawnObstacle();
	vector<ofObstacle> obstacles;

	ofRectangle player; 
	float spawnTimer = 0;

	void keyPressed(int key);
	void keyReleased(int key);

	vector<ofRectangle> roadMarks;
	float markSpeed = 5.0f;


};
