run : clean main.o
	./main.o

main.o :
	g++ -std=c++11 -ggdb -lpthread main.cpp Future.cpp ../Semaphore/Semaphore.cpp -o main.o

clean :
	- @ rm *.o
