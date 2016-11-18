run : clean main.o
	valgrind --tool=memcheck --leak-check=full ./main.o

main.o : main.cpp Example.cpp Dynamic.cpp
	g++ -std=c++11 -ggdb main.cpp Example.cpp Dynamic.cpp -o main.o

clean :
	- rm *.o
