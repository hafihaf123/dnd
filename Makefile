CC = gcc
CFLAGS = -Wall -g -fsanitize=address -fno-omit-frame-pointer

SRC_DIR = src
OBJ_DIR = obj
BIN_DIR = bin

SRCS := $(shell find $(SRC_DIR) -name '*.c')
OBJS := $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

TARGET = $(BIN_DIR)/dnd

all: $(TARGET)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	$(info Compiling $< to $@)
	$(CC) $(CFLAGS) -c $< -o $@

$(TARGET): $(OBJS)
	@mkdir -p $(BIN_DIR)
	# $(info SRCS: $(SRCS))
	# $(info OBJS: $(OBJS))
	# $(info CC $^ -o $@)
	$(CC) $(CFLAGS) $^ -o $@

clean:
	rm -rf $(OBJ_DIR)/*.o $(TARGET)
