#pragma once 
#include "Pattern.hpp"
#include "Cell.hpp"

class Grid
{
private:
	int width;
	int height; 
	Cell **cells;
	int sizeOfCell;
	bool trace;
	Pattern pattern;

public:
	void create(int width, int height, int size, bool randomStart, bool trace);
	~Grid();
	void setCell(bool alive, int x, int y);
	bool isCellAlive(int x, int y);
	void update();
	void draw(RenderWindow &window);
	void randomize();
	void setVisited(bool visited, int x , int y );
	void spawn(int number, int x_, int y_);
};