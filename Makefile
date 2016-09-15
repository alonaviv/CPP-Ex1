CC = g++
FLAGS = -Wextra -Wall -Wvla -pthread -std=c++11
FILES = ConvexHull.o Point.o PointSet.o
ConvexHull: $(FILES) 
	$(CC) $(FLAGS) $(FILES) -o ConvexHull 

ConvexHull.o: ConvexHull.cpp
	$(CC) $(FLAGS) -c ConvexHull.cpp

Point.o: Point.cpp
	$(CC) $(FLAGS) -c Point.cpp

PointSet.o: PointSet.cpp
	$(CC) $(FLAGS) -c PointSet.cpp

clean:
	rm ConvexHull $(FILES)
