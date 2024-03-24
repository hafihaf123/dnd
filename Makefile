MKDIR=mkdir -p
CLEANUP=rm -rf

.PHONY: all clean test delete_database

.DEFAULT_GOAL := all

CC = gcc
CFLAGS = -Wall -g -fsanitize=address -fno-omit-frame-pointer -Isqlite
TEST_FLAGS = -lrt -lm -Iminunit $(CFLAGS)
CFLAGS += $(shell find $(SRC_DIR) -name "*.h" -type f -exec dirname {} \; | sort -u | sed 's/.*/-I&/')

SRC_DIR = src
OBJ_DIR = obj
BIN_DIR = bin
SQLITE_DIR = sqlite
DB = db

TEST_FILE = test/test.c
SQLITE_FILE = $(SQLITE_DIR)/sqlite3.c

SRCS := $(shell find $(SRC_DIR) -name '*.c')
TEST_SRCS := $(filter-out $(SRC_DIR)/main.c, $(SRCS))
OBJS := $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

TARGET = $(BIN_DIR)/dnd
TEST_TARGET = $(BIN_DIR)/test_suite
SQLITE_TARGET = $(OBJ_DIR)/$(SQLITE_DIR)/sqlite3.o

all: $(TARGET)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(MKDIR) $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

$(SQLITE_TARGET): $(SQLITE_FILE)
	$(MKDIR) $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

$(TARGET): $(OBJS) $(SQLITE_TARGET)
	$(MKDIR) $(BIN_DIR)
	$(CC) $(CFLAGS) $^ -o $@

test: $(TEST_TARGET)
	./$(TEST_TARGET)

$(TEST_TARGET): $(TEST_FILE) $(TEST_SRCS) $(SQLITE_TARGET)
	$(MKDIR) $(BIN_DIR)
	$(CC) $(TEST_FLAGS) $^ -o $@

clean:
	$(CLEANUP) $(OBJ_DIR) $(TARGET) $(TEST_TARGET)

delete_database:
	$(CLEANUP) $(DB)

.PRECIOUS: $(OBJ_DIR)/%.o $(SQLITE_TARGET)
