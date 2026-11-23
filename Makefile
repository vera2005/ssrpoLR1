CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -Wpedantic -Iinclude --coverage
LDFLAGS = --coverage

SRC_DIR = src
BUILD_DIR = build
BIN_DIR = bin
TEST_DIR = test

SRCS = $(SRC_DIR)/l1_UserInterface.cpp \
       $(SRC_DIR)/l2_ApplicationLayer.cpp \
       $(SRC_DIR)/l3_DomainLayer.cpp \
       $(SRC_DIR)/l4_InfrastructureLayer.cpp

OBJS = $(patsubst $(SRC_DIR)/%.cpp,$(BUILD_DIR)/%.o,$(SRCS))

TARGET = $(BIN_DIR)/airfield

.PHONY: all clean test

all: $(TARGET)

$(TARGET): $(OBJS) | $(BIN_DIR)
	$(CXX) $(LDFLAGS) -o $@ $^

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c -o $@ $<

$(BIN_DIR):
	mkdir -p $(BIN_DIR)

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

test: $(TEST_DIR)/test01 $(TEST_DIR)/test02
	$(TEST_DIR)/test01
	$(TEST_DIR)/test02

$(TEST_DIR)/test01: $(TEST_DIR)/test01.cpp $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

$(TEST_DIR)/test02: $(TEST_DIR)/test02.cpp $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

clean:
	rm -rf $(BUILD_DIR) $(BIN_DIR) $(TEST_DIR)/test01 $(TEST_DIR)/test02