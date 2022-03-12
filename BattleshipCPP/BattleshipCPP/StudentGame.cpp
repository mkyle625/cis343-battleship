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
			// First check that the entire ship will fit
			if (x + i > WIDTH)
				return false;

			if (player[x + i][y] != EMPTY)
				isEmpty = false;
		}
		if (isEmpty) {
			for (size_t i = 0; i < s.getSpaces(); i++)
			{
				player[x + i][y] = s.getChr();
			}
			return true;
		}

	}
	if (d == VERTICAL) {
		bool isEmpty = true;
		for (size_t i = 0; i < s.getSpaces(); i++)
		{
			// Check that the entire ship fits
			if (y + i > WIDTH)
				return false;

			if (player[x][y + i] != EMPTY)
				isEmpty = false;
		}
		if (isEmpty) {
			for (size_t i = 0; i < s.getSpaces(); i++)
			{
				player[x][y + i] = s.getChr();
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
}

void Game::humanTurn() {
}

void Game::computerTurn() {
}

/**
 * Create a game instance and start.
 */
int main(int argc, char** argv) {
	(void)argc;
	(void)argv;
	Game g;
	g.beginGame();

	return 0;
}
