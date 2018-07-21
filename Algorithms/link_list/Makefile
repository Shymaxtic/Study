OPTIMZIE	= -g -Os
CXX		= g++
CC		= gcc

# CXX compiler option
CXXFLAGS	+=	$(OPTIMIZE)	\
			-Wall		\
			-DNDEBUG	\

# Include path
INCFLAGS	+= 	-Isrc		\
			-Isrc/**	\

# Library path

# Library libs	

# Source dir
SRC_DIR		= src

# Test dir
TEST_DIR	= tests

# Target lib
TARGET_LIB	= build

SOURCES		= $(wildcard $(SRC_DIR)/**/.c $(SRC_DIR)/*.c)
OBJECTS		= $(patsubst %.c, %.o, $(SOURCES))

TESTS_SRC	= $(wildcard $(TEST_DIR)/*_tests.c)
TESTS		= $(patsubst %.c, %, $(TESTS_SRC))

A_TARGET	= $(TARGET_LIB)/liblinklist.a
SO_TARGET	= $(patsubst %.a, %.so, $(A_TARGET))

# Target build
all: create $(A_TARGET) $(SO_TARGET) tests

create:
	@mkdir -p $(TARGET_LIB)
	@mkdir -p bin

$(A_TARGET): $(OBJECTS)
	@echo ---Static Library: Linking $<---
	ar rcs $@ $< 
	ranlib $@

$(SO_TARGET): $(A_TARGET) $(OBJECTS)
	@echo ---Dynamic Library: Linking $<---
	$(CC) -shared -o $@ $< 

$(OBJECTS): $(SOURCES)
	@echo ---Compiling $<---
	$(CC) -o $@ -c $< -fPIC $(INCFLAGS)

# Unit tests
.PHONY: tests
tests: CFLAGS += $(A_TARGET)
tests: $(TESTS)
	sh ./tests/runtests.sh

$(TESTS): $(TESTS_SRC)
	@echo ---Compiling $<---
	$(CC) -o $@ $< $(CFLAGS)

# Cleaner
clean:
	rm -rf $(TARGET_LIB) $(OBJECTS) $(TESTS)
	rm -f tests/tests.log
	find . -name "*.gc*" -exec rm {} \;
	rm -rf `find . -name "*.dSYM" -printf`


	



