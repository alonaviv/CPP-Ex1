//Point.cpp

#include "Point.h"
#include <string>
#include <sstream>

using namespace std;

// -------------------------------------------------------------------------------
// This file contains the implementation of the class Point.
// -------------------------------------------------------------------------------

/**
 * Constructor with given coordinates
 */
Point::Point(const int x, const int y): _x(x), _y(y){}

/**
 * Copy constructor
 */
Point::Point(const Point& point): _x(point.getX()), _y(point.getY()){}

/**
 * Getter for the x coordinate
 */
int Point::getX() const
{
	return _x;
}

/**
 * Getter for the y coordinate
 */
int Point::getY() const
{
	return _y;
}

/**
 * Sets the coordinates to given values
 */
void Point::set(const int x, const int y)
{
	_x = x;
	_y = y;
}

/**
 * Returns the coordinates of the point as a string
 */
string Point::toString() const
{
	ostringstream output;
	output << _x << "," << _y;
	return output.str();
}

/** Two points are equal if they have the same coordinates */
bool Point::operator==(const Point &other) const
{
	return _x == other.getX() and _y == other.getY();
}
