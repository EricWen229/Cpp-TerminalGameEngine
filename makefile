TARGET = Example.o

BUILDDIR = ./build
SRCDIR = ./src
INCDIR = ./include

CC = g++
CFLAGS = -std=c++11 -I$(INCDIR)
LFLAGS = -lpthread -lncurses

SRCS = $(shell find $(SRCDIR) -name *.cpp)
INCS = $(shell find $(INCDIR) -name *.h)

$(BUILDDIR)/$(TARGET): $(SRCS) $(INCS)
	$(CC) $(SRCS) $(CFLAGS) $(LFLAGS) -o $@

.PHONY: run clean

clean:
	rm -f $(BUILDDIR)/*

run: $(BUILDDIR)/$(TARGET)
	$(BUILDDIR)/$(TARGET)

