CC = g++
CFLAGS = -g -O2
OBJECTS = main.o

main.exe : $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o prog1

%.o : %.c
	$(CC) $(CFLAGS) -c $<
