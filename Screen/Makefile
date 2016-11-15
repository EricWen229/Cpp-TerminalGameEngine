clean :
	- rm *.o

compile :
	g++ -std=c++11 -ggdb test.cpp Screen.cpp ../Interface/Interface.cpp ../EventBuffer/EventBuffer.cpp ../Semaphore/Semaphore.cpp ../Array/Array.h -lpthread -lncurses -o test.o

run : clean compile
	./test.o
