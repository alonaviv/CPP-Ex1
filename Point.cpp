//Point.cpp

#include "Point.h"
#include <string>
#include <sstream>

using namespace std;

// -------------------------------------------------------------------------------
// This file contains the implementation of the class Point.
// -------------------------------------------------------------------------------

Point::Point(const int x, const int y): _x(x), _y(y){}

Point::Point(const Point& point): _x(point.getX()), _y(point.getY()){}

int Point::getX() const
{
	return _x;
}

int Point::getY() const
{
	return _y;
}


void Point::set(const int x, const int y)
{
	_x = x;
	_y = y;
}


string Point::toString() const
{
	ostringstream output;
	output << _x << "," << _y;
	return output.str();
}

bool Point::operator==(const Point &other) const
{
	return _x == other.getX() and _y == other.getY();
}
