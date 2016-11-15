objects = /CPP/lib/libcppunit.a main.cpp Array.h

main.o :
	g++ -ggdb -std=c++11 -L $(objects) -lcppunit -ldl -o main.o

clean :
	- @ rm *.o

run : clean main.o
	valgrind --leak-check=full --tool=memcheck ./main.o
