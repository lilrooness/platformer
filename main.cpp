#include <allegro.h>
#include <iostream>
#include "Player.h"
#include "Enemy.h"
#include "map.h"

void init();//initialises allegro and game
void gameLoop();//main game loop
void update();//updates the game
void render();//renders the game
void endGame();//ends the game (frees up resources)
void getInput();//gets input from the user
void updateGravity();//updates the effects of gravity on the player
void checkDeath();//checks to see if the player is dead, if so restart the game
void resetLevel();//resets the level
void initEnemies();//initialises all of the enemies
void loadStartPoint();//loads the startx and starty positions from the 
void loadMaps();//loads the maps into memory

bool isRunning;//true if the game is running
bool isWon;//false if the playe has not won the current level
int red, green, blue;//holds int values of red green and blue for allegro
int numberOfEnemies;//holds the number of enemies on the map
int startx, starty;//holds the starting position of the player for the level
int cameraX, cameraY;//holds the posision of the camera

Enemy *enemies;

BITMAP *camera;
BITMAP *buffer;
Player p;

int main(){
	init();
	ladder = load_bmp("ladder.bmp", NULL);
	dirt = load_bmp("dirt.bmp", NULL);
	shocked1 = load_bmp("shocked.bmp", NULL);
	if(ladder == NULL || dirt == NULL || shocked1 == NULL){
		std::cout << "Image not loaded\nExiting . . .\n" << std::endl;
		exit(1);
	}
	gameLoop();
	return 0;
}

void init(){
	allegro_init();
	loadMaps();
	printMaps();
	install_keyboard();
	install_timer();
	//install_mouse();
	//install_sound(DIGI_AUTODETECT, MIDI_AUTODETECT, 0);
	set_color_depth(16);
	set_gfx_mode(GFX_AUTODETECT_WINDOWED, 640, 480, 0, 0);
	buffer = create_bitmap(640, 480);
	camera = create_bitmap(640, 480);
	isRunning = true;
	isWon = false;
	red = makecol(255, 0, 0);
	green = makecol(0, 255, 0);
	blue = makecol(0, 0, 255);
	loadStartPoint();
	printf("Rows: %d Columns: %d\n", rows, columns);
	initEnemies();
	resetLevel();
}

void gameLoop(){
	while(isRunning){
		update();
		getInput();
		updateGravity();
		render();
		checkDeath();
		rest(3);
	}
	endGame();
}

void update(){
	p.update();
	p.onLadder = isOnLadder(p.x, p.y);
	p.y = p.y - p.ySpeed;
	if(isCollision(p.x, p.y)){
		p.y = p.y + p.ySpeed;
	}
	cameraX = p.x - 640 / 2;
	cameraY = p.y - 480 / 2;
	for(int i=0; i<numberOfEnemies; i++){
		enemies[i].update();
		draw_sprite(camera, shocked1, enemies[i].x, enemies[i].y);
		if(enemies[i].isCollision(p.x, p.y, p.width, p.height)){
			p.dead = true;
		}
	}
}

void render(){
	if(!isWon){
		p.render(camera);
		renderMap(camera);
		blit(camera, buffer, cameraX, cameraY, 0, 0, 640, 480);
		blit(buffer, screen, 0, 0, 0, 0, 640, 480);
		clear_bitmap(camera);
		clear_bitmap(buffer);
	}

}

void endGame(){
	destroy_bitmap(buffer);
	destroy_bitmap(camera);
	destroy_bitmap(ladder);
	destroy_bitmap(dirt);
	destroy_bitmap(shocked1);
}

void getInput(){
	if(key[KEY_ESC]){
		isRunning = false;
	}
	
	if(key[KEY_LEFT]){
		p.x = p.x - 1;
		if(isCollision(p.x, p.y)){
			p.x = p.x + 2;
		}
	}
	if(key[KEY_RIGHT]){
		p.x = p.x + 1;
		if(isCollision(p.x + p.width, p.y)){
			p.x = p.x - 2;
		}
	}
	if(key[KEY_SPACE]){
		p.jump();
	}
	if(key[KEY_R]){
		resetLevel();
	}
	if(key[KEY_UP] && p.onLadder == true){
		p.y = p.y - 2;
		if(isCollision(p.x, p.y + p.height)){
			p.y = p.y + 2;
		}
	}
}

void updateGravity(){
	p.y = p.y + 1;
	if(isCollision(p.x, p.y + p.height)){
		p.y = p.y - 1;
		p.onGround = true;
	}else{
		p.onGround = false;
	}
}

void checkDeath(){
	if(p.dead){
		resetLevel();
	}
}

void resetLevel(){
	p.x = startx;
	p.y = starty;
	p.dead = false;
}

void initEnemies(){
	numberOfEnemies = 0;
	for(int i=0; i<rows; i++){
		for(int j=0; j<columns; j++){
			if(enemyMap[i][j] == 3){
				numberOfEnemies ++;
			}
		}
	}
	printf("Number of Enemies = %d\n", numberOfEnemies);
	enemies = new Enemy[numberOfEnemies];
	int counter = 0;
	for(int i=0; i<rows; i++){
		for(int j=0; j<columns; j++){
			if(enemyMap[i][j] == 3){
				enemies[counter].x = j*20;
				enemies[counter].y = i*20;
				enemies[counter].width = 20;
				enemies[counter].height = 20;
				enemies[counter].runSpan = 20;
				counter++;
			}
		}
	}
}

void loadStartPoint(){
	for(int i=0; i<rows; i++){
		for(int j=0; j<columns; j++){
			if(map[i][j] == 3){
				startx = j*20;
				starty = i*20;
				break;
			}
		}
	}
}

void loadMaps(){
	char mapFilename[] = {"map.txt"};
	char enemyFilename[] = {"enemyMap.txt"};
	loadMap(mapFilename);
	loadEnemyMap(enemyFilename);
	printf("loaded maps");
}
