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
}

Board::Board(const Board& other) {
	// Not exactly sure what this constructor
	// does, but it will probably become useful later
}

Board& Board::operator=(const Board& other) {
	// Equals operator for checking Board = Board??
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
	/* 
	This is a stream that prints out the board, very
	similar to what is in the Ship.hpp file
	The pattern for printing out the board will become
	something like this:
	os << s.name << " [" << s.spaces << " spaces]";
		return os;
	*/
}

int Board::count() const {
}

bool Board::operator< (const Board& other) {
	// In class he said this was used to see who is currently winning
}
