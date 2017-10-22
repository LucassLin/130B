CC = g++
CFLAGS = -g -O2
DEPS = Disjoint.h
OBJECTS = main.o

main.exe : $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o prog2

%.o : %.c
	$(CC) $(CFLAGS) -c $<