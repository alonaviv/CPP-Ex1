//Point.cpp

#include "Point.h"
#include <string>
#include <sstream>

using namespace std;

// -------------------------------------------------------------------------------
// This file contains the implementaion of the class Point.
// -------------------------------------------------------------------------------

Point::Point(int x, int y): _x(x), _y(y){}

int Point::getX() const
{
	return _x;
}

int Point::getY() const
{
	return _y;
}


void Point::set(int x, int y)
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
