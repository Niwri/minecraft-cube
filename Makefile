# Compiler
CXX = g++
CC = gcc

# Compiler flags
CXXFLAGS = -Wall -Wextra -pedantic -std=c++11 -I./include
CFLAGS = -Wall -Wextra -pedantic -std=c11 -I./include
LDFLAGS = -L./lib
LDLIBS = -lglfw3 -lopengl32 -lgdi32 -lkernel32 -luser32 -lshell32

# Source files
CPPSRCS = $(wildcard src/*.cpp)
CSRCS = $(wildcard src/*.c)

# Object files
CPPOBJS = $(CPPSRCS:src/%.cpp=obj/%.o)
COBJS = $(CSRCS:src/%.c=obj/%.o)
OBJS = $(CPPOBJS) $(COBJS)

# Executable name
TARGET = minecraft-cube

# Default target
all: $(TARGET)

# Link object files to create the executable
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS) $(LDLIBS)

# Compile C++ source files
obj/%.o: src/%.cpp
	@mkdir -p obj
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Compile C source files
obj/%.o: src/%.c
	@mkdir -p obj
	$(CC) $(CFLAGS) -c $< -o $@

# Clean up build files
clean:
	rm -rf obj $(TARGET)

.PHONY: all clean