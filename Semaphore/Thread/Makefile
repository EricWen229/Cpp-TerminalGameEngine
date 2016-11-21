run : clean test.o
	./test.o

test.o: test.cpp Thread.cpp
	g++ test.cpp Thread.cpp -std=c++11 -ggdb -lpthread -o test.o

clean:
	- rm *.o
