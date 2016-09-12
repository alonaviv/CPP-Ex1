// Point.h
#ifndef POINT_H
#define POINT_H

#include <string>

using namespace std;
/**
 * This class represents a single point in a two dimensional space, with (x,y)
 * coordinates.
 */

class Point
{
public:

	/**
	 * Constructor with given coordinates
	 */
	Point(int x, int y);

	/** 
	 * Sets the coorditantes to given values
	 */
	void set(int x, int y);

	/**
	 * Getter for the x coordinate.
	 * @return The x coordinate
	 */
	int getX() const;

	/**
	 * Getter for the y coordinate
	 * @return The y coordinate
	 */
	int getY() const; 
	
	/**
	 * Returns the coordinates as a string in the format "<x>,<y>"
	 */
	string toString() const;

private:

	int _x;
	int _y;
	
};
	
#endif 
