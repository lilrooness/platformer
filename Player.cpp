#include "Player.h"

Player::Player(int x, int y, int width, int height){
	onGround = false;
	onLadder = false;
	this->x = x;
	this->y = y;
	this->width = width;
	this->height = height;
}

Player::Player(){
	onGround = false;
	onLadder = false;
	height = 5;
	width = 5;
}

void Player::jump(){
	if(onGround && !onLadder){
		onGround = false;
		ySpeed = 10;
	}
}

void Player::update(){
	if(onLadder){
		onGround = true;
	}
	if(ySpeed > 0){
		ySpeed --;
	}
}

void Player::render(BITMAP *buffer){
	rectfill(buffer, x, y, x + width, y + height, makecol(255,0,0));
}
