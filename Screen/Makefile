run : clean test.o
	valgrind --show-leak-kinds=all --leak-check=full --tool=memcheck --log-file=res ./test.o

clean :
	- rm *.o
	- rm res

test.o : test.cpp Screen.cpp ../Interface/Interface.cpp ../EventBuffer/EventBuffer.cpp ../Semaphore/Semaphore.cpp
	g++ -std=c++11 -ggdb test.cpp Screen.cpp ../Interface/Interface.cpp ../EventBuffer/EventBuffer.cpp ../Semaphore/Semaphore.cpp -lpthread -lncurses -o test.o
