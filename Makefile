# Source files
SRCS := $(wildcard *.cpp)

# Object files
OBJS := $(SRCS:.cpp=.o)

# Compiler
CC := g++

# Compiler flags
CFLAGS := -Wall -std=c++11

# Includes
#INCLUDES :=/usr/include/boost

# Libraries
LIBS := -lboost_system -lboost_thread

# Target executable
TARGET := cppchallenge

# Default target
all: $(TARGET)

# Rule to build the executable
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $(INCLUDES) -o $(TARGET) $(OBJS)

# Rule to build object files from source files
%.o: %.cpp
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

# Clean up intermediate files and the executable
clean:
	rm -f $(OBJS) $(TARGET)
