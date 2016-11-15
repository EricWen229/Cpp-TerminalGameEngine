compile : clean test.cpp
	g++ test.cpp ../EventBuffer/EventBuffer.cpp ../Semaphore/Semaphore.cpp Interface.cpp -std=c++11 -ggdb -lpthread -lncurses -o test.o

clean :
	- rm *.o

run : compile
	valgrind --tool=memcheck ./test.o
