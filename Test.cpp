//PointSetBinaryOperations.cpp

/** This file tests the different binary operations within PointSet */

#include <iostream> 
#include "Point.h"
#include "Point.cpp"
using namespace std;

int main()
{
	Point p1(1,13);
	Point p2(3,14);
	Point p3(4,13);
	Point p4(3,8);
	Point p5(4,8);
	Point p6(5,8);
	Point p7(6,8);
	Point p8(7,8);
	Point p9(8,8);
	
	
	PointSet set1; 
	set1.add(p1);
	set1.add(p2);
	set1.add(p3);
	set1.add(p4);
	set1.add(p5);
	set1.add(p6);
	set1.add(p7);
	set1.add(p8);
	set1.add(p9);
	
	
	PointSet set2;
	set2.add(p1);
	set2.add(p2);
	set2.add(p3);
	set2.add(p4);
	set2.add(p5);
	set2.add(p6);
	set2.add(p7);
	set2.add(p8);
	set2.add(p9);
	
	cout << "Are both sets equal ?" << (set1 == set2) ? "yes":"no" << endl;
}


	
