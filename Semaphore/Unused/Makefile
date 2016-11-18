run : compile
	valgrind --tool=helgrind --log-file="res" ./test.o

compile: clean test.cpp Semaphore.cpp
	g++ test.cpp Semaphore.cpp -std=c++11 -ggdb -lpthread -o test.o

clean:
	- rm *.o
	- rm res
