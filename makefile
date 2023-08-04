# Makefile for a C++ program using raylib.h

# Compiler and compiler flags
CC = g++
CFLAGS = -Wall -Wextra -std=c++11

# Path to the raylib library
RAYLIB_PATH = /usr/local
# Name of the output executable
TARGET = main

# Source files (add more if you have multiple source files)
SOURCES = main.cpp Camera.cpp Player.cpp

# Object files (automatically generated from source files)
OBJECTS = $(SOURCES:.cpp=.o)

# Include directories (add any additional include paths here)
INCLUDES = -I$(RAYLIB_PATH)/include

# Linker flags (add any additional libraries here)
LDFLAGS = -L$(RAYLIB_PATH)/lib -lraylib

# Build rules
all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) $(INCLUDES) -o $(TARGET) $(OBJECTS) $(LDFLAGS)

.cpp.o:
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -f $(OBJECTS) $(TARGET)

.PHONY: clean
