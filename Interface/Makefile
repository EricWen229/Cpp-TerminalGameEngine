run : clean Example.o
	valgrind --leak-check=full --show-leak-kinds=all --log-file=res --tool=memcheck ./Example.o

clean :
	- rm *.o
	- rm res

Example.o :
	g++ \
		Example.cpp \
		Interface.cpp \
		NoticeBoard.cpp \
		Sprite.cpp \
		../MailBox/MailBox.cpp \
		../Semaphore/Semaphore.cpp \
		../Dynamic/ObjectDynamic.cpp \
		../Array/Array.h \
		-std=c++11 -ggdb -lpthread -lncurses -o Example.o
