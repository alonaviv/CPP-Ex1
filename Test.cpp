#include <iostream> //TODO remove
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
	Point p79(8,8);
	
	PointSet s; 
	cout << "Removing from empty set: " << s.remove(p1) << endl;
	cout << s.add(p1) << endl;
	cout << s.add(p2) << endl;
	cout << s.add(p3) << endl;
	cout << s.add(p4) << endl;
	cout << s.add(p5) << endl;
	cout << s.add(p6) << endl;
	cout << s.add(p7) << endl;
	cout << s.add(p8) << endl;
	cout << s.add(p9) << endl;
	cout << s.add(p79) << endl;
	cout << s.toString() << endl;
	p1.set(48,50);
	cout << "size: " << s.size() << endl;
	cout << s.toString() << endl;
/*
	cout << s.remove(p1) << endl;
	cout << "size: " << s.size() << endl;
	cout << s.toString() << endl;

	cout << s.remove(p8) << endl;
	cout << "size: " << s.size() << endl;
	cout << s.toString() << endl;

	
	cout << s.remove(p9) << endl;
	cout << "size: " << s.size() << endl;
	cout << s.toString() << endl;

	cout << s.remove(p1) << endl;
	cout << s.toString() << endl;
	cout << s.remove(p2) << endl;
	cout << s.remove(p3) << endl;
	cout << s.remove(p4) << endl;
	cout << s.remove(p5) << endl;
	cout << s.remove(p6) << endl;
	cout << s.remove(p7) << endl;
	cout << s.remove(p9) << endl;
	cout << s.remove(p9) << endl;
	cout << s.remove(p79) << endl;
	cout << "size: " << s.size() << endl;
	cout <<"start"<< s.toString() <<"end";
*/
	s.grahmAlgorithmSort();
}

	
