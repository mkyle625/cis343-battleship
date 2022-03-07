#include "Board.hpp"
#include "BoardValues.hpp"

#include <algorithm>
#include <iostream>
#include <string>

Board::Board() {
	// Adding some comments here for figuring 
	// out how the code works.
	
	// This constructs the board class, probably
	// using the int& grid in the hpp file.
	
	// I am guessing that we need to construct a matrix
	// something like grid = new int[WIDTH][HEIGHT]

	//int gameGrid[WIDTH][HEIGHT];
	// Variable grid holds a pointer TO the actual game board multi-array
	grid = *(new int[WIDTH][HEIGHT]);

	//int temp[WIDTH][HEIGHT]{};
	//grid = *temp;
	// *(grid + (iRow * WIDTH) + iCol)

	// Columns
	for (size_t i = 0; i < WIDTH; i++)
	{
		// Rows
		for (size_t j = 0; j < HEIGHT; j++)
		{
			*(grid + (j * WIDTH) + i) = EMPTY;
		}
	}

	// TESTING STUFF BELOW

	//int count = 0;
	//// Columns
	//for (size_t i = 0; i < WIDTH; i++)
	//{
	//	// Rows
	//	for (size_t j = 0; j < HEIGHT; j++)
	//	{
	//		count++;
	//		std:: cout << *(grid + (j * WIDTH) + i);
	//	}
	//}

	//std::cout << count;

	//temp[0][0] = 64;
	//temp[1][0] = 63;
	//temp[2][0] = 62;
	//std::cout << *(grid + (0 * WIDTH) + 0) << std::endl;
	//std::cout << *(grid + (1 * WIDTH) + 0) << std::endl;

	/*for (size_t i = 0; i < WIDTH; i++)
	{
		std::cout << temp[i][0] << std::endl;
	}*/
}

Board::Board(const Board& other) {
	// Not exactly sure what this constructor
	// does, but it will probably become useful later
}

Board& Board::operator=(const Board& other) {
	// Equals operator for checking Board = Board??
	// TEMP VALUES TO COMPILE PLEASE REPLACE
	Board temp;
	return temp;
}

Board::~Board() {
}

void Board::setVisible(bool v) {
}

int& Board::Internal::operator[](int index) {
	// This code was supplied from the assingment description
	// It is part of what is used to do board[][]
	if (index >= WIDTH) {
		throw std::out_of_range(std::to_string(index) + " is greater value than or equal to grid width of " + std::to_string(WIDTH));
	}
	return _grid[index];
}

Board::Internal Board::operator[](int index) {
	// This code was supplied from the assingment description
	// It is part of what is used to do board[][]
	if (index >= HEIGHT) {
		throw std::out_of_range(std::to_string(index) + " is greater value than or equal to grid height of " + std::to_string(HEIGHT));
	}
	return Board::Internal(grid + (index * WIDTH)); NULL;
}

std::ostream& operator<<(std::ostream& os, Board const& b) {
	//os << s.name << " [" << s.spaces << " spaces]";
	//return os;

	// Print the header for the board:
	os << "     0     1     2     3     4     5     6     7     8     9" << std::endl;
	os << "--------------------------------------------------------------" << std::endl;


	// Columns
	for (size_t i = 0; i < WIDTH; i++)
	{
		// Print a new line for the next row
		os << std::endl;
		os << i << " |";
		// Rows
		for (size_t j = 0; j < HEIGHT; j++)
		{
			os << "    " << *(b.grid + (j * WIDTH) + i);
		}
	}

	return os;
}

int Board::count() const {
	// TEMP VALUES TO COMPILE
	return 0;
}

bool Board::operator< (const Board& other) {
	// In class he said this was used to see who is currently winning
	// TEMP VALUES TO COMPILE PLEASE REPLACE
	return true;
}
