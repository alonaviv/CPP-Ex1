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


/* y-coordinate Point comparator. Points are compared by the y coordinate,
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

/*
 * Compares two points according to their polar angle in comparison to a pivot.
 * This is done by calculating the slope of the vector connecting each point to
 * the pivot, and using the slope in order to compare the two. If the slope is
 * smaller, so is the polar angle. If one of the points is on the same line of
 * the pivot, the result is decided according to the location of that point in
 * comparison to the pivot on the x axis: to the right of the pivot - always
 * smaller, to the left - always larger.
 */
bool polarAngleComparator(const Point*& p1, const Point*& p2, const Point* pivot)
{
	if(p1 -> getY() == pivot -> getY())
	{
		return p1 -> getX() >= pivot -> getX();
	}
	
	if(p2 -> getY() == pivot -> getY())
	{
		return !(p2 -> getX() >= pivot -> getX());
	}

	double slope1 = (p1 -> getX() - pivot -> getX()) /(double) (p1 -> getY() - pivot -> getY());
	double slope2 = (p2 -> getX() - pivot -> getX()) /(double) (p2 -> getY() - pivot -> getY());
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
 */
int grahmScanSort(PointSet& set)
{
	cout << "entered grahm scan"<<endl;
	int i = 1;
	int hullSize = 0; // For index conveniance, the hull size is counted from
	                  // 0. The actual size will be returned incremented by 1.
	
	// Taking care of the point in index 1. Using the last point in the set as
	// the predecessor to the first (pivot) point.
	//TODO deal with same line
	cout << "Before first point. Comparing " << set[set.size()-1] -> toString() << ", " << set[0] -> toString() << " and " << set[1] -> toString() <<". Result is "<< getTurnDirection(set[set.size() - 1], set[0], set[1]) << endl;
	while(getTurnDirection(set[set.size() - 1], set[0], set[1]) < 0 and i < set.size())
	{
	cout << "In loop. Comparing " << set[set.size()-1] -> toString() << ", " << set[0] -> toString() << " and " << set[1] -> toString() <<". Result is "<< getTurnDirection(set[set.size() - 1], set[0], set[1]) << endl;
		i++;
		cout << "done with loop iteration. Increased i to " << i << endl;
	}
cout << "Done with loop. i is " << i <<". Hull size is " << hullSize << endl;
	hullSize++;
	set.swapSet(hullSize, i);
	cout << "incremented hull size to " << hullSize<<" and swaped hull and i. " << endl;
	
	cout << endl << "Starting main portion: "<<endl<<endl;

	//Iterating over the rest of the points.
	for(i++ ; i < set.size(); i++)
	{
		cout <<endl<< "Starting loop iteration. i is " <<i<<". Hull size is "<< hullSize<<". Set size(static) is "<<set.size()<<endl;
	cout << "Before Inner loop. Comparing " << set[hullSize-1] -> toString() << ", " << set[hullSize] -> toString() << " and " << set[i] -> toString() <<". Result is "<< getTurnDirection(set[hullSize-1], set[hullSize], set[i])<<endl; 
		while(getTurnDirection(set[hullSize-1], set[hullSize], set[i]) < 0)
		{
	cout << "Inner loop. Comparing " << set[hullSize-1] -> toString() << ", " << set[hullSize] -> toString() << " and " << set[i] -> toString() <<". Result is "<< getTurnDirection(set[hullSize-1], set[hullSize], set[i])<<endl; 
			if(i == set.size() -1) //on last point, no need to decrement.
			{
				cout << "got to last point. breaking out of function and returning " <<hullSize + 1 <<endl;
				return ++hullSize;
			}
			hullSize--;
			cout << "decreased hull size. It is now "<<hullSize<<endl;
		}
		hullSize++;
			cout << "increased hull size. It is now "<<hullSize<<endl;
		cout << "swapping between index hull size, which is "<< hullSize<< " and index i, which is "<<i<<endl;
		set.swapSet(hullSize, i);
	}
	
	cout << "done with it all. Returning " <<hullSize+1 << endl;
	return ++hullSize;	
}


int main()
{

	string line, coordinateInput;
	Point* point;
	istringstream stream;
	int x, y;
	while(getline(cin, line)
	{
		stream.str(line);
		getline(stream, coordinateInput, ','));
		x = stoi(coordinateInput);
		getline(stream, coordinateInput, ','));
		x = stoi(coordinateInput);
			
		
	const Point* min = s.getMinimum(yCoordinateComparator);
	cout <<	"Minimum is : " << min -> toString() << endl;
	PointSet::PivotComparator comparator(min, polarAngleComparator);
	s.sortSet(comparator);
	cout << "Set after first sort:"<<endl<<endl;
	for(int i=0;i<s.size();i++)
	{
		cout << "Point "<< i<<": " << s[i] -> toString() << endl; 
	}
	cout << "Hull size is "<< grahmScanSort(s)<<endl<<endl;
	for(int i=0;i<s.size();i++)
	{
		cout << "Point "<< i<<": " << s[i] -> toString() << endl; 
	}

}
