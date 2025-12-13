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
	if (moveLeft)
		playerVel.x = -5;
	else if (moveRight)
		playerVel.x = 5;
	else
		playerVel.x = 0;

	// Apply gravity
	playerVel.y += gravity;
	playerPos += playerVel;

	for(auto& platform : platforms)

	onGround = false;
	// Platform collision

	for (auto& platform : platforms)
	{
		if (CheckCircleWithRectCollision(platform))
		{
			HandleCircleWithRectCollision(platform);
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
	// Draw circle player

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
	ofDrawCircle(playerPos.x, playerPos.y, playerRadius);

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
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
void ofApp::keyReleased(int key) {
	if (key == 'a') moveLeft = false;
	if (key == 'd') moveRight = false;
}

// A possible collision for Windows. It might make sense to split this into two functions so that you can check either X or Y.
void ofApp::HandleWindowCollision()
{
	// Clamp horizontal position
	if (playerPos.x < 0) playerPos.x = 0;
	if (playerPos.x > ofGetWidth() - playerRadius) playerPos.x = ofGetWidth() - playerRadius;

	if (playerPos.y > ofGetHeight()) {
		// Player has fallen below the screen — trigger respawn
		playerPos.set(playerRespawn); // Or wherever you want them to respawn
		playerVel.set(0, 0);
		isJumping = false;
	}
}

bool ofApp::CheckCircleWithRectCollision(const ofRectangle& rect) 
{
	//We get the closest point from playerPosition
    float closestX = ofClamp(playerPos.x, rect.getLeft(), rect.getRight()); 
    float closestY = ofClamp(playerPos.y, rect.getTop(), rect.getBottom());

	// offsetX = horizontal distance between the circle’s center and the closest point on the rectangle.
	// Positive if the circle is to the right of that point, negative if to the left.
    float offsetX = playerPos.x - closestX;

	// offsetY = vertical distance between the circle’s center and the closest point on the rectangle.
	// Positive if the circle is below that point, negative if above.
    float offsetY = playerPos.y - closestY;
	float distance = sqrt(offsetX * offsetX + offsetY * offsetY);

	//We check for distance
	return distance < playerRadius; 
}

// A function to handle collisions with circles and rectangles.
// This only works when the platform is axis-aligned.
void ofApp::HandleCircleWithRectCollision(const ofRectangle& rect) 
{
	//We get the closest point from playerPosition
	float closestX = ofClamp(playerPos.x, rect.getLeft(), rect.getRight());
	float closestY = ofClamp(playerPos.y, rect.getTop(), rect.getBottom());

	// offsetX = horizontal distance between the circle’s center and the closest point on the rectangle.
	// Positive if the circle is to the right of that point, negative if to the left.
	float offsetX = playerPos.x - closestX;

	// offsetY = vertical distance between the circle’s center and the closest point on the rectangle.
	// Positive if the circle is below that point, negative if above.
	float offsetY = playerPos.y - closestY;
	float distance = sqrt(offsetX * offsetX + offsetY * offsetY);

	// returns the absolute positive value. So if you have -5 when you use abs(5) it becomes 5
	// If offsetX is bigger then we know, that we need to check Horizontal collision. 
	// Otherwise it is Vertical collision.
	if (abs(offsetX) > abs(offsetY))  
	{
		// Horizontal collision
		if (offsetX > 0) 
			playerPos.x = rect.getRight() + playerRadius;
		else        
			playerPos.x = rect.getLeft() - playerRadius;
		playerVel.x = 0;
	}
	else {
		// Vertical collision
		if (offsetY > 0) {
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