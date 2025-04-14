# Compiler
CXX = g++
CC = gcc

# Compiler flags
CXXFLAGS = -Wall -Wextra -pedantic -std=c++11 -I./include -DGLM_ENABLE_EXPERIMENTAL
CFLAGS = -Wall -Wextra -pedantic -std=c11 -I./include
LDFLAGS = -L./lib -static
LDLIBS = -lglfw3 -lopengl32 -lgdi32 -lkernel32 -luser32 -lshell32

# Source files
CPPSRCS = $(shell find src -name "*.cpp")
CSRCS = $(shell find src -name "*.c")

# Object files
CPPOBJS = $(patsubst src/%.cpp,obj/%.o,$(CPPSRCS))
COBJS = $(patsubst src/%.c,obj/%.o,$(CSRCS))
OBJS = $(CPPOBJS) $(COBJS)

# Executable name
TARGET = minecraft-cube

# Default target
all: $(TARGET)

# Link object files to create the executable
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS) $(LDLIBS)

obj/graphic/glad.o: src/graphic/glad.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS:-pedantic=) -c $< -o $@

# Compile C++ source files
obj/%.o: src/%.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@

obj/%.o: src/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

# Clean up build files
clean:
	rm -rf obj $(TARGET)

.PHONY: all clean