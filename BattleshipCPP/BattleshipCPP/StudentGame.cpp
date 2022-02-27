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

	// Add ships to the vector
	ships.insert(ships.begin(), *carrier);
	ships.insert(ships.begin() + 1, *battleship);
	ships.insert(ships.begin() + 2, *destroyer);
	ships.insert(ships.begin() + 3, *submarine);
	ships.insert(ships.begin() + 4, *patrolBoat);
	
	// Ship temp = ships.at(3);
	// std::cout << temp.getName() << std::endl;

	
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
}

/**
 * Handle the computer placing ships.
 */
void Game::placeShipsPC() {
}

/**
 * Helper method that checks if it is safe to put a ship
 * at a particular spot with a particular direction.
 */
bool Game::place(const int& x, const int& y, Direction d, const Ship& s, Board& b) {
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
