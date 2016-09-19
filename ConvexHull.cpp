// ConvexHull.cpp

/* This program receives a list of points from the user. The Convex Hull of the
 * given points is calculated by the Grahm Scan algorithm, and the points
 * comprising the hull are returned to the user, sorted by the x coordinates,
 * and secondly by the y coordinates. 
 */
#include "Point.h"
#include "PointSet.h"
#include <iostream>
#include <sstream>
#include <string>

static const int MINIMAL_POINTS_IN_HULL = 3;

/** Custom modulu operation. Adds the sum of the modulu to the result in case of
 * a negative modulu result. This allows "looping around" for indexes, also in
 * the negative direction */
int modulu(const int a, const int b)
{
	int result = a % b;
	return (result < 0) ? result + b: result;
}


/** y-coordinate Point comparator. Points are compared by the y coordinate,
 * with ties broken by the x coordinate
 */
bool yCoordinateComparator(const Point*& p1, const Point*& p2)
{
	if(p1 -> getY() == p2 -> getY())
	{
		return p1 -> getX() < p2 -> getX();
	}
	return p1 -> getY() < p2 -> getY();
}


/** x-coordinate Point comparator. Points are compared by the x coordinate,
 * with ties broken by the y coordinate
 */
bool xCoordinateComparator(const Point*& p1, const Point*& p2)
{
	if(p1 -> getX() == p2 -> getX())
	{
		return p1 -> getY() < p2 -> getY();
	}
	return p1 -> getX() < p2 -> getX();
}


/**
 * Compares two points according to their polar angle in comparison to a pivot.
 * This is done by calculating the slope of the vector connecting each point to
 * the pivot, and using the slope in order to compare the two. If the slope is
 * smaller, so is the polar angle. If one of the points is on the same line of
 * the pivot, the result is decided according to the location of that point in
 * comparison to the pivot on the x axis: to the right of the pivot - always
 * smaller, to the left - always larger. If one of the points IS the pivot, it
 * is always the smallest.
 */
bool polarAngleComparator(const Point*& p1, const Point*& p2, const Point& pivot)
{
	if(*p1 == pivot)
	{
		return true;
	}

	if(*p2 == pivot)
	{
		return false;
	}
	
	if(p1 -> getY() == pivot.getY())
	{
		return p1 -> getX() > pivot.getX();
	}
	
	if(p2 -> getY() == pivot.getY())
	{
		return !(p2 -> getX() > pivot.getX());
	}

	double slope1 = (p1 -> getX() - pivot.getX()) / (double) (p1 -> getY() - pivot.getY());
	double slope2 = (p2 -> getX() - pivot.getX()) / (double) (p2 -> getY() - pivot.getY());
	return slope1 > slope2;
}

/** 
 * Checks what turn is formed with the line between the three given points.
 * Returns a positive number for a left turn, a negative for a right turn, and
 * 0 if all points are on the same line
 */
int getTurnDirection(const Point* p1, const Point* p2, const Point* p3)
{
	return (p2 -> getX() - p1 -> getX())*(p3 -> getY() - p1 -> getY()) - (p2 ->
			getY() - p1 -> getY())*(p3 -> getX() - p1 -> getX()); 
}


/** Receives a PointSet object with a pivot point located at the start of the
 * set. The pivot point is defined as the lowest and most left point in the
 * set. The function uses the Grahm Scan algorithm in order to locate the
 * points in the set which constitute the convex hull. These points are swapped
 * within the given set so they comprise the first M places, with M being the
 * number of points in the convex hull. This M is returned by the function.
 * The grahm scan algorithm was taken from the wikipedia article:
 * https://en.wikipedia.org/wiki/Graham_scan. The algorithm's complexity is 
 * dominated by the sort - so the complexity is O(n log n). The actual scan, 
 * after the sort is performed, is of complexity O(n).
 */
int grahmScanSort(PointSet& set)
{
	// No point in performing the algorithm for less than three points
	if(set.size() < MINIMAL_POINTS_IN_HULL)
	{
		return set.size();
	}
	
	
	int i = 1;
	int hullSize = 0; // For index convenience, the hull size is counted from
	                  // 0. The actual size will be returned incremented by 1.
	
	// Taking care of the point in index 1. Using the last point in the set as
	// the predecessor to the first (pivot) point.
	while(getTurnDirection(set[set.size() - 1], set[hullSize], set[i]) <= 0 and i < set.size() - 1)
	{
		i++;
	}
	hullSize++;
	set.swapPoints(hullSize, i);

	//Iterating over the rest of the points.
	for(i++ ; i < set.size(); i++)
	{
		while(getTurnDirection(set[modulu(hullSize-1, set.size())], set[hullSize], set[i]) <= 0)
		{
			hullSize--;
		}
		hullSize++;
		set.swapPoints(hullSize, i);
	}
	return ++hullSize; 
}

/**
* Main function - receives points from user and returns the convex hull 
*/
int main()
{
	/* Receiving input, creating corresponding Points, and adding them to the
	 * set. Since the set creates a copy of the points, original points are
	 * deleted */
	string line, coordinateInput;
	PointSet set;
	Point* newPoint;
	istringstream stream;
	int x, y;
	while(getline(cin, line))
	{	
		stream.str(line);
		getline(stream, coordinateInput, ',');
		x = stoi(coordinateInput);
		getline(stream, coordinateInput);
		y = stoi(coordinateInput);
		newPoint = new Point(x, y);
		set.add(*newPoint);		
		delete(newPoint);
		stream.clear();
	}
	
	/* Sorting set according to polar comparison to the pivot - the point with
	 * the lowest y (ties broken by x) */
	const Point* min = set.getMinimum(yCoordinateComparator);
	PointSet::PivotComparator polarComparator(*min, polarAngleComparator);
	set.sortSet(polarComparator);
	
	/*Running the grahm scan algorithm. The Points consisting the convex hull
	 * will be swapped to the start of the set */
	int hullSize = grahmScanSort(set);

	/* Trimming the set so only the points in the hull remain, sorting
	 * according to the x coordinate and printing. */
	set.trim(set.size()- hullSize);
	set.sortSet(xCoordinateComparator);
	cout << "result" << endl;
	cout << set.toString();
}
