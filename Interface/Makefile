compile : clean test.cpp
	g++ test.cpp ../EventBuffer/EventBuffer.cpp ../Semaphore/Semaphore.cpp Interface.cpp -std=c++11 -ggdb -lpthread -lncurses -o test.o

clean :
	- rm *.o
	- rm res

run : compile
	valgrind --leak-check=full --show-leak-kinds=all --log-file=res --tool=memcheck ./test.o
