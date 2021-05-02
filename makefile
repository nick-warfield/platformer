BINARY_NAME = platformer
CC = ccache clang++
OPT = O2

CFLAGS = -std=c++17 -$(OPT) -Wall -Wextra -Wno-missing-braces -DDEBUG
LDFLAGS = -lsfml-graphics -lsfml-window -lsfml-audio -lsfml-system

LIB_DIR = lib
INCLUDE_DIR = include
SOURCE_DIR = src
OBJECT_DIR = src/obj
RESOURCE_DIR = resources
BUILD_DIR = build
TEST_DIR = tests

CFLAGS += -I$(INCLUDE_DIR) -isystem $(LIB_DIR)

HEADERS = $(wildcard *, $(INCLUDE_DIR)/*.hpp)
OBJECTS := main.o $(patsubst %.hpp,%.o, $(notdir $(HEADERS)))
OBJECTS := $(addprefix $(OBJECT_DIR)/, $(OBJECTS))

$(OBJECT_DIR)/%.o: $(SOURCE_DIR)/%.cpp $(HEADERS)
	$(CC) -c -o $@ $< $(CFLAGS)

$(BUILD_DIR)/$(BINARY_NAME): init $(OBJECTS)
	$(CC) -o $@ $(OBJECTS) $(CFLAGS) $(LDFLAGS)

.PHONY: run clean test init all

all: clean $(BUILD_DIR)/$(BINARY_NAME)

run: $(BUILD_DIR)/$(BINARY_NAME)
	@./$(BUILD_DIR)/$(BINARY_NAME)

clean:
	@[ ! -d $(OBJECT_DIR) ] || trash $(OBJECT_DIR)
	@[ ! -d $(BUILD_DIR) ] || trash $(BUILD_DIR)

test:
	@echo "Testing Makefile not implemented"

init:
	@[ -d $(OBJECT_DIR) ] \
		|| ( mkdir -p $(OBJECT_DIR); \
		echo "$(OBJECT_DIR) created")
	@[ -d $(BUILD_DIR) ] \
		|| (mkdir -p $(BUILD_DIR); \
		echo "$(BUILD_DIR) created")
	@[ -d $(BUILD_DIR)/$(RESOURCE_DIR) ] || [ ! -d $(RESOURCE_DIR) ] \
		|| (ln -s "$(realpath $(RESOURCE_DIR))" $(BUILD_DIR); \
		echo "$(RESOURCE_DIR) linked to $(BUILD_DIR)/$(RESOURCE_DIR)")
