C = gcc
OBJS = prestigebias.o mt19937ar.o main.o
TARGET = main
#CFLAGS = -Wall -g -lm
CFLAGS = -Wall -g


$(TARGET):$(OBJS)
	$(CC) $(OBJS) $(CFLAGS) -o $(TARGET) -lm

#prestigebias.c mt19937ar.c main.c: prestigebias.h


clean:
	rm *.o
