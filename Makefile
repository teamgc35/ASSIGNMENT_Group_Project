CC = gcc
AR = ar
CFLAGS = -g -Wall -ansi -Wextra -std=c99 
SRC = $(wildcard ./src/*.c)
OBJ = $(patsubst %.c, %.o, $(SRC))
INCLUDE = ./include 

.PHONY: $(OBJ)

*.o: $(SRC)
	$(CC) $(CFLAGS) -o $@ $^ -I $(INCLUDE)