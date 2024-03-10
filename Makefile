MKDIR=mkdir -p
CLEANUP=rm -rf

.PHONY: all
.PHONY: clean
.PHONY: test

.DEFAULT_GOAL := all

CC = gcc
CFLAGS = -Wall -g -fsanitize=address -fno-omit-frame-pointer
TEST_FLAGS = -lrt -lm -Iminunit $(CFLAGS)
CFLAGS += $(shell find $(SRC_DIR) -name "*.h" -type f -exec dirname {} \; | sort -u | sed 's/.*/-I&/')

SRC_DIR = src
OBJ_DIR = obj
BIN_DIR = bin
CHAR_DIR = .characters

TEST_FILE = test/test.c

SRCS := $(shell find $(SRC_DIR) -name '*.c')
TEST_SRCS := $(filter-out $(SRC_DIR)/main.c, $(SRCS))
OBJS := $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

TARGET = $(BIN_DIR)/dnd
TEST_TARGET = $(BIN_DIR)/test_suite

all: $(TARGET)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(MKDIR) $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

$(TARGET): $(OBJS)
	$(MKDIR) $(BIN_DIR)
	$(CC) $(CFLAGS) $^ -o $@

test: $(TEST_TARGET)
	./$(TEST_TARGET)

$(TEST_TARGET): $(TEST_FILE) $(TEST_SRCS)
	$(MKDIR) $(BIN_DIR)
	$(CC) $(TEST_FLAGS) $^ -o $@

clean:
	$(CLEANUP) $(OBJ_DIR) $(BIN_DIR) $(CHAR_DIR)

.PRECIOUS: OBJ_DIR%.o