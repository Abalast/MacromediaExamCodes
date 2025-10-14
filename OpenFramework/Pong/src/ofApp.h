#pragma once

#include "ofMain.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);

		//Pong variable

		// Ball values
		ofVec2f ballPos, ballVel;
		float ballRadius;

		//Paddle
		float paddleWidth, paddleHeight;
		ofVec2f leftPaddlePos, rightPaddlePos;
		float paddleSpeed;

		//Score
		int leftScore, rightScore;

		//controls
		bool wPressed, sPressed;
		bool upPressed, downPressed;
		
};
