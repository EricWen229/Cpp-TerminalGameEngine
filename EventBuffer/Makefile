objects = /CPP/lib/libcppunit.a main.cpp EventBuffer.cpp ../Semaphore/Semaphore.cpp

main.o :
	g++ -ggdb -std=c++11 -L $(objects) -lcppunit -ldl -pthread -o main.o
	valgrind --tool=helgrind --log-file="res" ./main.o

clean :
	- @ rm *.o
	- @ rm res
