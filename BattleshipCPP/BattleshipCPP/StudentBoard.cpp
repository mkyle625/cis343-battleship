#include "Board.hpp"
#include "BoardValues.hpp"

#include <algorithm>
#include <iostream>
#include <string>

#include <iomanip>

/**
 * Constructor upon game init. to create an empty board
 */
Board::Board() {
	
	// Variable grid holds a pointer TO the actual game board multi-array
	grid = *(new int[WIDTH][HEIGHT]);

	// Columns
	for (size_t i = 0; i < WIDTH; i++)
	{
		// Rows
		for (size_t j = 0; j < HEIGHT; j++)
		{
			*(grid + (j * WIDTH) + i) = EMPTY;
		}
	}
}

/**
 * Whether to make the ships visible on this board or not.
 * Used for when the ships on the computer board should be
 * hidden from the player
 */
void Board::setVisible(bool v) {
	if (v)
		visible = true;
	else
		visible = false;
}

/**
 * Allows for the operation of board[][]
 */
int& Board::Internal::operator[](int index) {
	// This code was supplied from the assingment description
	// It is part of what is used to do board[][]
	if (index >= WIDTH) {
		throw std::out_of_range(std::to_string(index) + " is greater value than or equal to grid width of " + std::to_string(WIDTH));
	}
	return _grid[index];
}

/**
 * Allows for the operation of board[][]
 */
Board::Internal Board::operator[](int index) {
	// This code was supplied from the assingment description
	// It is part of what is used to do board[][]
	if (index >= HEIGHT) {
		throw std::out_of_range(std::to_string(index) + " is greater value than or equal to grid height of " + std::to_string(HEIGHT));
	}
	return Board::Internal(grid + (index * WIDTH)); NULL;
}

/**
 * Allows for the operation of std::cou t << board;
 * Prints the entire state of the board
 */
std::ostream& operator<<(std::ostream& os, Board const& b) {

	// Print the header for the columns
	// The setw(5) ensures the grid prints out in a nice rectangle
	os << "  ";
	for (int i = 0; i < WIDTH; i++)
	{
		os << std::setw(5) << i;
	}
	os << std::endl;
	os << "---------------------------------------------------------";

	// Columns
	for (size_t i = 0; i < WIDTH; i++)
	{
		// Print a new line for the next row
		os << std::endl;
		os << i << "|";
		// Rows
		for (size_t j = 0; j < HEIGHT; j++)
		{
			// Player board
			if (b.visible)
				os << std::setw(5) << (char)*(b.grid + (j * WIDTH) + i);
			// Computer board
			else {
				if ((*(b.grid + (j * WIDTH) + i)) != HIT && (*(b.grid + (j * WIDTH) + i)) != MISS)
					os << std::setw(5) << " ";
				else
					os << std::setw(5) << (char)*(b.grid + (j * WIDTH) + i);
			}
		}
	}

	return os;
}

/**
 * Counts the number of hits on the board
 */
int Board::count() const {
	// Count all of the hits on the board.
	
	// A player needs 5 + 4 + 3 + 3 + 2 = 17 hits to win
	
	int count = 0;

	// Columns
	for (size_t i = 0; i < WIDTH; i++)
	{
		// Rows
		for (size_t j = 0; j < HEIGHT; j++)
		{
			if ((*(grid + (j * WIDTH) + i)) == HIT)
				count++;
		}
	}

	return count;
}

/**
 * Allows for the operation of board < otherBoard
 */
bool Board::operator< (const Board& other) {
	
	// Used to see who is currently winning
	
	if (other.count() < count())
		return true;
	else
		return false;
}
