CC = g++
FLAGS = -Wextra -Wall -Wvla -pthread -std=c++11
FILES = ConvexHull.o Point.o PointSet.o

all: ConvexHull PointSetBinaryOperations
	./PointSetBinaryOperations

ConvexHull: $(FILES) 
	$(CC) $(FLAGS) $(FILES) -o ConvexHull 

PointSetBinaryOperations: Point.o PointSet.o PointSetBinaryOperations.o
	$(CC) $(FLAGS) PointSetBinaryOperations.o Point.o PointSet.o -o PointSetBinaryOperations 	

ConvexHull.o: ConvexHull.cpp
	$(CC) $(FLAGS) -c ConvexHull.cpp

PointSetBinaryOperations.o: PointSetBinaryOperations.cpp
	$(CC) $(FLAGS) -c PointSetBinaryOperations.cpp

Point.o: Point.cpp
	$(CC) $(FLAGS) -c Point.cpp

PointSet.o: PointSet.cpp
	$(CC) $(FLAGS) -c PointSet.cpp

tar:
	tar -cvf ex1.tar  README Point.cpp Point.h PointSet.cpp PointSet.h PointSetBinaryOperations.cpp\
        ConvexHull.cpp Makefile extension.pdf
clean:
	rm $(FILES) ex1.tar ConvexHull  PointSetBinaryOperations.o PointSetBinaryOperations
