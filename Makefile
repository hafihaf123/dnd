MKDIR=mkdir -p
CLEANUP=rm -rf

.PHONY:all
.PHONY:clean

.DEFAULT_GOAL := all

CC = gcc
CFLAGS = -Wall -g -fsanitize=address -fno-omit-frame-pointer
CFLAGS += $(shell find $(SRC_DIR) -name "*.h" -type f -exec dirname {} \; | sort -u | sed 's/.*/-I&/')

SRC_DIR = src/
BUILD_DIR = build/
OBJ_DIR = $(BIN_DIR)obj/
BIN_DIR = bin/
CHAR_DIR = .characters/

SRCS := $(shell find $(SRC_DIR) -name '*.c')
OBJS := $(SRCS:$(SRC_DIR)%.c=$(OBJ_DIR)%.o)

TARGET = $(BIN_DIR)dnd

all: $(TARGET)

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	$(MKDIR) $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

$(TARGET): $(OBJS)
	$(MKDIR) $(BIN_DIR)
	$(CC) $(CFLAGS) $^ -o $@

clean:
	$(CLEANUP) $(BUILD_DIR) $(BIN_DIR) $(CHAR_DIR)