#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	ofSetWindowTitle("Jump and Run with Circle");
	ofSetFrameRate(framerate);

	playerRespawn.set(100, 300);
	playerPos.set(playerRespawn);
	playerVel.set(0, 0);
	gravity = 0.8;
	isJumping = false;
	moveLeft = moveRight = false;

	playerSprite.load("images/player.png");
	playerSprite.setImageType(OF_IMAGE_COLOR_ALPHA);

	//Level elements
	ground_rect.set(0, 1035, 1920, 50);
	ground_col.set(80, 70, 30, 255);

	//platforms.push_back(ofRectangle(playerPos.x - 25, playerPos.y + playerHeight, 200, 20));
	platforms.push_back(ofRectangle(30, 450, 200, 20));
	platforms.push_back(ofRectangle(400, 400, 150, 20));
	platforms.push_back(ofRectangle(700, 300, 180, 20));
	platforms.push_back(ofRectangle(300, 950, 200, 20));
	platforms.push_back(ofRectangle(500, 850, 200, 20));
	platforms.push_back(ofRectangle(800, 750, 200, 20));
	platforms.push_back(ofRectangle(200, 550, 200, 20));
	platforms.push_back(ofRectangle(500, 650, 200, 20));
	platforms.push_back(ground_rect);



	jumpSound.load("sounds/jump.mp3");
	//landSound.load("land.wav");
	jumpSound.setMultiPlay(true); // allows overlapping sounds
	landSound.setMultiPlay(true);
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
	// Draw circle player
	ofSetColor(255);
	ofDrawCircle(playerPos.x, playerPos.y, playerRadius);

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

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

void ofApp::HandleCircleRectCollision(const ofRectangle& rect) {
    float closestX = ofClamp(playerPos.x, rect.getLeft(), rect.getRight());
    float closestY = ofClamp(playerPos.y, rect.getTop(), rect.getBottom());

    float dx = playerPos.x - closestX;
    float dy = playerPos.y - closestY;

    if (abs(dx) > abs(dy)) {
        // Horizontal collision
        if (dx > 0) playerPos.x = rect.getRight() + playerRadius;
        else        playerPos.x = rect.getLeft() - playerRadius;
        playerVel.x = 0;
    }
    else {
        // Vertical collision
        if (dy > 0) {
            // Player above platform
            playerPos.y = rect.getBottom() + playerRadius;
        }
        else {
            // Player landed on top
            playerPos.y = rect.getTop() - playerRadius;
            onGround = true;
            isJumping = false;
        }
        playerVel.y = 0;
    }
}
