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
	Cell(int x, int y, bool alive, int size, bool trace,bool visited);
	Cell();
	bool isAlive();
	void setAlive(bool alive);
	bool isVisited();
	void setVisited(bool visited);


	RectangleShape* getShape();
	void draw(RenderWindow &window);

};