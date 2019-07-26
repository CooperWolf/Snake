// Snake.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>

using namespace std;

void tick();

int main()
{
	tick();
}

void tick() 
{
	for (int i = 0; i < 20; i++) 
	{
		// clear console
		system("CLS");
		// draw new board
		cout << i;
	}
}