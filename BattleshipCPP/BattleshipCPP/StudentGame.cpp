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

	// Ship temp = ships.at(3);
	// std::cout << temp.getName() << std::endl;

	// Create new boards for both the player and the computer
	player = *(new Board());
	computer = *(new Board());

	//Board* playerBoard = new Board();
	
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
	std::cout << "You will be facing off against the legendary CAPTAIN <name>" << std::endl;

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
	// Place ship logic here
	// Probably want to loop through every ship and have randomly place it, checking if its valid

	// Gonna use the same logic as above, except choose random numbers and see if they work
	// Loop through every ship
	for (Ship ship : ships)
	{
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

			if (place(x, y, d, ship, computer)) {
				shipPlaced = true;
				//std::cout << "Ship is being placed at " << x << " , " << y << std::endl;
				//std::cout << "COMPUTER BOARD: " << std::endl;
				//std::cout << computer << std::endl;
			}
				//std::cout << "Ship cannot be placed here. Try again." << std::endl;

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

	while((player.count() != 17) && (computer.count() != 17)){
		humanTurn();
		computerTurn();
		std::cout << "PLAYER BOARD: " << std::endl;
		std::cout << player << std::endl;
		std::cout << "COMPUTER BOARD: " << std::endl;
		std::cout << computer << std::endl;
		if(computer.operator<(player)){
			std::cout << "PLAYER IS WINNING" << std::endl;
		} else {
			std::cout << "COMPUTER IS WINNING" << std::endl;
		}
	}
	if(computer.operator<(player)){
		std::cout << "PLAYER WON" << std::endl;
	} else {
		std::cout << "COMPUTER WON" << std::endl;
	}
}

void Game::humanTurn() {

	// Process turn
	int x = 0;
	int y = 0;
	//std::cout << "Where do you wish to place " << ship << "?" << std::endl;
	std::cout << "Where do you wish to fire? (X cord then Y cord)" << std::endl;
	std::cin >> x;
	std::cin >> y;
	if (x < 0 || y < 0 || x > WIDTH || y > HEIGHT){
		std::cout << "Invalid coordinates, please try again." << std::endl;
		humanTurn();
	} else {
		if(computer[x][y] == EMPTY){
			computer[x][y] = MISS;
			std::cout << "Player MISS!" << std::endl;
		} else if (computer[x][y] == MISS){
			std::cout << "Player MISSES Again!" << std::endl;
		} else {
			computer[x][y] = HIT;
			std::cout << "Player HIT!" << std::endl;
		}
	}
}

void Game::computerTurn() {

	// Same as human turn, but add random elements 
	int x = -10;
	int y = -10;
	for (size_t i = 0; i < WIDTH; i++)
	{
		// Rows
		for (size_t j = 0; j < HEIGHT; j++)
		{
			if ((player[i][j] != MISS) && (player[i][j] != HIT)){
				x = i;
				y = j;
			}
			if ((x != -10) && (y != -10)){break;}
		}
		if ((x != -10) && (y != -10)){break;}
	}
	if(player[x][y] == EMPTY){
		player[x][y] = MISS;
		std::cout << "Computer MISS!" << std::endl;
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
