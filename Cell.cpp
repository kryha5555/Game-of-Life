#include "Cell.hpp"

using namespace sf;

Cell::Cell(int x, int y, bool alive, int size, bool trace, bool visited)
{
	shape = RectangleShape(Vector2f(size, size));
	shape.setOutlineThickness(-0.5);
	shape.setOutlineColor(Color::Color(100, 100, 100));
	shape.setPosition(x, y);

	this->alive = alive;
	this->trace = trace;
	this->visited = alive;
	if (alive)
		shape.setFillColor(Color::Black);
	else
		shape.setFillColor(Color::White);
}

Cell::Cell() {}

bool Cell::isAlive()
{
	return alive;
}

void Cell::setAlive(bool alive_)
{
	this->alive = alive_;

	if (alive)
		shape.setFillColor(Color::Black);
	else if (visited && trace)
		shape.setFillColor(Color::Color(180, 180, 180));
	else 
		shape.setFillColor(Color::White);
}

bool Cell::isVisited()
{
	return visited;
}

void Cell::setVisited(bool visited_)
{
	this->visited = visited_;
	if (alive)
		shape.setFillColor(Color::Black);
	else if (visited && trace)
		shape.setFillColor(Color::Color(180, 180, 180));
	else
		shape.setFillColor(Color::White);

}



RectangleShape* Cell::getShape()
{
	return &shape;
}

void Cell::draw(RenderWindow &window)
{
	window.draw(shape);
}