# Compiler and flags
CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++17
SRC_DIR = src
BIN_DIR = bin

SRCS := $(wildcard $(SRC_DIR)/**/*.cpp)

EXES := $(patsubst $(SRC_DIR)/%.cpp, $(BIN_DIR)/%, $(SRCS))

TEXTS := $(wildcard $(SRC_DIR)/**/*.txt)

DATA := $(patsubst $(SRC_DIR)/%.txt, $(BIN_DIR)/%.txt, $(TEXTS))

all: $(BIN_DIR) $(EXES) $(DATA)
	echo $(BIN_DIR) $(EXES) $(DATA)

$(BIN_DIR):
	mkdir -p $(BIN_DIR)

$(BIN_DIR)/%: $(SRC_DIR)/%.cpp | $(BIN_DIR)
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -o $@ $<

$(BIN_DIR)/%.txt: $(SRC_DIR)/%.txt | $(BIN_DIR)
	@mkdir -p $(dir $@) # Create corresponding subdirectories in bin
	cp $< $@


clean:
	rm -rf $(BIN_DIR)
