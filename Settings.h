#pragma once

class Settings
{
private:
	int difficulty;
	int boardWidth;
	int boardHeight;

public:
	Settings(int difficulty, int boardWidth, int boardHeight);
	void setDifficulty(int difficulty);
	int getDifficulty();
	void setBoardWidth(int boardWidth);
	int getBoardWidth();
	void setBoardHeight(int boardHeight);
	int getBoardHeight();
};