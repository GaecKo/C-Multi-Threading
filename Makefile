CC := gcc
CFLAGS := -Wall -Werror -Ic/include -lpthread

# Directories 
SRC_DIR := c
BUILD_DIR := $(SRC_DIR)/build
EXEC_DIR := executables

# Source files
SOURCES := $(wildcard $(SRC_DIR)/*.c) # all c files
EXECS := $(filter-out sem,$(patsubst $(SRC_DIR)/%.c,%,$(SOURCES))) # all c file, except sem. Removes dir name: c/file1 -> file1 with patsubst
SPECIAL_SOURCES := $(wildcard $(SRC_DIR)/*2.c)
HEADER = $(wildcard $(SRC_DIR)/headers/*.h)


# make 
all: folder $(addprefix $(EXEC_DIR)/,$(EXECS))
	@echo "Compilation finished"

# creating folders
folder:
	@mkdir -p $(EXEC_DIR)
	@mkdir -p $(BUILD_DIR)

# file: needs file.o and sem.o
$(EXEC_DIR)/%: $(BUILD_DIR)/%.o $(BUILD_DIR)/sem.o
	$(CC) $(CFLAGS) $^ -o $@

# file.o: needs file.c
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c $(HEADER)
	$(CC) $(CFLAGS) -c $< -o $@

# sem.o: needs sem.c
$(BUILD_DIR)/sem.o: $(SRC_DIR)/sem.c
	$(CC) $(CFLAGS) -c $< -o $@

# Clean up
clean:
	@echo "Cleaning up..."
	rm -rf $(BUILD_DIR) $(EXEC_DIR) 

test: all 
	@echo "testing..."
	./experiments.sh 
	@echo "make test done!"

.PHONY: all clean test 
