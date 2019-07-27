using namespace std;

class Settings
{
private:
	int difficulty;
	int boardWidth;
	int boardHeight;

public:
	Settings(int difficulty, int boardWidth, int boardHeight) {
		this->difficulty = difficulty;
		this->boardWidth = boardWidth;
		this->boardHeight = boardHeight;
	}

#pragma region Difficulty
	void setDifficulty(int difficulty) {
		this->difficulty = difficulty;
	}

	int getDifficulty() {
		return difficulty;
	}
#pragma endregion

#pragma region Board Width
	void setBoardWidth(int boardWidth) {
		this->boardWidth = boardWidth;
	}

	int getBoardWidth() {
		return boardWidth;
	}
#pragma endregion

#pragma region Board Height
	void setBoardHeight(int boardHeight) {
		this->boardHeight = boardHeight;
	}

	int getBoardHeight() {
		return boardHeight;
	}
#pragma endregion
};