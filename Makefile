# Variables
CXX := g++
CXXFLAGS := -Iinclude -Wall -Wextra -std=c++17 -O3
SRC_DIR := src
OUT_DIR := out
TARGET := $(OUT_DIR)/a.out
TESTS_DIR := tests

# Source files
SRCS := $(wildcard $(SRC_DIR)/*.cpp)
TEST_SRCS := $(wildcard $(TESTS_DIR)/*.cpp)

# Object files
OBJS := $(SRCS:$(SRC_DIR)/%.cpp=$(OUT_DIR)/%.o)
TEST_OBJS := $(TEST_SRCS:$(TESTS_DIR)/%.cpp=$(OUT_DIR)/%.test.o)

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

# Compile test files
$(OUT_DIR)/%.test.o: $(TESTS_DIR)/%.cpp | $(OUT_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

tests: $(TARGET) $(TEST_SRCS) | $(OUT_DIR)
	echo $(TEST_SRCS)
	@for test_file in $(TEST_SRCS); do \
		echo "Running $$test_file..."; \
		$(CXX) $(CXXFLAGS) $$test_file $(filter-out $(OUT_DIR)/main.o, $(OBJS)) -o $(OUT_DIR)/$$(basename $$test_file .cpp).out && $(OUT_DIR)/$$(basename $$test_file .cpp).out; \
	done

# Clean up generated files
clean:
	rm -rf $(OUT_DIR)/*.o $(TARGET) $(OUT_DIR)/*.out

# Phony targets
.PHONY: all tests clean
