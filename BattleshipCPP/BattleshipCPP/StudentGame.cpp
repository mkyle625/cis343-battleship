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
	int count = 0;
	//// Columns
	//for (size_t i = 0; i < WIDTH; i++)
	//{
	//	// Rows
	//	for (size_t j = 0; j < HEIGHT; j++)
	//	{
	//		count++;
	//		//player[i][j] = 0;
	//		std::cout << player[i][j] << std::endl;
	//	}
	//}
	std::cout << player << std::endl;
	//Board* playerBoard = new Board();
	
}

/**
 * Begin Game let's user and then computer setup boards then calls run()
 */
void Game::beginGame() {
	// Have the user setup their board
	placeShips();
	// Have the computer setup their board
	placeShipsPC();

}

/**
 * Handle the human placing ships.
 */
void Game::placeShips() {
	// Place ship logic here
	// Probably want to loop through every ship and have player place it, checking if its valid
}

/**
 * Handle the computer placing ships.
 */
void Game::placeShipsPC() {
	// Place ship logic here
	// Probably want to loop through every ship and have randomly place it, checking if its valid
}

/**
 * Helper method that checks if it is safe to put a ship
 * at a particular spot with a particular direction.
 */
bool Game::place(const int& x, const int& y, Direction d, const Ship& s, Board& b) {
	// TEMP VALUE TO COMPILE
	return true;
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
