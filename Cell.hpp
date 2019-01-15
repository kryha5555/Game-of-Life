#pragma once
#include <SFML/Graphics.hpp>
using namespace sf;

class Cell
{
private:
	bool alive;
	bool visited;
	RectangleShape shape;
	bool trace;
	
public:
	Cell(int x, int y, bool alive, int size, bool trace);
	Cell();
	bool isAlive();
	void setAlive(bool alive);
	bool isVisited();
	void setVisited(bool visited);
	void paint();
	void draw(RenderWindow &window);
};