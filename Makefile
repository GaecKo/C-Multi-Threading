# Compiler settings
CC := gcc
CFLAGS := -Wall -Werror -Iincludes/

# Source, build, and executable directories
SRC_DIR := c
BUILD_DIR := $(SRC_DIR)/build
EXEC_DIR := executables

# Source files
SOURCES := $(wildcard $(SRC_DIR)/*.c)
# Exclude sem.c from executables
EXECS := $(filter-out sem,$(patsubst $(SRC_DIR)/%.c,%,$(SOURCES)))

# Special case source files that need sem.c
SPECIAL_SOURCES := $(wildcard $(SRC_DIR)/*2.c)


# Rule to make everything
all: folder $(addprefix $(EXEC_DIR)/,$(EXECS))
	echo "Compilation finished"

folder:
	mkdir -p $(EXEC_DIR)
	mkdir -p $(BUILD_DIR)

# Rule to make each executable
$(EXEC_DIR)/%: $(BUILD_DIR)/%.o $(BUILD_DIR)/sem.o
	$(CC) $(CFLAGS) $^ -o $@

# Rule to compile object files from source files
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

# Special rule for files that include sem.c
$(BUILD_DIR)/sem.o: $(SRC_DIR)/sem.c
	$(CC) $(CFLAGS) -c $< -o $@

# Clean up
clean:
	rm -rf $(BUILD_DIR) $(EXEC_DIR) 

test: all 
	./experiments.sh 

.PHONY: all clean
