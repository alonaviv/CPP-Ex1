CC = g++
FLAGS = -Wextra -Wall -Wvla -pthread -std=c++11
FILES = ConvexHull.o Point.o PointSet.o

ConvexHull: $(FILES) 
	$(CC) $(FLAGS) $(FILES) -o ConvexHull 

PointSetBinaryOperations: Point.o PointSet.o PointSetBinaryOperations.o
	$(CC) $(FLAGS) PointSetBinaryOperations.o Point.o PointSet.o -o PointSetBinaryOperations 	

GDBPointSetBinaryOperations: Point.o PointSet.o PointSetBinaryOperations.o
	$(CC) $(FLAGS) -g PointSetBinaryOperations.o Point.o PointSet.o -o GDBPointSetBinaryOperations 	

ConvexHull.o: ConvexHull.cpp
	$(CC) $(FLAGS) -c ConvexHull.cpp

PointSetBinaryOperations.o: PointSetBinaryOperations.cpp
	$(CC) $(FLAGS) -c PointSetBinaryOperations.cpp

Point.o: Point.cpp
	$(CC) $(FLAGS) -c Point.cpp

PointSet.o: PointSet.cpp
	$(CC) $(FLAGS) -c PointSet.cpp

clean:
	rm ConvexHull $(FILES)
