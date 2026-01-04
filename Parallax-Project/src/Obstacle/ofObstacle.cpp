#include "ofObstacle.h"

ofObstacle::ofObstacle(float x, float y, float w, float h, float newSpeed)
{
    rect = ofRectangle(x, y, w, h);
    this->speed = newSpeed;
    active = false; // Initially inactive
}

void ofObstacle::update()
{
    if (active)
    {
        rect.y += speed; // Move down
    }
}

void ofObstacle::draw()
{
    if (active)
    {
        ofSetColor(255, 0, 0);
        ofDrawRectangle(rect);
    }
}

bool ofObstacle::isOffScreen()
{
    return rect.y > ofGetHeight();
}

bool ofObstacle::isActive() const
{
    return active;
}

void ofObstacle::activate(float x, float y, float newSpeed)
{
    rect.set(x, y, rect.getWidth(), rect.getHeight());
    speed = newSpeed;
    active = true;
}

void ofObstacle::deactivate()
{
	//Move it off-screen
    rect.set(3000, 3000, rect.getWidth(), rect.getHeight());
	speed = 0;
    active = false;
}

void ofObstacle::reset()
{

    float w = ofRandom(40, 120);
    float h = 30;
    float x = ofRandom(0, ofGetWidth() - w);
    float y = -h;
    float speed = ofRandom(3, 7);

    activate(x, y, speed); // Reset is essentially reactivating with new parameters
}
