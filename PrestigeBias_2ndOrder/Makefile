C = gcc
OBJS = prestigebias.o mt19937ar.o main.o
TARGET = main
#CFLAGS = -Wall -g -lm
CFLAGS = -Wall -g


$(TARGET):$(OBJS)
	$(CC) $(OBJS) $(CFLAGS) -o $(TARGET) -lm

clean:
	rm *.o
