####
# $@ - Target file
# $< - First dependecy
# $^ - All dependecies
####

RM := rm

CPP := g++
CPP_FLAGS := -O2 -Wall $(`Magick++-config --cxxflags --cppflags`)

BINARY_NAME := identicon
SRC_DIR := src
BUILD_DIR := build
TARGET_DIR := bin
TARGET := $(TARGET_DIR)/$(BINARY_NAME)
SRC_EXT := cpp

SOURCES := $(wildcard src/*.$(SRC_EXT))
OBJECTS := $(patsubst $(SRC_DIR)/%,$(BUILD_DIR)/%,$(SOURCES:.$(SRC_EXT)=.o))

LIB := -lssl `Magick++-config --cxxflags --cppflags --ldflags --libs --ldflags --libs`
INC := -I.


$(TARGET): $(OBJECTS)
	@echo " Linking..."
	@mkdir -p $(TARGET_DIR)
	$(CPP) -o $@ $^ $(LIB)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.$(SRC_EXT)
	@mkdir -p $(BUILD_DIR)
	$(CPP) $(CPP_FLAGS) -c -o $@ $< $(LIB)

clean:
	$(RM) -r $(BUILD_DIR) $(TARGET)

.PHONY: clean
