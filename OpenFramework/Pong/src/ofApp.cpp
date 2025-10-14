#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
   
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

    // Bounce off top/bottom
    if (ballPos.y < ballRadius || ballPos.y > ofGetHeight() - ballRadius)
        ballVel.y *= -1;

    // Left paddle collision
    if (ballPos.x - ballRadius < leftPaddlePos.x + paddleWidth && ballPos.y > leftPaddlePos.y && ballPos.y < leftPaddlePos.y + paddleHeight)
        ballVel.x *= -1;

    // Right paddle collision
    if (ballPos.x + ballRadius > rightPaddlePos.x && ballPos.y > rightPaddlePos.y && ballPos.y < rightPaddlePos.y + paddleHeight)
        ballVel.x *= -1;

    if (wPressed) 
        leftPaddlePos.y -= paddleSpeed;
    if (sPressed) 
        leftPaddlePos.y += paddleSpeed;

    // Simple AI: move right paddle toward ball
    if (ballPos.y < rightPaddlePos.y + paddleHeight / 2)
        rightPaddlePos.y -= paddleSpeed;
    else if (ballPos.y > rightPaddlePos.y + paddleHeight / 2)
        rightPaddlePos.y += paddleSpeed;

    // Score check
    if (ballPos.x < 0) {
        rightScore++;
        ballPos.set(ofGetWidth() / 2, ofGetHeight() / 2);
    }
    else if (ballPos.x > ofGetWidth()) {
        leftScore++;
        ballPos.set(ofGetWidth() / 2, ofGetHeight() / 2);
    }
}

//--------------------------------------------------------------
void ofApp::draw() {
    ofDrawCircle(ballPos, ballRadius);
    ofDrawRectangle(leftPaddlePos.x, leftPaddlePos.y, paddleWidth, paddleHeight);
    ofDrawRectangle(rightPaddlePos.x, rightPaddlePos.y, paddleWidth, paddleHeight);

    ofDrawBitmapString("Left: " + ofToString(leftScore), 20, 20);
    ofDrawBitmapString("Right: " + ofToString(rightScore), ofGetWidth() - 100, 20);
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
void ofApp::keyReleased(int key){
    if (key == 'w') 
        wPressed = false;
    if (key == 's') 
        sPressed = false;
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
