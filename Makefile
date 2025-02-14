CC = clang
CFLAGS = -Wall -Wextra -I./include

# Directories
SRC_DIR = src
TEST_DIR = tests
OBJ_DIR = obj

# Create obj directory if it doesn't exist
$(shell mkdir -p $(OBJ_DIR))

# Source files
TEST_SRC = $(TEST_DIR)/test_encoder.c
ENCODER_SRC = $(SRC_DIR)/encoder.c

# Object files
TEST_OBJ = $(OBJ_DIR)/test_encoder.o
ENCODER_OBJ = $(OBJ_DIR)/encoder.o

# Default target
all: test_encoder

# Build the test executable
test_encoder: $(TEST_OBJ) $(ENCODER_OBJ)
	$(CC) $(CFLAGS) -o $@ $^

# Compile test source
$(TEST_OBJ): $(TEST_SRC)
	$(CC) $(CFLAGS) -c $< -o $@

# Compile encoder source
$(ENCODER_OBJ): $(ENCODER_SRC)
	$(CC) $(CFLAGS) -c $< -o $@

# Run tests
test: test_encoder
	./test_encoder

clean:
	rm -rf $(OBJ_DIR) test_encoder

.PHONY: all test clean