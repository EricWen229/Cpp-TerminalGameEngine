run : clean UnitTest.o
	valgrind --tool=memcheck --log-file="MemRes" ./UnitTest.o
	valgrind --tool=helgrind --log-file="HelRes" ./UnitTest.o

clean :
	- rm *.o
	- rm HelRes
	- rm MemRes

UnitTest.o :
	g++ -ggdb -std=c++11 -L /CPP/lib/libcppunit.a \
		UnitTest.cpp \
		Semaphore.cpp \
		-lcppunit -ldl -lpthread -o UnitTest.o
