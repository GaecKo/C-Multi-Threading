CC := gcc
CFLAGS := -Wall -Werror -I$(SRC_DIR)/header

SRC_DIR := c
OBJ_DIR := $(SRC_DIR)
BIN_DIR := .

SRCS := $(wildcard $(SRC_DIR)/*.c)
OBJS := $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRCS))
BINS := $(patsubst $(SRC_DIR)/%.c, $(BIN_DIR)/%, $(SRCS:.c=))

.PHONY: all clean

all: $(BINS)

$(BIN_DIR)/%: $(OBJ_DIR)/%.o
	$(CC) $^ -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(SRC_DIR)/header/%.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJS) $(BINS)

