run : clean main.o
	valgrind --tool=memcheck --leak-check=full ./main.o

clean :
	- rm *.o

main.o :
	g++ -std=c++11 -ggdb main.cpp Example.cpp ObjectDynamic.cpp -o main.o
