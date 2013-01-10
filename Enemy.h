#include <allegro.h>

class Enemy{
	private:

	public:
	bool right;//if true enemy is moving right, if false, enemy is moving to the left
	int x, y, width, height, runSpan, runCounter;//runSpan controlls where and for how far the Enemy runs for
	Enemy(int x, int y, int width, int height, int runSpan);
	Enemy();//Default Constructor (So can be used in an array)
	void update();//updates the enemy's position, based on its runSpan
	void render(BITMAP *buffer);//renders the enemy to the buffer
	bool isCollision(int x, int y, int width, int height);//returns true if there s a collision with the enemy
};

