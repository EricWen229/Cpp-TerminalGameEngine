objects = /CPP/lib/libcppunit.a main.cpp MailBox.cpp ../Semaphore/Semaphore.cpp ../Dynamic/Dynamic.cpp

run : clean main.o
	valgrind --tool=memcheck ./main.o
	valgrind --tool=helgrind --log-file=res ./main.o

main.o : clean main.cpp MailBox.cpp ../Semaphore/Semaphore.cpp ../Dynamic/Dynamic.cpp
	g++ -ggdb -std=c++11 -L $(objects) -lcppunit -ldl -pthread -o main.o

test : clean test.o
	valgrind --tool=helgrind --log-file="res" ./test.o
	valgrind --tool=memcheck ./test.o

test.o :
	g++ test.cpp MailBox.cpp ../Semaphore/Semaphore.cpp ../Dynamic/ObjectDynamic.cpp -std=c++11 -ggdb -lpthread -o test.o

clean:
	- rm *.o
	- rm res
