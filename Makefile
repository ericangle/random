all:
	g++ -c -o box.o Box.cpp
	g++ -c -o main.o main.cpp 
	g++ -o executable box.o main.o
clean:
	rm *.o
	rm executable 
