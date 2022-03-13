#ifndef			__HPP_BOARD__
#define			__HPP_BOARD__

#include "BoardValues.hpp"
#include <iostream>

#define HEIGHT 10
#define WIDTH 10

class Board {

public:
	Board();
	int count() const;
	bool operator< (const Board& other); // Count number of spots on board, if "this" board is less than "other" board
	void setVisible(bool v);

	class Internal {
	public:
		Internal(int* _g) {
			_grid = _g;
		}
		int& operator[](int index);

	private:
		int* _grid;
	};
	Internal operator[](int index);
	

private:
	int* grid;
	bool visible;

	friend std::ostream& operator<<(std::ostream& os, Board const& b);

};


#endif
