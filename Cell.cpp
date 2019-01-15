#include "Cell.hpp"

using namespace sf;

Cell::Cell(int x, int y, bool alive_, int size, bool trace_)
{
	shape = RectangleShape(Vector2f(size, size));
	shape.setOutlineThickness(-0.5);
	shape.setOutlineColor(Color::Color(100, 100, 100));
	shape.setPosition(x, y);

	alive = alive_;
	trace = trace_;
	visited = alive;

	paint();
}

Cell::Cell() {}

bool Cell::isAlive()
{
	return alive;
}

void Cell::setAlive(bool alive_)
{
	alive = alive_;
	paint();
}

bool Cell::isVisited()
{
	return visited;
}

void Cell::setVisited(bool visited_)
{
	visited = visited_;
	paint();
}

void Cell::paint()
{
	if (alive)
		shape.setFillColor(Color::Black);
	else if (visited && trace)
		shape.setFillColor(Color::Color(180, 180, 180));
	else
		shape.setFillColor(Color::White);
}

void Cell::draw(RenderWindow &window)
{
	window.draw(shape);
}