objects = /CPP/lib/libcppunit.a main.cpp ObjectDynamic.cpp Example.cpp

run : clean exMain.o
	valgrind --tool=memcheck --leak-check=full ./exMain.o

exMain.o : exMain.cpp Example.cpp ObjectDynamic.cpp
	g++ -std=c++11 -ggdb exMain.cpp Example.cpp ObjectDynamic.cpp -o exMain.o

test : clean main.o
	valgrind --tool=memcheck --leak-check=full ./main.o
	./main.o

main.o : main.cpp ObjectDynamic.cpp
	g++ -ggdb -std=c++11 -L $(objects) -lcppunit -ldl -o main.o

clean :
	- rm *.o
