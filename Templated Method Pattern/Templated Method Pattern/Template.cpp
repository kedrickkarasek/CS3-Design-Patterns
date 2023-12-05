//Example of Templated Method Design Pattern
//Created by Kedrick Karasek

/*
*************************Important Information about Templated Method Design Pattern*******************************************************************
1. Must specify an abstract class that implements most of the functionality                                                                           *
2. Primative Operations: Are functions to be implemented (overriden) in concrete classes                                                              *
3. Hook Operations: Are functions that may be overriden by concrete classes, must provide some default behavior                                       *
4. Templated method: is a function of the base class that uses primitive operations to accomplish a certain task. (concrete implementations)          *
5. Templated method design pattern is a behavioral pattern                                                                                            *
6. Templated method is used to design frameworks because the base class invokes the subclass method                                                   *
*******************************************************************************************************************************************************
*/

#include <iostream>

//Template for any game where players take, turns to make moves and there is a winner
class Game {
public:
	//defualt constructor for game
	Game() :playerCount_(0), moveCount_(0), playerWon_(noWinner) {}

	//Template Method
	void playGame(const int playerCount = 0) {
		playerCount_ = playerCount;
		moveCount_ = 0;

		initializeGame();

		for (int i = 0; !endOfGame(); i = (i + 1) % playerCount_) {
			makeMove(i);
			if (i == playerCount_ - 1) {
				++moveCount_;
			}
		}

		printWinner();
	}

	//Destructor
	virtual ~Game(){}

protected: //things in protected are members of a class that are accessible within the class and its derived classes but is not directly accessible from outside the class hierarchy.
	//Primitive Operations Below
	virtual void initializeGame() = 0;     //Pure Virutal
	virtual void makeMove(int player) = 0; //Pure Virtual
	virtual void printWinner() = 0;        //Pure Virtual

	//Hook Operation
	virtual bool endOfGame() {
		return playerWon_ != noWinner;
	}

	//variables
	static const int noWinner = -1;
	int playerCount_;
	int moveCount_;
	int playerWon_;

};

//a concrete game implementing primitive operations for the template method
class Monopoly : public Game {
public:
	//Implementing Concrete Methods (override keyword is optional but recommended)
	void initializeGame() override{
		playerCount_ = rand() % numPlayersAllowed_ + 1;
	}

	void makeMove(int player) override {
		if (moveCount_ > minMoves_) {
			const int chance = minMoves_ + rand() % (maxMoves_ - minMoves_);
			if (chance < moveCount_) playerWon_ = player;
		}
	}

	void printWinner() override {
		std::cout << "Monopoly, player " << playerWon_ << " won in " << moveCount_ << " moves." << std::endl;
	}

private:
	//variables
	static const int numPlayersAllowed_ = 8; //Maximum number of players allowed for Monoploy
	static const int minMoves_ = 20;  //Nobody wins before minMoves_
	static const int maxMoves_ = 200; //Somebody wins before maxMoves_
};

//another concrete game implementing primitive operations for the template method
class Chess : public Game {
public:
	//Implmenting Concrete Methods (without override keyword to prove it works the same way, but with less protection)
	void initializeGame() {
		playerCount_ = numPlayersAllowed_;
		for (int i = 0; i < numPlayersAllowed_; ++i) {
			experience_[i] = rand() % maxExperience_ + 1;
		}
	}

	void makeMove(int player) {
		if (moveCount_ > minMoves_) {
			for (int i = 0; i < numPlayersAllowed_; ++i) {
				const int chance = (rand() % maxExperience_ + 1);
				if (chance < moveCount_) {
					playerWon_ = player;
				}
			}
		}
	}

	void printWinner() {
		std::cout << "Chess, player " << playerWon_
			<< " with experience " << experience_[playerWon_]
			<< " won in " << moveCount_ << " moves over"
			<< " player with experience " << experience_[playerWon_ == 0 ? 1 : 0]
			<< std::endl;
	}

private:
	//variables
	static const int numPlayersAllowed_ = 2;
	static const int minMoves_ = 2; //nobody wins before minMoves
	static const int maxMoves_ = 100; //somebody wins before maxMoves
	static const int maxExperience_ = 5; //player's Experience, the higher the experience the greater probability of winning
	int experience_[numPlayersAllowed_];
};

int main() {
	//need for when rand() is called
	srand(time(nullptr));

	//pointer to game class initialized to nullptr
	Game* gp = nullptr;

	//playing chess 10 times
	for (int i = 0; i <= 10; ++i) {
		//set game pointer to a new chess game play the game and then deallocated the data and repeate 
		gp = new Chess;
		gp->playGame();
		delete gp;
	}

	//playing monoploy 10 times
	for (int i = 0; i <= 10; ++i) {
		// set game pointer to a new monopoloy game play the game and then deallocated the data and repeate
		gp = new Monopoly;
		gp->playGame();
		delete gp;
	}
}