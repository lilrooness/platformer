#include <allegro.h>
#include <string>
#include <iostream>
#include <fstream>
#include <cstdlib>

using namespace std;

bool isCollision(int x, int y);//returns true if the square under real coordinates x, y hold a value other than 1 when mapped to the map array
void renderMap(BITMAP *buffer);//renders the map to the buffer
//3 is player start, 1 is solid block, 2 is level end
void loadMap(char filename[]);//loads in map from a file "filename"
bool isOnLadder(int x, int y);
void loadBitmaps();//loads the assets

string levels[] = {"assets/map.txt", "assets/level2.txt"};
string enemyMaps[] = {"assets/enemyMap.txt", "assets/enemies2.txt"};

int currentLevel = 0;

int **map;
int **enemyMap;
int rows;
int columns;
BITMAP *ladder;
BITMAP *dirt;
BITMAP *shocked1;
BITMAP *goldKey;
BITMAP *door;

bool isKeyCollected = false;

void renderMap(BITMAP *buffer){
	for(int i=0; i<rows; i++){
		for(int j=0; j<columns; j++){
			if(map[i][j] == 1){
				//rectfill(buffer, j*20, i*20, j*20 + 20, i*20 + 20, makecol(0, 255, 0));
				draw_sprite(buffer, dirt, j*20, i*20);
			}else if(map[i][j] == 4){
				draw_sprite(buffer, ladder, j*20, i*20);
			}else if(map[i][j] == 6){
				draw_sprite(buffer, door, j*20, i*20);
			}
			if(map[i][j] == 5 && !isKeyCollected){
				draw_sprite(buffer, goldKey, j*20, i*20);
			}
		}
	}
}

bool isCollision(int x, int y){
	bool collision = false;
	int mx = x / 20;
	int my = y / 20;

	if(my >= rows - 1 || mx >= columns - 1 || my <= 0 || mx <= 0){
		collision = true;
	}else if(map[my][mx] == 1 || map[my][mx] == 2){
		collision = true;
	}else if(map[my][mx] == 5){
		isKeyCollected = true;
	}
	return collision;
}

void loadMap(const char* filename){
	int lines = 0;
	string line;
	ifstream mapFile;
	mapFile.open(filename);
	while(mapFile.good()){
		getline(mapFile, line);
		lines++;
	}
	mapFile.close();
	mapFile.open(filename);
	int counter = 0;
	string lineArray[lines];
	while(mapFile.good()){
		getline(mapFile, lineArray[counter++]);
	}
	mapFile.close();
	int length = lineArray[0].size();

	//create new 2D int array
	map = new int *[lines - 1];
	for(int i=0; i<lines - 1; i++){
		map[i] = new int[length];
	}

	for(int i=0; i<lines - 1; i++){
		for(int j=0; j<length; j++){
			map[i][j] = lineArray[i][j] - '0';
		}
	}
	rows = lines - 1;
	columns = length;
}

void loadEnemyMap(const char* filename){
	int lines = 0;
	string line;
	ifstream mapFile;
	mapFile.open(filename);
	while(mapFile.good()){
		getline(mapFile, line);
		lines++;
	}
	mapFile.close();
	mapFile.open(filename);
	int counter = 0;
	string lineArray[lines];
	while(mapFile.good()){
		getline(mapFile, lineArray[counter++]);
	}
	mapFile.close();
	int length = lineArray[0].size();

	//create new 2D int array
	enemyMap = new int *[lines - 1];
	for(int i=0; i<lines - 1; i++){
		enemyMap[i] = new int[length];
	}

	for(int i=0; i<lines - 1; i++){
		for(int j=0; j<length; j++){
			enemyMap[i][j] = lineArray[i][j] - '0';
		}
	}
	rows = lines - 1;
	columns = length;
}

bool isOnLadder(int x, int y){
	bool onLadder = false;
	int mx, my;
	mx = x/20;
	my = y/20;
	if(map[my][mx] == 4){
		onLadder = true;
	}

	return onLadder;
}

void printMaps(){
	for(int i=0; i<rows; i++){
		for(int j=0; j<columns; j++){
			cout << map[i][j];
		}
		cout << endl;
	}
}
