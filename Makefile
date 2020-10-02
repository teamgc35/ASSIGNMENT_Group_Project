CC = gcc
AR = ar
DEBUG_CFLAGS = -g -Wall -Wextra -std=c99

INCLUDE_DIR = ./include
SRC_DIR = ./src
OBJ_OUTPUT = ./build/obj
SHARED_OUTPUT = ./build/lib
STATIC_OUTPUT = ./build/lib
BIN_OUTPUT = ./build/bin

PHONY:  as_encrypt.o as_compress.o libassignment testcase

all: libassignment_static libassignment_shared testcase

as_encrypt.o: $(SRC_DIR)/as_encrypt.c 
	$(CC) $(SRC_DIR)/as_encrypt.c -c $(CFLAGS) -o $(OBJ_OUTPUT)/as_encrypt.o -I $(INCLUDE_DIR)

as_compress.o: $(SRC_DIR)/as_compress.c 
	$(CC) $(SRC_DIR)/as_compress.c -c $(CFLAGS) -o $(OBJ_OUTPUT)/as_compress.o -I $(INCLUDE_DIR)

libassignment: 
	$(AR) -rcv $(STATIC_OUTPUT)/libassignment.a $(OBJ_OUTPUT)/*.o


testcase: ./test/TestCase.c 
	$(CC) ./test/TestCase.c $(CFLAGS) -L $(SHARED_OUTPUT) -l assignment -o $(BIN_OUTPUT)/TestCase -I $(INCLUDE_DIR)