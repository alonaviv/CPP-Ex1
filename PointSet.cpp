// PointSet.cpp
#include <typeinfo>
#include "PointSet.h"
#include <string>
#include <algorithm>
#include <cstdlib> /* Using c-style memory allocation in order to control the
			    	  allocation and resizing of the array.*/
#include <iostream> //TODO remove
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
static const int ARRAY_STARTING_SIZE = 1;//TODO change to 10
static const int ARRAY_INCREASE_FACTOR = 2;

PointSet::PointSet():_setSize(0), _arraySize(ARRAY_STARTING_SIZE), _iteratorIndex(0)
{
	/* Using the c-style malloc in order to allocate an array to hold the Point
	 * objects, without initializing any such object yet. The c-style is also
	 * used in order to efficiently resize the array latter on. */
	if((_array = (const Point**)malloc(sizeof(Point*) * ARRAY_STARTING_SIZE)) == nullptr)
	{
		exit(1);
	}
}

PointSet::~PointSet()
{
	for(int i=0; i<_setSize; i++)
	{
		delete(_array[i]);
	}
	free(_array);
}

int PointSet::getIndex(const Point& point) const
{
	for(int i=0; i<_setSize; i++)
	{
		if(_array[i] -> getX() == point.getX() and _array[i] -> getY() == point.getY())
		{
			return i;
		}
	}
	return POINT_NOT_FOUND;
}

/* Adds point to the end of the array. The add function creates a new Point
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

string PointSet::toString() const
{
	string result = "";
	for(int i=0; i<_setSize; i++)
	{
		result += _array[i] -> toString() + "\n";
	}
	return result;
}

/* Removes the given point by moving all following points within the array one
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
	for(i = pointIndex+1; i<_setSize; i++)
	{
		_array[i-1] = _array[i];
	}
	_array[i] = nullptr;
	_setSize --;
	return true;
}

void PointSet::trim(const int n)
{
	for(int i=0; i<n; i++)
	{
		delete(_array[_setSize-1-i]);
		_array[_setSize-1-i] = nullptr;
	}
	_setSize -= n;
}

int PointSet::size() const
{
	return _setSize;
}


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

void PointSet::sortSet(const PivotComparator& comparator)
{
	sort(_array, _array + _setSize, comparator);
}

void PointSet::sortSet(bool (*const comparator)(const Point*& p1, const Point*& p2))
{
	sort(_array, _array + _setSize, comparator);
}

PointSet::PivotComparator::PivotComparator(const Point& pivot, bool
		(*const comparatorFunction)(const Point*& p1, const Point*& p2, const Point&
			pivot)): _pivot(pivot), _comparatorFunction(comparatorFunction){} 

bool PointSet::PivotComparator::operator()(const Point*& p1, const Point*& p2) const
{
	return _comparatorFunction(p1, p2, _pivot);
}

const Point* PointSet::operator[] (const int index)
{
	assert(_validIndex(index));
	return _array[index];
}

void PointSet::swapSet(const int i, const int j)
{
	
	assert(_validIndex(i) and _validIndex(j));
	swap(_array[i], _array[j]);
}


bool PointSet::_validIndex(int index) const
{
	return 0 <= index and index < _setSize;
}


bool PointSet::_isSameSet(const PointSet& other) const
{
	if(_setSize != other.size())
	{
		return false;
	}

	for(int i=0; i<_setSize; i++)
	{
		if(other.getIndex(*_array[i]) == POINT_NOT_FOUND)
		{
			return false;
		}
	}
	
	return true;
}


bool PointSet::operator==(const PointSet& other) const
{
	return _isSameSet(other);
}

bool PointSet::operator!=(const PointSet& other) const
{
	return !_isSameSet(other);
}
