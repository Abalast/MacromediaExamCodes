#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup()
{
	ofSetFrameRate(60); 
	
	float markWidth = 10; 
	float markHeight = 40; 
	float spacing = 80; 
	// Space between road marks
	for (int i = 0; i < 10; i++) 
	{ 
		roadMarks.push_back(ofRectangle(ofGetWidth() / 2 - markWidth / 2, // middle of the screen 
			i * spacing, // move down with spacing
			markWidth, 
			markHeight 
		)); 
	}

	// Set player initial position
	player = ofRectangle(ofGetWidth()/2 - 20, ofGetHeight() - 80, 40, 40);

	// Pre-create a pool of obstacles
	for (int i = 0; i < 10; i++)
	{
		float w = ofRandom(40, 120);
		float h = 30;
		float x = ofRandom(0, ofGetWidth() - w);
		float y = -h;
		float speed = ofRandom(3, 7);
		obstacles.emplace_back(x, y, w, h, speed);
	}
}

//--------------------------------------------------------------
void ofApp::update()
{
	// Update road marks position with the Pooling design pattern. For more information, look it up.
	for (auto& m : roadMarks) 
	{
		m.y += markSpeed;
		// When the mark goes off the screen, reset its position to the top
		if (m.y > ofGetHeight())
		{
			m.y = -m.height;
		}
	}

	// Update obstacles movement using pooling
	for (auto& o : obstacles)
	{
		if (o.isActive())
		{
			o.update();
			// Reset obstacle position if it goes off-screen
			if (o.isOffScreen())
			{
				o.deactivate(); // Deactivate the obstacle instead of resetting
			}
		}
	}

	// Set obstacle spawn timer
	spawnTimer += ofGetLastFrameTime(); 
	if(spawnTimer > 1.0f)
	{
		// Activate an obstacle from the pool every second
		spawnObstacle(); 
		spawnTimer = 0; 
	} 
}

//--------------------------------------------------------------
void ofApp::draw(){
	ofBackground(30); 

	// Road marks
	ofSetColor(255);
	for (auto& m : roadMarks)
	{
		ofDrawRectangle(m);
	}

	//Player zeichnen 
	ofSetColor(0, 200, 255); 
	ofDrawRectangle(player);

	// Draw obstacles
	for(auto &o : obstacles)
	{ 
		o.draw(); 
	} 
}

void ofApp::spawnObstacle() 
{
	// Find an inactive obstacle in the pool and activate it
	for (auto& o : obstacles)
	{
		if (!o.isActive())
		{
			o.reset();
			break;
		}
	}
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}
