# Paths
SRC_DIR := src
INCLUDE_DIR := include
BUILD_DIR := build
BIN_DIR := $(BUILD_DIR)/bin
BIN_NAME := exec
BIN_PATH := $(BIN_DIR)/$(BIN_NAME)

# Compiler flags
CXX ?= g++
CXXFLAGS += --std=c++20 -Wall -Wextra -Wpedantic -g
CXX_DEB_FLAGS = -DDEBUG
CXX_REL_FLAGS = -O2
INCLUDES = -I $(INCLUDE_DIR)
LIBRARIES =

# Find all source files (any *.cpp under $(SRC_DIR)).
SOURCES = $(wildcard $(SRC_DIR)/*.cpp)
SOURCES += $(wildcard $(SRC_DIR)/**/*.cpp)

# Generate object names from source files.
OBJECTS = $(SOURCES:$(SRC_DIR)/%.cpp=$(BUILD_DIR)/%.o)

# Generate dependency file names for header dependencies.
DEPENDS = $(OBJECTS:.o=.d)

# Phony targets
.PHONY: _default build run clean
_default: build

build: $(BIN_PATH)

run: build
	@$(BIN_PATH)

clean:
	$(RM) -r $(BUILD_DIR)

$(BIN_PATH): $(OBJECTS)
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) $(LIBRARIES) -o $@ $^

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) $(INCLUDES) -MP -MMD -o $@ -c $<

-include $(DEPENDS)
