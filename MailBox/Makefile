run : clean memUnitTest helUnitTest memExample helExample

clean:
	- rm *.o

memUnitTest : UnitTest.o
	valgrind --tool=memcheck ./UnitTest.o

helUnitTest : UnitTest.o
	valgrind --tool=valgrind ./UnitTest.o

memExample : Example.o
	valgrind --tool=memcheck ./Example.o

helExample : Example.o
	valgring --tool=helgring ./Example.o

UnitTest.o :
	g++ -ggdb -std=c++11 -L /CPP/lib/libcppunit.a \
		UnitTest.cpp \
		MailBox.cpp \
		../Semaphore/Semaphore.cpp \
		../Dynamic/ObjectDynamic.cpp \
		-lcppunit -ldl -pthread -o UnitTest.o

Example.o :
	g++ -ggdb -std=c++11 \
		Example.cpp \
		MailBox.cpp \
		../Semaphore/Semaphore.cpp \
		../Dynamic/ObjectDynamic.cpp \
		-lpthread -o Example.o
