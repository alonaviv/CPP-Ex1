// PointSet.cpp
#include <typeinfo>
#include "PointSet.h"
#include <string>
#include <algorithm>
#include <cstdlib> /* Using c-style memory allocation in order to control the
			    	  allocation and resizing of the array.*/
#include <cassert> /* Using c-style assertion, as static assertion is not what
					  is needed in this case. I'm looking for runtime error
					  checking. */
using namespace std;

// --------------------------------------------------------------------------------------
// This file contains the implementation of the class Point.
// --------------------------------------------------------------------------------------


/* PointerSet is implemented as a vector: an array of pointers to Point objects
 * that doubles in size whenever the size of the array is maxed. The array size
 * starts at 10, fairly arbitrarily. 
 */
static const int ARRAY_STARTING_SIZE = 10;
static const int ARRAY_INCREASE_FACTOR = 2;

/**
 * Constructs the with the given values
 */
PointSet::PointSet(const int setSize, const int arraySize):_setSize(setSize), _arraySize(arraySize) 
{
	/* Using the c-style malloc in order to allocate an array to hold the Point
	 * objects, without initializing any such object yet. The c-style is also
	 * used in order to efficiently resize the array later on. */
	if((_array = (const Point**)malloc(sizeof(Point*) * _arraySize)) == nullptr)
	{
		exit(1);
	}
}


/**
 * Default constructor
 */
PointSet::PointSet():PointSet(0, ARRAY_STARTING_SIZE){}

/**
 * Copy constructor
 */
PointSet::PointSet(const PointSet& other):PointSet(other._setSize, other._arraySize)
{
	for(int i = 0; i < _setSize; i++)
	{
		_array[i] = new Point(*other._array[i]);
	}
}


/**
 * Destructor
 */
PointSet::~PointSet()
{
	for(int i = 0; i < _setSize; i++)
	{
		delete(_array[i]);
	}
	free(_array);
}


/** Returns the index of given point within the array. Returns -1 if no
 * Point is found. */
int PointSet::getIndex(const Point& point) const
{
	for(int i = 0; i < _setSize; i++)
	{
		if(_array[i] -> getX() == point.getX() and _array[i] -> getY() == point.getY())
		{
			return i;
		}
	}
	return POINT_NOT_FOUND;
}


/** Adds point to the end of the array. The add function creates a new Point
 * object, and stores its pointer in the array. The destructor frees the memory
 * of this new object. The memory management of the given point is up to the
 * caller. The size of the array is doubled if the
 * current capacity has been maximized.
 */
bool PointSet::add(const Point& point)
{
	if(getIndex(point) != POINT_NOT_FOUND)
	{
		return false;
	}

	if(_arraySize == _setSize)
	{
		_arraySize *= ARRAY_INCREASE_FACTOR; 
		if((_array = (const Point**)realloc(_array, _arraySize * sizeof(Point*))) == nullptr)
		{
			exit(1);
		}
	}

	_array[_setSize] = new Point(point); 
	_setSize++;
	return true;
}

/**
 * Prints the coordinates of all the points in the set 
 */
string PointSet::toString() const
{
	string result = "";
	for(int i = 0; i < _setSize; i++)
	{
		result += _array[i] -> toString() + "\n";
	}
	return result;
}


/** Removes the given point by moving all following points within the array one
 * cell back. The cell that had the last point receives a nullptr instead */
bool PointSet::remove(const Point& point)
{
	int pointIndex = getIndex(point);
	if(pointIndex == POINT_NOT_FOUND)
	{
		return false;
	}

	delete(_array[pointIndex]);

	int i;
	for(i = pointIndex + 1; i < _setSize; i++)
	{
		_array[i-1] = _array[i];
	}
	_setSize --;
	return true;
}


/** Removes the last n points from the set. Requires n to be smaller or
 * equal to the size of the set */
void PointSet::trim(const int n)
{
	for(int i = 0; i < n; i++)
	{
		delete(_array[_setSize-1-i]);
		_array[_setSize-1-i] = nullptr;
	}
	_setSize -= n;
}


