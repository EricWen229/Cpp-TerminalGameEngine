run : clean test.o
	valgrind --tool=helgrind --log-file="res" ./test.o

test.o: test.cpp MailBox.cpp ../../Semaphore/Semaphore.cpp ../../Dynamic/Dynamic.cpp
	g++ test.cpp MailBox.cpp ../../Semaphore/Semaphore.cpp ../../Dynamic/Dynamic.cpp -std=c++11 -ggdb -lpthread -o test.o

clean:
	- rm *.o
	- rm res
