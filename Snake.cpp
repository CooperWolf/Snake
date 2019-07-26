// Snake.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <thread>
#include <chrono>

using namespace std;

void tick(char board[5][20]);

int main()
{
	bool running = true;
	while (running)
	{
		// speed is the parameter which controls how often the game is updated. Lower number is faster
		// wait to update state based on speed
		this_thread::sleep_for(chrono::milliseconds(100));
		char game[5][20];

		tick(game);
	}
}

void tick(char board[5][20]) 
{
	// clear console
	system("CLS");
	// draw new board
	string gameBoard = "";
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 20; j++) {
			// append each row and print out all at once
			gameBoard = gameBoard + board[i][j];
		}
	}
	cout << gameBoard;
}