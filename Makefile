clean :
	- rm *.o

Screen.o : Screen.cpp
	g++ -std=c++11 -ggdb Screen.cpp -o Screen.o

simpleTest.o : Array.h simpleTest.cpp
	g++ -std=c++11 -ggdb simpleTest.cpp -o simpleTest.o

simpleTest : clean simpleTest.o
	valgrind --tool=memcheck ./simpleTest.o

ncurses.o : ncurses.cpp
	g++ -std=c++11 -ggdb ncurses.cpp -lncurses -o ncurses.o
