#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

    //Menu
    ofSetWindowTitle("Pong in openFrameworks");
    ofSetFrameRate(60);

    // Ball variable
    ballRadius = 10;
    ballPos.set(ofGetWidth() / 2, ofGetHeight() / 2);
    ballVel.set(5, 3);

    // paddle variable
    paddleWidth = 10;
    paddleHeight = 80;
    paddleSpeed = 5;

    // Control
    leftPaddlePos.set(30, ofGetHeight() / 2 - paddleHeight / 2);
    rightPaddlePos.set(ofGetWidth() - 40, ofGetHeight() / 2 - paddleHeight / 2);

    leftPaddle = ofRectangle(leftPaddlePos.x, leftPaddlePos.y, paddleWidth, paddleHeight);
    rightPaddle = ofRectangle(rightPaddlePos.x, rightPaddlePos.y, paddleWidth, paddleHeight);

    wPressed = false;
    sPressed = false;
    upPressed = false;
    downPressed = false;

    // Score
    leftScore = rightScore = 0;
}

//--------------------------------------------------------------
void ofApp::update() {
    ballPos += ballVel;

    HandleCollision();

    //if (wPressed)
    //    leftPaddle.y -= paddleSpeed;
    //if (sPressed)
    //    leftPaddle.y += paddleSpeed;

    if (wPressed)
    {
        float targetY = leftPaddle.y - paddleSpeed;
        leftPaddle.y = ofLerp(rightPaddle.y, targetY, 1);  
    }

    if (sPressed)
    {
        float targetY = leftPaddle.y + paddleSpeed;
        leftPaddle.y = ofLerp(rightPaddle.y, targetY, 1);
    }

    // Simple AI: move right paddle toward ball
    if (ballPos.y < rightPaddle.y + paddleHeight / 2)
    {
        float targetY = ballPos.y - paddleHeight / 2;
        rightPaddle.y = ofLerp(rightPaddle.y, targetY, 0.05); //Lerp is used to make the movement of the AI more smooth. For more information look up interpolation.
    }
    else if (ballPos.y > rightPaddle.y + paddleHeight / 2)
    {
        float targetY = ballPos.y + paddleHeight / 2;
        rightPaddle.y = ofLerp(rightPaddle.y, targetY, 0.05);
    }

    // Score check
    if (ballPos.x < 0) {
        rightScore++;
        ballPos.set(ofGetWidth() / 2, ofGetHeight() / 2);
        ballVel.set(ofRandom(-5, 5), ofRandom(-3, 3));
    }
    else if (ballPos.x > ofGetWidth()) {
        leftScore++;
        ballPos.set(ofGetWidth() / 2, ofGetHeight() / 2);
        ballVel.set(ofRandom(3, 5) * (ofRandom(1) > 0.5 ? 1 : -1), ofRandom(-3, 3));
    }
}

//--------------------------------------------------------------
void ofApp::draw() {
    ofDrawCircle(ballPos, ballRadius);
    ofDrawRectangle(leftPaddle);
    ofDrawRectangle(rightPaddle);

    ofDrawBitmapString("Left: " + ofToString(leftScore), 20, 20);
    ofDrawBitmapString("Right: " + ofToString(rightScore), ofGetWidth() - 100, 20);

    ofDrawLine(ofGetWidth() / 2, 0, ofGetWidth() / 2, ofGetHeight());
}

//--------------------------------------------------------------

void ofApp::keyPressed(int key) {
    if (key == 'w')
        wPressed = true;
    if (key == 's')
        sPressed = true;
    if (key == OF_KEY_UP)
        upPressed = true;
    if (key == OF_KEY_DOWN)
        downPressed = true;
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key) {
    if (key == 'w')
        wPressed = false;
    if (key == 's')
        sPressed = false;
}

void ofApp::HandleCollision()
{
    // Bounce off top/bottom
    if (CheckWindowCollision(ballPos, ballRadius))
        ballVel.y *= -1;

    // Left paddle collision
    if (CheckCollisionWithRectangle(ballPos, ballRadius, leftPaddle))
        ballVel.x *= -1;

    // Right paddle collision
    if (CheckCollisionWithRectangle(ballPos, ballRadius, rightPaddle))
        ballVel.x *= -1;

    // Just making sure, that the paddles leaves the window.
    leftPaddle.y = ofClamp(leftPaddle.y, 0, ofGetHeight() - paddleHeight);
    // Just making sure, that the paddles leaves the window.
    rightPaddle.y = ofClamp(rightPaddle.y, 0, ofGetHeight() - paddleHeight);
}

bool ofApp::CheckCollisionWithRectangle(ofVec2f pos, float posRadius, ofRectangle rect)
{
    // Circle vs Rectangle (right wall)
    float closestX = ofClamp(pos.x, rect.getX(), rect.getX() + rect.getWidth());
    float closestY = ofClamp(pos.y, rect.getY(), rect.getY() + rect.getHeight());
    float distanceX = pos.x - closestX;
    float distanceY = pos.y - closestY;
    float distanceSquared = (distanceX * distanceX) + (distanceY * distanceY);

    return distanceSquared < (posRadius * posRadius);
}

// A possible collision for Windows. It might make sense to split this into two functions so that you can check either X or Y.
bool ofApp::CheckWindowCollision(ofVec2f pos, float radius)
{
    bool collided = false;

    if (pos.y - radius < 0 || pos.y + radius > ofGetHeight()) 
    {
        collided = true;
    }

    return collided;
}