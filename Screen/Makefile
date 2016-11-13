clean :
	- rm *.o

Screen.o : Screen.cpp
	g++ -std=c++11 -ggdb Screen.cpp -o Screen.o

simpleTest.o : Array.h simpleTest.cpp
	g++ -std=c++11 -ggdb simpleTest.cpp -o simpleTest.o

simpleTest : clean simpleTest.o
	valgrind --leak-check=full --tool=memcheck ./simpleTest.o

ncurses.o : clean ncurses.cpp
	g++ -std=c++11 -ggdb ncurses1.cpp -lncurses -o ncurses.o
	./ncurses.o
