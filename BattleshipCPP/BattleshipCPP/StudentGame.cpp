#include "Board.hpp"
#include "Direction.hpp"
#include "Game.hpp"
#include "Ship.hpp"
#include <iostream>
#include <random>

/**
 * Constructor will create the ships vector and add ships to it.
 */
Game::Game() {
	// Valid ships: Carrier (5), Battleship (4), Destroyer (3), Submarine (3), Patrol Boat (2)
	Ship* carrier = new Ship(5, "Carrier", 67);
	Ship* battleship = new Ship(4, "Battleship", 66);
	Ship* destroyer = new Ship(3, "Destroyer", 68);
	Ship* submarine = new Ship(3, "Submarine", 83);
	Ship* patrolBoat = new Ship(2, "Patrol Boat", 80);

	ships.insert(ships.begin(), *carrier);
	ships.insert(ships.begin() + 1, *battleship);
	ships.insert(ships.begin() + 2, *destroyer);
	ships.insert(ships.begin() + 3, *submarine);
	ships.insert(ships.begin() + 4, *patrolBoat);

	// Create new boards for both the player and the computer
	player = *(new Board());
	computer = *(new Board());
}

/**
 * Begin Game let's user and then computer setup boards then calls run()
 */
void Game::beginGame() {
	// Print both boards (for visualization)
	std::cout << "COMPUTER BOARD: " << std::endl;
	std::cout << computer << std::endl;
	std::cout << "PLAYER BOARD: " << std::endl;
	std::cout << player << std::endl;

	// Introduction
	std::cout << "Welcome to Battleship!" << std::endl;
	std::cout << "You will be facing off against the legendary CAPTAIN HENRY MORGAN" << std::endl;

	std::cout << "To get started, place your ships by following the prompts." << std::endl;

	// Have the user setup their board
	placeShips();

	// Have the computer setup their board
	placeShipsPC();

}

/**
 * Handle the human placing ships.
 */
void Game::placeShips() {
	// Loop through every ship
	for (Ship ship : ships)
	{
		bool shipPlaced = false;
		int x, y, tempD = 0;
		Direction d;
		// Keep trying to place this ship until it is valid
		while (!shipPlaced) {
			std::cout << "Where do you wish to place " << ship << "?" << std::endl;
			std::cin >> x;
			std::cin >> y;
			std::cout << "Horizontal or Vertical? (0 or 1)" << std::endl;
			std::cin >> tempD;
			if (tempD == 0)
				d = HORIZONTAL;
			else if (tempD == 1)
				d = VERTICAL;
			else {
				std::cout << "Must be a 0 or 1. Try again." << std::endl;
				continue;
			}

			if (place(x, y, d, ship, player)) {
				shipPlaced = true;
				std::cout << "Ship is being placed at " << x << " , " << y << std::endl;
				std::cout << "PLAYER BOARD: " << std::endl;
				std::cout << player << std::endl;
			}
			else
				std::cout << "Ship cannot be placed here. Try again." << std::endl;

		}
	}
}

/**
 * Handle the computer placing ships.
 */
void Game::placeShipsPC() {
	// Loop through every ship
	for (Ship ship : ships)
	{
		//Setup temp vars
		bool shipPlaced = false;
		int x, y, tempD = 0;
		int min = 0;
		int max = 9;
		int randInt = 0;
		Direction d;

		// Keep trying to place this ship until it is valid
		while (!shipPlaced) {
			// Seed the random generator
			std::random_device rd;
			std::mt19937 rng(rd());
			std::uniform_int_distribution<int> uni(min, max);

			x = uni(rng);
			y = uni(rng);
			tempD = uni(rng);

			if (tempD > 5)
				d = VERTICAL;
			else
				d = HORIZONTAL;

			//Place and check that the ship was placed
			if (place(x, y, d, ship, computer)) {
				shipPlaced = true;
			}
		}
	}
}

/**
 * Helper method that checks if it is safe to put a ship
 * at a particular spot with a particular direction.
 */
