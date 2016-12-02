run : clean UnitTest.o
	valgrind --leak-check=full --tool=memcheck ./UnitTest.o

clean :
	- @ rm *.o

UnitTest.o :
	g++ -ggdb -std=c++11 -L /CPP/lib/libcppunit.a \
		UnitTest.cpp \
		Array.h \
		-lcppunit -ldl -o UnitTest.o
