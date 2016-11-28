objects = /CPP/lib/libcppunit.a main.cpp EventBuffer.cpp ../Semaphore/Semaphore.cpp

run : main.o
	valgrind --tool=helgrind --log-file="res" ./main.o
	valgrind --tool=memcheck ./main.o

main.o : clean main.cpp EventBuffer.cpp ../Semaphore/Semaphore.cpp
	g++ -ggdb -std=c++11 -L $(objects) -lcppunit -ldl -pthread -o main.o

clean :
	- @ rm *.o
	- @ rm res
