#include <iostream>
#include <conio.h>
#include <thread>
#include <chrono>

// functions
void run();
void printMap();
void initMap();
void move(int dx, int dy);
void updateMap();
void changeDirection(char key);
void clearScreen();
void generateFood();

// Variables
char getMapValue(int value);
// Map details
const int mapWidth = 10;
const int mapHeight = 20;
const int totalMapSize = mapWidth * mapHeight;
int map[totalMapSize];
// Snake details
int snakeHeadXPosition;
int snakeHeadYPosition;
int snakeDirection; // 0 is up, 1 is down, 2 is left, 3 is right
int snakeLength = 3; // starting length is 3
// If the game is running
bool running = true;

int main()
{
	// Run our game
	run();
	return 0;
}

// Main game function
void run()
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

		// Clear the screen
		clearScreen();

		// Print the map
		printMap();

		// wait 0.5 seconds
		std::this_thread::sleep_for(std::chrono::milliseconds(250));
	}

	// Print out game over text
	std::cout << "\t\t!!!Game over!" << std::endl << "\t\tYour score is: " << snakeLength;

	// Stop console from closing instantly
	std::cin.ignore();
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
	if (map[newx + newy * mapWidth] == -2) {
		// Increase food value (body length)
		snakeLength++;

		// Generate new food on map
		generateFood();
	}

	// Check location is free
	else if (map[newx + newy * mapWidth] != 0) {
		running = false;
	}

	// Move head to new location
	snakeHeadXPosition = newx;
	snakeHeadYPosition = newy;
	map[snakeHeadXPosition + snakeHeadYPosition * mapWidth] = snakeLength + 1;

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
		x = rand() % (mapWidth - 2) + 1;
		y = rand() % (mapHeight - 2) + 1;

		// If location is not free try again
	} while (map[x + y * mapWidth] != 0);

	// Place new food
	map[x + y * mapWidth] = -2;
}

// Updates the map
void updateMap() {
	// Move in direction indicated
	switch (snakeDirection) {
	case 0: move(-1, 0);
		break;
	case 1: move(0, 1);
		break;
	case 2: move(1, 0);
		break;
	case 3: move(0, -1);
		break;
	}

	// Reduce snake values on map by 1
	for (int i = 0; i < totalMapSize; i++) {
		if (map[i] > 0) map[i]--;
	}
}

// Initializes map
void initMap()
{
	// Places the initual head location in middle of map
	snakeHeadXPosition = mapWidth / 2;
	snakeHeadYPosition = mapHeight / 2;
	map[snakeHeadXPosition + snakeHeadYPosition * mapWidth] = 1;

	// Places top and bottom walls 
	for (int x = 0; x < mapWidth; ++x) {
		map[x] = -1;
		map[x + (mapHeight - 1) * mapWidth] = -1;
	}

	// Places left and right walls
	for (int y = 0; y < mapHeight; y++) {
		map[0 + y * mapWidth] = -1;
		map[(mapWidth - 1) + y * mapWidth] = -1;
	}

	// Generates first food
	generateFood();
}

// Prints the map to console
void printMap()
{
	for (int x = 0; x < mapWidth; ++x) {
		for (int y = 0; y < mapHeight; ++y) {
			// Prints the value at current x,y location
			std::cout << getMapValue(map[x + y * mapWidth]);
		}
		// Ends the line for next x value
		std::cout << std::endl;
	}
}

// Returns graphical character for display from map value
char getMapValue(int value)
{
	// Returns a part of snake body
	if (value > 0) return 'o';

	switch (value) {
		// Return wall
	case -1: return 'X';
		// Return food
	case -2: return 'O';
	}
}