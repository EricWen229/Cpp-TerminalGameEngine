run :
	g++ -c -ggdb test.cpp
	g++ -c -ggdb Able.cpp
	g++ -c -ggdb Fly.cpp
	g++ -c -ggdb Screen.cpp
	g++ -c -ggdb Control.cpp
	g++ -c -ggdb GTexture.cpp
	g++ test.o Able.o Fly.o Screen.o Control.o GTexture.o -o main.o -lsfml-graphics -lsfml-window -lsfml-system
	./main.o

clean :
	- rm *.o
