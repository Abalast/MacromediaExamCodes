#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

	ofSetWindowTitle("Jump and Run");
	ofSetFrameRate(framerate);

	playerWidth = 50;
	playerHeight = 50;
	playerRespawn.set(100, 300);
	playerPos.set(playerRespawn);
	playerVel.set(0, 0);
	gravity = 0.8;
	isJumping = false;
	moveLeft = moveRight = false;
	groundY = ofGetHeight() - playerHeight;

	//PlayerCollision
	ofRectangle playerCollision(playerPos.x, playerPos.y, playerWidth, playerHeight);
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

	if (moveLeft) 
		playerVel.x = -5;
	else if (moveRight) 
		playerVel.x = 5;
	else 
		playerVel.x = 0;

	// Platform collision
	for (auto& platform : platforms) 
	{
		if (CheckHorizontalCollision(platform))
		{
			HandleHorizontalCollision(platform);
			break;
		}
	}

	// Apply gravity
	playerVel.y += gravity;
	playerPos += playerVel;

	onGround = false;
	// Platform collision
	for (auto& platform : platforms) 
	{
		if (CheckVerticalCollision(platform))
		{
			HandleVerticalCollision(platform);
			onGround = true;
			break;
		}
	}

	//Code example for coyote-jump
	if (onGround) {
		isJumping = false;
		coyoteTimer = coyoteTime; // reset grace period
	}
	else {
		// falling or in air
		if (coyoteTimer > 0) {
			coyoteTimer -= 1.0f / framerate; // assuming 60 fps
		}
		else {
			isJumping = true; // grace expired
		}
	}

	HandleWindowCollision();
}

//--------------------------------------------------------------
void ofApp::draw(){
	ofBackground(135, 206, 235); // Sky blue



	ofSetColor(0, 150, 0); // Green platform
	ofDrawRectangle(platform);

	ofSetColor(0, 155, 0);
	for (auto& platform : platforms) {
		ofDrawRectangle(platform);
	}

	ofSetColor(101, 67, 33); // ground
	ofDrawRectangle(ground_rect);

	//Player 
	ofEnableAlphaBlending();
	ofSetColor(255); // Full white, no tint

	if (facingLeft) {
		ofPushMatrix();
		ofTranslate(playerPos.x + playerWidth, playerPos.y); // shift origin to right edge
		ofScale(-1, 1); // flip horizontally
		playerSprite.draw(0, 0, playerWidth, playerHeight);
		ofPopMatrix;
	}
	else {
		playerSprite.draw(playerPos.x, playerPos.y, playerWidth, playerHeight);
	}
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	if (key == 'a')
	{
		moveLeft = true;
		facingLeft = true;
	}
	if (key == 'd')
	{
		facingLeft = false;
		moveRight = true;
	}
	if (key == ' ' && !isJumping) {
		playerVel.y = -15;
		isJumping = true;
		coyoteTimer = 0; // consume grace
		jumpSound.play();
	}
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
	if (key == 'a') moveLeft = false;
	if (key == 'd') moveRight = false;
}


bool ofApp::CheckVerticalCollision(const ofRectangle& rect) 
{
	ofRectangle playerBox(playerPos.x, playerPos.y, playerWidth, playerHeight);
	return playerBox.intersects(rect);
}

void ofApp::HandleVerticalCollision(const ofRectangle& rect)
{
	float playerBottom = playerPos.y + playerHeight;
	float playerTop = playerPos.y;
	float rectTop = rect.getY();
	float rectBottom = rect.getY() + rect.getHeight();

	if (playerVel.y > 0 && playerBottom >= rectTop && playerTop < rectTop) {
		playerPos.y = rectTop - playerHeight;
		playerVel.y = 0;
		isJumping = false;
	}
	else if (playerVel.y < 0 && playerTop <= rectBottom && playerBottom > rectBottom) {
		playerPos.y = rectBottom;
		playerVel.y = 0;
	}
}

bool ofApp::CheckHorizontalCollision(const ofRectangle& rect) 
{
	ofRectangle playerBox(playerPos.x, playerPos.y, playerWidth, playerHeight);
	return playerBox.intersects(rect);
}

void ofApp::HandleHorizontalCollision(const ofRectangle& rect)
{
	float playerLeft = playerPos.x;
	float playerRight = playerPos.x + playerWidth;
	float rectLeft = rect.x;
	float rectRight = rect.x + rect.getWidth();

	if (playerVel.x > 0 && playerRight >= rectLeft && playerLeft < rectLeft)
	{
		playerPos.x = rectLeft - playerWidth;
	}
	else if (playerVel.x < 0 && playerLeft <= rectRight && playerRight > rectRight)
	{
		playerPos.x = rectRight;
	}
}

// A possible collision for Windows. It might make sense to split this into two functions so that you can check either X or Y.
void ofApp::HandleWindowCollision()
{
	// Clamp horizontal position
	if (playerPos.x < 0) playerPos.x = 0;
	if (playerPos.x > ofGetWidth() - playerWidth) playerPos.x = ofGetWidth() - playerWidth;

	if (playerPos.y > ofGetHeight()) {
		// Player has fallen below the screen — trigger respawn
		playerPos.set(playerRespawn); // Or wherever you want them to respawn
		playerVel.set(0, 0);
		isJumping = false;
	}
}