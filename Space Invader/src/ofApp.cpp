#include "ofApp.h"

// Utility function for collision detection
bool ofApp::checkCollision(const ofVec2f& a, const ofVec2f& b, float radius) {
    return ofDist(a.x, a.y, b.x, b.y) < radius;
}

void ofApp::setup() {
    ofSetWindowTitle("Space Invaders");
    ofSetFrameRate(60);
    playerPos.set(ofGetWidth() / 2, ofGetHeight() - 50);
    spawnEnemies();

    // Load sounds
    playerShootSound.load("sound/shoot.mp3");
    enemyShootSound.load("sound/enemyShot.mp3");
    explosionSound.load("sound/explosion.mp3");
}

void ofApp::update() {
    uint64_t timer = ofGetElapsedTimeMillis();

    // Restart game after win or loss
    if ((gameOver || gameWon) && timer - gameOverTime >= restartDelay) {
        resetGame();
    }

    // Player movement
    if (moveLeft) 
        playerPos.x -= playerSpeed;
    if (moveRight) 
        playerPos.x += playerSpeed;

    //Makes sure, player does not leave window
    playerPos.x = ofClamp(playerPos.x, 15, ofGetWidth() - 15);

    // Update player bullets
    for (auto& bullet : bullets) 
        bullet.update();

    // Enemy update and collision
    bool bounceNeeded = false;
    for (auto& enemy : enemies) {
        if (!enemy.alive) 
            continue;

        for (auto& bullet : bullets) {
            if (checkCollision(bullet.pos, enemy.pos + ofVec2f(15, 10), 20)) {
                enemy.alive = false;
                bullet.pos.y = -100;
                explosionSound.play();
                break;
            }
        }

        enemy.update();
        if (enemy.pos.x < 0 || enemy.pos.x > ofGetWidth() - 30) 
            bounceNeeded = true;
    }

    if (bounceNeeded) {
        for (auto& enemy : enemies) enemy.bounce();
    }

    // Enemy shooting
    if (timer - lastEnemyShotTime >= enemyFireDelay) {
        vector<Enemy*> aliveEnemies;
        for (auto& e : enemies) if (e.alive) aliveEnemies.push_back(&e);

        if (!aliveEnemies.empty() && !gameOver && !gameWon) {
            int index = ofRandom(aliveEnemies.size());
            ofVec2f bulletPos = aliveEnemies[index]->pos + ofVec2f(15, 20);
            enemyBullets.push_back(EnemyBullet(bulletPos));
            enemyShootSound.play();
            lastEnemyShotTime = timer;
        }
    }

    // Win condition
    if (!gameWon && std::all_of(enemies.begin(), enemies.end(), [](Enemy& e) { return !e.alive; })) {
        gameWon = true;
        gameOverTime = timer;
    }

    // Enemy bullet update and player collision
    for (auto& bullet : enemyBullets) {
        bullet.update();
        if (!gameOver && !gameWon && checkCollision(bullet.pos, playerPos, 20)) {
            explosionSound.play();
            gameOver = true;
            gameOverTime = timer;
            bullet.pos.y = ofGetHeight() + 100;
        }
    }

    // Remove off-screen bullets
    bullets.erase(remove_if(bullets.begin(), bullets.end(),
        [](Bullet& b) { return b.pos.y < 0; }), bullets.end());

    enemyBullets.erase(remove_if(enemyBullets.begin(), enemyBullets.end(),
        [](EnemyBullet& b) { return b.pos.y > ofGetHeight(); }), enemyBullets.end());
}

void ofApp::draw() {
    ofBackground(0);

    if (gameOver) {
        ofSetColor(255, 0, 0);
        ofDrawBitmapString("GAME OVER", ofGetWidth() / 2 - 50, ofGetHeight() / 2);
    }
    else if (gameWon) {
        ofSetColor(0, 255, 0);
        ofDrawBitmapString("YOU WIN!", ofGetWidth() / 2 - 50, ofGetHeight() / 2);
    }
    else {
        ofSetColor(255);

        // Draw player
        ofDrawTriangle(playerPos.x, playerPos.y,
            playerPos.x - 15, playerPos.y + 30,
            playerPos.x + 15, playerPos.y + 30);

        // Draw bullets
        for (auto& bullet : bullets) 
            bullet.draw();

        for (auto& bullet : enemyBullets) 
            bullet.draw();


        ofSetColor(255); // reset to white before drawing enemies
        // Draw enemies
        for (auto& enemy : enemies) 
            enemy.draw();
    }
}

void ofApp::keyPressed(int key) {
    if (key == OF_KEY_LEFT) 
        moveLeft = true;
    if (key == OF_KEY_RIGHT) 
        moveRight = true;

    // Player shoots
    if (key == ' ') {
        uint64_t now = ofGetElapsedTimeMillis();
        if (now - lastShotTime >= fireDelay) {
            bullets.push_back(Bullet(playerPos));
            playerShootSound.play();
            lastShotTime = now;
        }
    }
}

void ofApp::keyReleased(int key) {
    if (key == OF_KEY_LEFT) moveLeft = false;
    if (key == OF_KEY_RIGHT) moveRight = false;
}

void ofApp::spawnEnemies() {
    enemies.clear();
    enemies.reserve(30); // 3 rows × 10 columns
    for (int y = 0; y < 3; y++) {
        for (int x = 0; x < 10; x++) {
            enemies.push_back(Enemy(60 + x * 40, 60 + y * 30));
        }
    }
}

void ofApp::resetGame() {
    playerPos.set(ofGetWidth() / 2, ofGetHeight() - 50);
    bullets.clear();
    enemyBullets.clear();
    spawnEnemies();
    gameOver = false;
    gameWon = false;
}
