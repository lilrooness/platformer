#include "Enemy.h"

Enemy::Enemy(int x, int y, int width, int height, int runSpan){
	this->x = x;
	this->y = y;
	this->width = width;
	this->height = height;
	right = true;
	runCounter = 0;
}

Enemy::Enemy(){
	runCounter = 0;
	right = true;
}

void Enemy::update(){
	if(right){
		if(runCounter < runSpan){
			runCounter++;
			x++;
		}else{
			right = false;
		}
	}else{
		if(runCounter > 0){
			runCounter--;
			x --;
		}else{
			right = true;
		}
	}
}

void Enemy::render(BITMAP *buffer){
	rectfill(buffer, x, y, x + width, y + height, makecol(255,255,255));
}

bool Enemy::isCollision(int x, int y, int width, int height){
	bool collision = false;
	if(x + width > this->x && x < this->x + this->width && y + height > this->y && y < this->y + this->height){
		collision = true;
	}
	return collision;
}
