# Variables
CXX := g++
CXXFLAGS := -Iinclude -Wall -Wextra -std=c++17 -O3
SRC_DIR := src
OUT_DIR := out
TARGET := $(OUT_DIR)/a.out

# Source files
SRCS := $(wildcard $(SRC_DIR)/*.cpp)

# Object files
OBJS := $(SRCS:$(SRC_DIR)/%.cpp=$(OUT_DIR)/%.o)

# Default target
all: $(TARGET)

# Link object files to create the executable
$(TARGET): $(OBJS) | $(OUT_DIR)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Compile source files into object files
$(OUT_DIR)/%.o: $(SRC_DIR)/%.cpp | $(OUT_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Ensure the output directory exists
$(OUT_DIR):
	mkdir -p $(OUT_DIR)

# Clean up generated files
clean:
	rm -rf $(OUT_DIR)/*.o $(TARGET)

# Phony targets
.PHONY: all clean
