#pragma once

#include "ofMain.h"

class Bullet {
public:
    ofVec2f pos;
    float speed;

    Bullet(ofVec2f startPos, float speed = 10) : pos(startPos), speed(speed) {}

    virtual void update() {
        pos.y -= speed;
    }

    virtual void draw() {
        ofSetColor(255); // default color
        ofDrawCircle(pos, 5);
    }
};

class EnemyBullet : public Bullet {
public:
    EnemyBullet(ofVec2f startPos) : Bullet(startPos, 5) {}

    void update() override {
        pos.y += speed; // move downward
    }

    void draw() override {
        ofSetColor(255, 0, 0); // red bullet
        ofDrawCircle(pos, 5);
    }
};

class Enemy {
public:
    ofVec2f pos;
    bool alive = true;
    float speed = 2;

    Enemy(float x, float y) : pos(x, y) {}

    void update() {
        pos.x += speed;
    }

    void bounce() {
        speed *= -1;
        pos.y += 20;
    }

    void draw() {
        if (alive) ofDrawRectangle(pos.x, pos.y, 30, 20);
    }
};

class ofApp : public ofBaseApp {
public:
    void setup();
    void update();
    void draw();

    void keyPressed(int key);
    void keyReleased(int key);

    // Game logic
    void spawnEnemies();
    void resetGame();
    bool checkCollision(const ofVec2f& a, const ofVec2f& b, float radius = 20.0f);

    // Player
    ofVec2f playerPos;
    float playerSpeed = 5;
    bool moveLeft = false;
    bool moveRight = false;
    uint64_t lastShotTime = 0;
    uint64_t fireDelay = 300;

    // Bullets
    vector<Bullet> bullets;
    vector<EnemyBullet> enemyBullets;

    // Enemies
    vector<Enemy> enemies;
    uint64_t lastEnemyShotTime = 0;
    uint64_t enemyFireDelay = 1000;

    // Sounds
    ofSoundPlayer playerShootSound;
    ofSoundPlayer enemyShootSound;
    ofSoundPlayer explosionSound;

    // Game state
    bool gameOver = false;
    bool gameWon = false;
    uint64_t gameOverTime = 0;
    uint64_t restartDelay = 3000;
};
