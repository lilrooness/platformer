#include <allegro.h>

class Player{
	public:
	bool dead;//set to true if player dies
	bool onGround;//true if the player is on the ground
	bool onLadder;
	int x, y, width, height, ySpeed;//yspeed is the jump speed
	Player(int x, int y, int width, int height);
	Player();
	void render(BITMAP *buffer);//renders the player to the buffer
	void jump();//makes the player jump
	void update();//updates the players yspeed
};
