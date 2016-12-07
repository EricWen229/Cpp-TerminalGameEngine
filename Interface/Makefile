run : clean test.o
	valgrind --leak-check=full --show-leak-kinds=all --log-file=res --tool=memcheck ./test.o

test.o : test.cpp
	g++ test.cpp ../MailBox/MailBox.cpp ../Dynamic/ObjectDynamic.cpp ../Semaphore/Semaphore.cpp Interface.cpp -std=c++11 -ggdb -lpthread -lncurses -o test.o

clean :
	- rm *.o
	- rm res
