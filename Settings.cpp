// Implementation for Settings object

#include "Settings.h"

Settings::Settings(int difficulty, int boardWidth, int boardHeight) {
	this->difficulty = difficulty;
	this->boardWidth = boardWidth;
	this->boardHeight = boardHeight;
}

#pragma region Difficulty
void Settings::setDifficulty(int difficulty) {
	this->difficulty = difficulty;
}

int Settings::getDifficulty() {
	return difficulty;
}
#pragma endregion

#pragma region Board Width
void Settings::setBoardWidth(int boardWidth) {
	this->boardWidth = boardWidth;
}

int Settings::getBoardWidth() {
	return boardWidth;
}
#pragma endregion

#pragma region Board Height
void Settings::setBoardHeight(int boardHeight) {
	this->boardHeight = boardHeight;
}

int Settings::getBoardHeight() {
	return boardHeight;
}
#pragma endregion
