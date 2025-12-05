#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	
	//Player character
	posPlayer.x = 100;
	posPlayer.y = 100;

	posPlayer = ofVec2f(100, 100);
	velocityX = 1;
	velocityY = 1;
	playerRadius = 30;

	// Circle
	posB = ofVec2f(350, 150);
	radiusB = 40;

	// Rectangle
	rectLeft = ofRectangle(20,50, 50,200);
	rectRight = ofRectangle(550, 50, 50, 200);

	// Bonus Rectangle
	rect = ofRectangle(100, 400, 200, 150);

}

//--------------------------------------------------------------
void ofApp::update(){

	//Simple game logic. Move the player
	posPlayer.x += velocityX;
	posPlayer.y += velocityY;
	mouse = ofVec2f(ofGetMouseX(), ofGetMouseY());

	//Collision logic examples 
	if (posPlayer.distance(posB) < playerRadius + radiusB) 
	{
		ofLog() << "Collision detected!";
		changeColor = true;
	}
	else 
	{
		changeColor = false;
	}

	if (rect.inside(mouse)) 
	{
		ofLog() << "Mouse inside rectangle!";
		changeRectColor = true;
	}
	else
	{
		changeRectColor = false;
	}

	if (CheckCollisionWithRectangle(posPlayer, playerRadius, rectLeft) || CheckCollisionWithRectangle(posPlayer, playerRadius, rectRight))
	{
		ofLog() << "Collision with wall!";
		velocityX *= -1;
	}

	if (CheckWindowCollision(posPlayer, playerRadius))
	{
		ofLog() << "Collision with wall!";
		velocityX *= -1;
		velocityY *= -1;
	}
}

//--------------------------------------------------------------
void ofApp::draw(){

	// Draw static rectangles (walls)
	ofSetColor(255);
	ofDrawRectangle(rectLeft);
	ofDrawRectangle(rectRight);

	// Draw player circle
	ofSetColor(215, 100, 140);
	ofDrawCircle(posPlayer, playerRadius);

	// Draw interactive rectangle
	if (changeRectColor) 
		ofSetColor(215, 100, 10);   // collision color
	else 
		ofSetColor(255);            // normal color

	ofDrawRectangle(rect);

	// Draw target circle
	if (changeColor) 
		ofSetColor(215, 200, 10);   // collision color
	else 
		ofSetColor(255);            // normal color

	ofDrawCircle(posB, radiusB);
}

// Perfect approach if you want to check a circle based object with a rectangle object
bool ofApp::CheckCollisionWithRectangle(ofVec2f pos, float posRadius ,ofRectangle rect)
{
	// Circle vs Rectangle (right wall)
	float closestX = ofClamp(pos.x, rect.getX(), rect.getX() + rect.getWidth());
	float closestY = ofClamp(pos.y, rect.getY(), rect.getY() + rect.getHeight());
	float distanceX = pos.x - closestX;
	float distanceY = pos.y - closestY;
	float distanceSquared = (distanceX * distanceX) + (distanceY * distanceY);

	return distanceSquared < (posRadius * posRadius);
}


// This approach is more Performant than using Distance
bool ofApp::CustomCollisionCheckWithTwoVectors(ofVec2f positionA, ofVec2f positionB, float radiusA, float radiusB)
{
	float dx = positionA.x - positionB.x;
	float dy = positionA.y - positionB.y;
	float distanceSquared = dx * dx + dy * dy;

	float radiusSum = radiusA + radiusB;
	float radiusSumSquared = radiusSum * radiusSum;

	return distanceSquared < radiusSumSquared;
}

// A possible collision for Windows. It might make sense to split this into two functions so that you can check either X or Y.
bool ofApp::CheckWindowCollision(ofVec2f pos, float radius)
{
	bool collided = false;

	if (pos.x - radius < 0 || pos.x + radius > ofGetWidth()) {
		collided = true;
	}
	if (pos.y - radius < 0 || pos.y + radius > ofGetHeight()) {
		collided = true;
	}

	return collided;
}
