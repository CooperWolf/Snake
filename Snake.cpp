#include <iostream>
#include <sstream>
#include <string>
#include <conio.h>
#include <thread>
#include <chrono>
#include "Settings.h"

using namespace std;

#pragma region functions
Settings setUpGame(Settings *currentSettings);
void run(int difficulty);
void printMap();
void initMap();
void move(int dx, int dy);
void updateMap();
void changeDirection(char key);
void clearScreen();
void generateFood();
char getMapValue(int value);
#pragma endregion

#pragma region Variables
// Map details
const int mapHeight = 20;
const int mapWidth = 40;
const int totalMapSize = mapHeight * mapWidth;
int map[totalMapSize];
// Snake details
int snakeHeadXPosition;
int snakeHeadYPosition;
int snakeDirection; // 0 is up, 1 is down, 2 is left, 3 is right
int snakeLength = 3; // starting length is 3
// If the game is running
bool running = true;
// Difficulty
/*
* 800 = easy = 1
* 600 = medium = 2
* 400 = hard = 3
* 200 = extreme = 4
* 50 = good luck = 5
*/
// easy by default
int speed = 800; 
int difficultyChoice = 1;
#pragma endregion

int main()
{
	// Settings object with default vaslues to start
	Settings gameSettings = Settings(difficultyChoice, mapWidth, mapHeight);
	// Get Load our game settings
	setUpGame(&gameSettings);
	// Run our game
	run(speed);
	return 0;
}

Settings setUpGame(Settings *currentSettings) {
	// game defaults
	int difficulty = 1;
	int width = 40;
	int height = 20;

	cout << "1 = easy" << endl;
	cout << "2 = medium" << endl;
	cout << "3 = hard" << endl;
	cout << "4 = extreme" << endl;
	cout << "5 = good luck" << endl;
	cout << "Choose your diffuclty: " << endl;
	cin >> difficultyChoice;
	// get the choice and them convert it to a int
	stringstream temp(difficultyChoice);
	int dChoice = 0;
	temp >> dChoice;

	switch (dChoice)
	{
	case 2:
		// medium
		difficultyChoice = 2;
		difficulty = 600;
		break;
	case 3:
		// hard
		difficultyChoice = 3;
		difficulty = 400;
		break;
	case 4:
		// extreme
		difficultyChoice = 4;
		difficulty = 200;
		break;
	case 5:
		// extreme
		difficultyChoice = 5;
		difficulty = 50;
		break;
	default:
		// we default to 1 = easy
		difficultyChoice = 1;
		difficulty = 800;
		break;
	}

	// create our settings object and return it
	return Settings(difficulty, width, height);
}

// Main game function
void run(int difficulty)
{
	// Create and draw the initial map
	initMap();
	// While the game is running...
	while (running) {
		// Check if a key is being pressed, if it is than determine if the snake needs to change directions
		if (_kbhit())
			changeDirection(_getch());

		// Upate the map
		updateMap();

		// Print the current Map
		printMap();

		// wait .25 seconds. Can change this value if you want the game to be faster or slower
		// less time is faster and a higher time is slower.
		this_thread::sleep_for(chrono::milliseconds(difficulty));
	}

	// Print out game over text
	cout << "\t\tGame Over :'(" << endl << "\t\tYour score is: " << snakeLength;

	// Stop console from closing instantly
	cin.ignore();
}

// Change the direction of the snake
void changeDirection(char key) {
	switch (key) {
	case 'w':
		// make sure they are not currently heading down
		if (snakeDirection != 2) 
			snakeDirection = 0;
		break;
	case 'd':
		// make sure they are not currently heading left
		if (snakeDirection != 3) 
			snakeDirection = 1;
		break;
	case 's':
		// make sure they are not currently heading up
		if (snakeDirection != 4) 
			snakeDirection = 2;
		break;
	case 'a':
		// make sure they are not currently heading right
		if (snakeDirection != 5) 
			snakeDirection = 3;
		break;
	}
}

// updates where teh snakes head is at
void move(int dx, int dy) {
	// determine new head position
	int newx = snakeHeadXPosition + dx;
	int newy = snakeHeadYPosition + dy;

	// Check if there is food at location
	if (map[newx + newy * mapHeight] == -2) {
		// Increase food value (body length)
		snakeLength++;

		// Generate new food on map
		generateFood();
	}

	// Check location is free
	else if (map[newx + newy * mapHeight] != 0) {
		running = false;
	}

	// Move head to new location
	snakeHeadXPosition = newx;
	snakeHeadYPosition = newy;
	map[snakeHeadXPosition + snakeHeadYPosition * mapHeight] = snakeLength + 1;

}

// Clears screen
void clearScreen() {
	// Clear the screen
	system("cls");
}

// Generates new food on map
void generateFood() {
	int x = 0;
	int y = 0;
	do {
		// Generate random x and y values within the map
		x = rand() % (mapHeight - 2) + 1;
		y = rand() % (mapWidth - 2) + 1;

		// If location is not free try again
	} while (map[x + y * mapHeight] != 0);

	// Place new food
	map[x + y * mapHeight] = -2;
}

// Updates the map
void updateMap() {
	// Move in direction indicated
	switch (snakeDirection) {
	case 0: 
		move(-1, 0);
		break;
	case 1: 
		move(0, 1);
		break;
	case 2: 
		move(1, 0);
		break;
	case 3: 
		move(0, -1);
		break;
	}

	// Reduce snake values on map by 1
	for (int i = 0; i < totalMapSize; i++) {
		if (map[i] > 0) 
			map[i]--;
	}
}

// Initializes map
void initMap()
{
	// Places the initual head location in middle of map
	snakeHeadXPosition = mapHeight / 2;
	snakeHeadYPosition = mapWidth / 2;
	map[snakeHeadXPosition + snakeHeadYPosition * mapHeight] = 1;

	// Places top and bottom walls 
	for (int x = 0; x < mapHeight; ++x) {
		map[x] = -1;
		map[x + (mapWidth - 1) * mapHeight] = -1;
	}

	// Places left and right walls
	for (int y = 0; y < mapWidth; y++) {
		map[0 + y * mapHeight] = -1;
		map[(mapHeight - 1) + y * mapHeight] = -1;
	}

	// Generates food
	generateFood();
}

// Prints the map to console
void printMap()
{
	// Clear the current screen
	clearScreen();

	string board = "";
	for (int x = 0; x < mapHeight; ++x) {
		for (int y = 0; y < mapWidth; ++y) {
			// Prints the value at current x,y location
			board = board + getMapValue(map[x + y * mapHeight]);
		}
		// Ends the line for next x value
		board = board + "\n";
	}
	cout << board;
}

// Returns graphical character for display from map value
char getMapValue(int value)
{
	if (value > 0) 
		// @ = snale body part
		return '@';

	switch (value) {
	case -1: 
		// # = Wall
		return '#';
	case -2: 
		// * = Food
		return '*';
	}
}