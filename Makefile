main: main.cpp element.h element.o record.h
	g++ -o main main.cpp element.o `pkg-config --cflags --libs opencv4`

element.o: element.h element.cpp
	g++ -c element.cpp `pkg-config --cflags --libs opencv4`
