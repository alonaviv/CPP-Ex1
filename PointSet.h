// PointSet.h
#ifndef POINT_SET_H
#define POINT_SET_H

#include <string>
#include "Point.h"

using namespace std;

static const int POINT_NOT_FOUND = -1;
/**
 * This class represents an ordered set of Point objects, with no duplicates.
 */

class PointSet
{
public:

	/** Functor object for comparing two points according to a known pivot
	 * point. To be used in the sort method. 
	 */
	class PivotComparator
	{

	public:
		/**
		 * The constructor receives a pivot point and a boolean
		 * function that performs a comparison between two points, given the known
		 * pivot point.
		 */
		PivotComparator(const Point& pivot, bool (*const comparatorFunction)(const
					Point*& p1, const Point*& p2, const Point& pivot));

		/**
		 * Overloads the () operator in order to provide the functor capability.
		 * Calling the object using () will result in comparing two objects given
		 * the pivot, according to the comparator function held by the object
		 */
		bool operator()(const Point*& p1, const Point*& p2) const;

	private:
		const Point& _pivot;
		bool (* const _comparatorFunction)(const Point*& p1, const Point*& p2, const Point& pivot);
	};

	/**
	 * Constructor
	 */
	PointSet();

	/**
	 * Destructor
	 */
	~PointSet();

	/**
	 * Returns a string specifying the coordinates of all Points in the set
	 */ 
	string toString() const; 
	
	/**
	 * Adds given point to the set iff it doesn't currently exist in the set. 
	 * @return True iff Point was added to the set
	 */
	bool add(const Point& point);
	
	/**
	 * Removes given point from the set.
	 * @return True iff point was removed from the set(i.e. if it was in the
	 * set to begin with
	 */
	bool remove(const Point& point);

	/** Removes the last n points from the set. Requires n to be smaller or
	 * equal to the size of the set */
	void trim(const int n);
	
	/** Returns the number of points currently in the set*/
	int size() const;

	/**
	 * Sorts the set according to the given PivotComparator object.
	 */
	void sortSet(const PivotComparator& comparator);

	/**
	 * Sorts the set according to a given boolean function
	 */
	void sortSet(bool (*const comparator)(const Point*& p1, const Point*& p2));

	/**
	 * Returns the minimal point in the set according to the given comparator
	 * function. Returns a nullptr if set is empty.
	 */
	const Point* getMinimum (bool (*const comparatorFunction)(const Point*& p1, const Point*& p2)) const;
	
	/** Returns the pointer in the given index. */
	const Point* operator[] (const int index); 

	/** Swaps between the location of two points in the set, according to the
	 * given indexes */
	void swapSet(const int i, const int j);

private:
	int _setSize;
	int _arraySize;
	const Point * * _array;
	int _iteratorIndex;
	
	/** Returns the index of given point within the array. Returns -1 if no
	 * Point is found. */
	int _getIndex(const Point& point) const;	

	/** Checks if the given index exists in the array */
	bool _validIndex(int index) const;
};
#endif
