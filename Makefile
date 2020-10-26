CC = gcc
AR = ar
CFLAGS = -g -Wall -ansi -Wextra -std=c99 -DNDEBUG
SRC = $(wildcard ./src/*.c)
TEST_SRC = $(wildcard ./test/*.c)
INCLUDE = ./include
BUILD_DIR = ./build_debug
LIB_NAME = assignment

.PHONY: clean mkdirs objs static_lib test_case tbox payroll test

ALL: mkdirs test_case tbox payroll


objs: $(SRC)
	$(foreach FILE, $(SRC), \
		$(CC) $(CFLAGS) -c $(FILE) -o $(addprefix $(BUILD_DIR)/, $(patsubst %.c, %.o, $(notdir $(FILE)))) -I $(INCLUDE); \
	)

static_lib: objs
	$(AR) -rcs $(BUILD_DIR)/lib/lib$(LIB_NAME).a $(wildcard $(BUILD_DIR)/*.o)

test_case: static_lib
	$(foreach FILE, $(TEST_SRC), \
		$(CC) $(CFLAGS)  $(FILE) -o $(addprefix $(BUILD_DIR)/bin/, $(patsubst %.c, %, $(notdir $(FILE)))) -I $(INCLUDE) -L $(BUILD_DIR)/lib -l $(LIB_NAME);\
	)

tbox: $(BUILD_DIR)/lib/lib$(LIB_NAME).a tbox.c
	$(CC) $(CFLAGS) tbox.c -o $(BUILD_DIR)/bin/tbox -I $(INCLUDE) -L $(BUILD_DIR)/lib -l $(LIB_NAME)

payroll: $(BUILD_DIR)/lib/lib$(LIB_NAME).a payroll.c
	$(CC) $(CFLAGS) payroll.c -o $(BUILD_DIR)/bin/payroll -I $(INCLUDE) -L $(BUILD_DIR)/lib -l $(LIB_NAME)

mkdirs:
	$(shell mkdir -p $(BUILD_DIR)/lib $(BUILD_DIR)/bin $(BUILD_DIR)/include)

clean:
	rm $(BUILD_DIR)/*.o $(BUILD_DIR)/lib/* $(BUILD_DIR)/bin/*

test:
	$(foreach FILE, $(wildcard $(BUILD_DIR)/bin/TestCase*),\
		$(FILE); \
	)