bool Game::place(const int& x, const int& y, Direction d, const Ship& s, Board& b) {
	// Start with some basic checks before moving on to placement

	// Check that the number is not negative
	if (x < 0 || y < 0)
		return false;

	// Check that the number is within bounds
	if (x > WIDTH || y > HEIGHT)
		return false;

	// Check that it can fit (Vertically go (y + spaces), Horizontally go (x + spaces))

	// Check horizontal
	if (d == HORIZONTAL) {
		bool isEmpty = true;
		for (size_t i = 0; i < s.getSpaces(); i++)
		{
			try {
				if (b[x + i][y] != EMPTY)
					isEmpty = false;
			}
			catch (const std::exception& e) {
				return false;
			}
		}
		if (isEmpty) {
			for (size_t i = 0; i < s.getSpaces(); i++)
			{
				b[x + i][y] = s.getChr();
			}
			return true;
		}

	}
	//Check Vertical
	if (d == VERTICAL) {
		bool isEmpty = true;
		for (size_t i = 0; i < s.getSpaces(); i++)
		{
			try {
				if (b[x][y + i] != EMPTY)
					isEmpty = false;
			}
			catch (const std::exception& e) {
				return false;
			}
		}
		if (isEmpty) {
			for (size_t i = 0; i < s.getSpaces(); i++)
			{
				b[x][y + i] = s.getChr();
			}
			return true;
		}
	}

	return false;
}

/**
 * Call human turn/computer turn until someone wins.
 */
void Game::run() {
	//While neither player has the number of hits required to win.
	while((player.count() != 17) && (computer.count() != 17)){
		//Run turns
		humanTurn();
		computerTurn();
		//Print boards after hits are made
		std::cout << "PLAYER BOARD: " << std::endl;
		std::cout << player << std::endl;
		std::cout << "COMPUTER BOARD: " << std::endl;
		std::cout << computer << std::endl;
		//Print who is winning
		if(computer.operator<(player)){
			std::cout << "PLAYER IS WINNING" << std::endl;
		} else {
			std::cout << "COMPUTER IS WINNING" << std::endl;
		}
	}
	//Print who has won
	if(computer.operator<(player)){
		std::cout << "PLAYER WON" << std::endl;
	} else {
		std::cout << "COMPUTER WON" << std::endl;
	}
}

/**
 * @brief Method loop for the human player to fire shots in their turn
 * 
 */
void Game::humanTurn() {
	//temp vars
	int x = 0;
	int y = 0;
	//Ask and read where to fire
	std::cout << "Where do you wish to fire? (X cord then Y cord)" << std::endl;
	std::cin >> x;
	std::cin >> y;
	//Check that coordinates are valid
	if (x < 0 || y < 0 || x > WIDTH || y > HEIGHT){
		std::cout << "Invalid coordinates, please try again." << std::endl;
		humanTurn();
	//Cords are valid
	} else {
		//Check for miss
		if(computer[x][y] == EMPTY){
			computer[x][y] = MISS;
			std::cout << "Player MISS!" << std::endl;
		//Check for a repeat miss
		} else if (computer[x][y] == MISS){
			std::cout << "Player MISSES Again!" << std::endl;
		//Check for hit
		} else {
			computer[x][y] = HIT;
			std::cout << "Player HIT!" << std::endl;
		}
	}
}

/**
 * @brief Method loop for the computer player to fire shots in their turn. AI scans through every single space in the board.
 * 
 */
void Game::computerTurn() {
	//Temp vars preset for invalid cords
	int x = -10;
	int y = -10;
	//Iterate through the board
	for (size_t i = 0; i < WIDTH; i++)
	{
		for (size_t j = 0; j < HEIGHT; j++)
		{
			//Find a space that hasn't been shot at yet
			if ((player[i][j] != MISS) && (player[i][j] != HIT)){
				//load it into the temp vars
				x = i;
				y = j;
			}
			//Break loop if the temp vars are filled
			if ((x != -10) && (y != -10)){break;}
		}
		//Break loop if the temp vars are filled
		if ((x != -10) && (y != -10)){break;}
	}
	//Check for misses
	if(player[x][y] == EMPTY){
		player[x][y] = MISS;
		std::cout << "Computer MISS!" << std::endl;
	//Check for hits
	} else {
		player[x][y] = HIT;
		std::cout << "Computer HIT!" << std::endl;
	}
}

/**
 * Create a game instance and start.
 */
int main(int argc, char** argv) {
	(void)argc;
	(void)argv;
	Game g;
	g.beginGame();
	g.run();

	return 0;
}
