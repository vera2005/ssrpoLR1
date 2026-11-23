CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -Wpedantic -Iinclude --coverage
LDFLAGS = --coverage

SRC = src
BUILD = build
BIN = bin
TEST = test

SRCS = $(SRC)/l1_UserInterface.cpp $(SRC)/l2_ApplicationLayer.cpp \
       $(SRC)/l3_DomainLayer.cpp $(SRC)/l4_InfrastructureLayer.cpp
OBJS = $(patsubst $(SRC)/%.cpp,$(BUILD)/%.o,$(SRCS))
DL_OBJS = $(BUILD)/l2_ApplicationLayer.o $(BUILD)/l3_DomainLayer.o $(BUILD)/l4_InfrastructureLayer.o

TARGET = $(BIN)/airfield

.PHONY: all clean test
all: $(TARGET)

$(TARGET): $(OBJS) | $(BIN)
	$(CXX) $(LDFLAGS) -o $@ $^

$(BUILD)/%.o: $(SRC)/%.cpp | $(BUILD)
	$(CXX) $(CXXFLAGS) -c -o $@ $<

$(BIN):
	mkdir -p $(BIN)
$(BUILD):
	mkdir -p $(BUILD)

$(TEST)/test01: $(TEST)/test01.cpp $(DL_OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^
$(TEST)/test02: $(TEST)/test02.cpp $(DL_OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

test: $(TEST)/test01 $(TEST)/test02
	$(TEST)/test01
	$(TEST)/test02

clean:
	rm -rf $(BUILD) $(BIN) $(TEST)/test01 $(TEST)/test02 *.gcda *.gcno t1.data