RUN : clean
	g++ -ggdb -std=c++11 testAlloc.cpp ../MailBox/MailBox.cpp ../Interface/Interface.cpp ../Dynamic/Dynamic.cpp ../Semaphore/Semaphore.cpp -lncurses -lpthread -o test.o
	./test.o

run : clean test.o
	valgrind --show-leak-kinds=all --leak-check=full --tool=memcheck --log-file=res ./test.o

clean :
	- rm *.o
	- rm res
	- rm logFile

test.o : test.cpp Screen.cpp ../Interface/Interface.cpp ../MailBox/MailBox.cpp ../Semaphore/Semaphore.cpp ../Dynamic/Dynamic.cpp
	g++ -std=c++11 -ggdb test.cpp Screen.cpp ../Interface/Interface.cpp ../MailBox/MailBox.cpp ../Dynamic/Dynamic.cpp ../Semaphore/Semaphore.cpp -lpthread -lncurses -o test.o
