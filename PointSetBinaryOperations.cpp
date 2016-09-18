//PointSetBinaryOperations.cpp

/** This file tests the different binary operations within PointSet */

#include <iostream> 
#include "Point.h"
#include "PointSet.h"
using namespace std;


int main()
{
	// Setting up points and adding them to sets.
	Point p1(1,13);
	Point p2(3,14);
	Point p3(4,13);
	Point p4(3,8);
	Point p5(4,8);
	Point p6(5,8);
	Point p7(6,8);
	Point p8(7,8);
	Point p9(8,8);
	Point p10(10,10);	

	PointSet set1; 
	set1.add(p1);
	set1.add(p2);
	set1.add(p3);
	set1.add(p4);
	set1.add(p5);
	set1.add(p6);
	set1.add(p7);
	set1.add(p8);
	
	PointSet set2;
	set2.add(p1);
	set2.add(p2);
	set2.add(p3);
	set2.add(p4);
	set2.add(p5);
	set2.add(p6);
	set2.add(p7);
	set2.add(p8);
	
	PointSet set3;
	set3.add(p1);
	set3.add(p2);
	set3.add(p3);
	set3.add(p4);
	set3.add(p5);
	set3.add(p6);
	set3.add(p7);
	set3.add(p9);

	cout << "Set 1 contains:" << endl << set1.toString() << endl;
	cout << "Set 2 contains:" << endl << set2.toString() << endl;
	cout << "Set 3 contains:" << endl << set3.toString() << endl;


	// Using equality and inequality operators	
	cout << "Are sets 1 and 2 equal? " << (set1 == set2) << endl;
	cout << "Are sets 1 and 3 equal? " << (set1 == set3) << endl;
	cout << "Are sets 1 and 3 not equal? " << (set1 != set3) << endl;
	
	cout << "Removing point " << p9.toString() << " from set 3" << endl;
	set3.remove(p9);

	cout << "Adding point " << p8.toString() << " to set 3" << endl;
	set3.add(p8);

	cout << "Are sets 1 and 3 equal now? " << (set1 == set3) << endl;

	cout << "Removing point " << p5.toString() << " from set 3" << endl;
	set3.remove(p5);

	cout << "Removing point " << p6.toString() << " from set 2" << endl;
	set2.remove(p6);
	cout << "Are sets 1 and 3 equal now? " << (set1 == set3) << endl;
	

	// Using '-' and '&' operators
	set3.add(p9);
	cout << "Here is the result of set3 - set1:" << endl << (set3 - set1).toString() << endl;
	
	cout << "Creating set 4 - an empty set" << endl;
	PointSet set4;
	cout << "This is the current content of set 3" << endl << set3.toString() << endl;
	cout << "Here is the result of set4 - set3:" << endl << (set4 - set3).toString() << endl;
	cout << "Here is the result of set3 - set4:" << endl << (set3 - set4).toString() << endl;

	cout << "Adding point " << p10.toString() << " to set 1" << endl;
	set1.add(p10);	

	cout << "This is the current content of set 1: " << endl << set1.toString() << endl;
	cout << "Here is the result of setl & set3:" << endl << (set1 & set3).toString() << endl;
	cout << "Here is the result of set1 & set4:" << endl << (set1 & set4).toString() << endl;


	//Using the assignment operator
	cout << "This is the current content of set 1" << endl << set1.toString() << endl;
	cout << "This is the current content of set 2" << endl << set2.toString() << endl;
	cout << "This is the current content of set 3" << endl << set3.toString() << endl;

	set3 = set1;
	cout << "After assigning set1 to set3, this is the contents of set3:" << set3.toString() << endl;
	cout << "Did set1 stay the same? "<< set1.toString() << endl;

	set2 = set2;
	cout << "After assigning set2 to set2, this is the contents of set2:" << set2.toString() << endl;

	set1 = set3;
	cout << "After assigning set3 to set1, this is the contents of set1:" << set1.toString() << endl;
	cout << "Did set3 stay the same? "<< set3.toString() << endl;
}