/** Returns the number of points currently in the set*/
int PointSet::size() const
{
	return _setSize;
}


/**
 * Returns the minimal point in the set according to the given comparator
 * function. Returns a nullptr if set is empty.
 */
const Point* PointSet::getMinimum(bool (*const comparatorFunction)(const Point*& p1,
                                  const Point*& p2)) const
{
	if(_setSize == 0)
	{
		return nullptr;
	}
	return *min_element(_array, _array + _setSize,
			*comparatorFunction);
}


/**
 * Sorts the set according to the given PivotComparator object.
 */
void PointSet::sortSet(const PivotComparator& comparator)
{
	sort(_array, _array + _setSize, comparator);
}


/**
 * Sorts the set according to a given boolean function
 */
void PointSet::sortSet(bool (*const comparator)(const Point*& p1, const Point*& p2))
{
	sort(_array, _array + _setSize, comparator);
}



/**
 * The constructor receives a pivot point and a boolean
 * function that performs a comparison between two points, given the known
 * pivot point.
 */
PointSet::PivotComparator::PivotComparator(const Point& pivot, 
                                           bool(*const comparatorFunction)(const Point*& p1,
                                           const Point*& p2, const Point& pivot)):
                                           _pivot(pivot), _comparatorFunction(comparatorFunction){} 


/**
 * Overloads the () operator in order to provide the functor capability.
 * Calling the object using () will result in comparing two objects given
 * the pivot, according to the comparator function held by the object
 */
bool PointSet::PivotComparator::operator()(const Point*& p1, const Point*& p2) const
{
	return _comparatorFunction(p1, p2, _pivot);
}


/** Returns the pointer in the given index. */
const Point* PointSet::operator[] (const int index)
{
	assert(_validIndex(index));
	return _array[index];
}


/** Swaps between the location of two points in the set, according to the
 * given indexes */
void PointSet::swapPoints(const int i, const int j)
{
	
	assert(_validIndex(i) and _validIndex(j));
	swap(_array[i], _array[j]);
}


/** Checks if the given index exists in the array */
bool PointSet::_validIndex(int index) const
{
	return 0 <= index and index < _setSize;
}


/** Checks if the given set has the exact same points as self, disregarding
 * order */
bool PointSet::_isSameSet(const PointSet& other) const
{
	if(_setSize != other.size())
	{
		return false;
	}

	for(int i = 0; i < _setSize; i++)
	{
		if(other.getIndex(*_array[i]) == POINT_NOT_FOUND)
		{
			return false;
		}
	}
	return true;
}


/**
 * Destroys current set and reloads it with the points in the given set,
 * with the same order
 */
bool PointSet::operator==(const PointSet& other) const
{
	return _isSameSet(other);
}


/**
 * Standard != overloader. Returns true iff both sets don't contain exactly
 * the same points (disregarding the order within the sets)
 */
bool PointSet::operator!=(const PointSet& other) const
{
	return !_isSameSet(other);
}


/** 
 * Returns a new PointSet object containing all the points in self,
 * excluding the points in the given set.
 */
PointSet PointSet::operator-(const PointSet& other) const
{
	PointSet newSet;

	for(int i = 0; i <  _setSize; i++)
	{
		if(other.getIndex(*_array[i]) == POINT_NOT_FOUND)
		{
			newSet.add(*_array[i]);
		}
	}
	return newSet;
}


/** 
 * Returns a new PointSet object containing all the points that are both in self,
 * and in the given set.
 */
PointSet PointSet::operator&(const PointSet& other) const
{
	PointSet newSet;

	for(int i = 0; i < _setSize; i++)
	{
		if(other.getIndex(*_array[i]) != POINT_NOT_FOUND)
		{
			newSet.add(*_array[i]);
		}
	}
	return newSet;
}


/** Swaps between the data of the given sets. */
void swapSets(PointSet& a, PointSet& b)
{
	swap(a._setSize, b._setSize);
	swap(a._arraySize, b._arraySize);
	swap(a._array, b._array);
	
}


PointSet& PointSet::operator=(PointSet other)
{
	swapSets(*this, other);
	return *this;
}
