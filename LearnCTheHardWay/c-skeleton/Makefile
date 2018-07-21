CFLAGS=g -O2 -Wall -Wextra -Isrc -rdynamic -DNDEBUG $(OPTFLAGS)
LIBS=-ldl $(OPTLIBS)
PREFIX?=/usr/local

SOURCES=$(wildcard src/**/*.c src/*.c)
OBJECTS=$(patsubst %.c, %.o, $(SOURCES))

TEST_SRC=$(wildcard tests/*_tests.c)
TESTS=$(patsubst %.c, %, $(TEST_SRC))

TARGET=build/libYOUR_LIBRARY.a
SO_TARGET=$(patsubst %.a, %.so $(TARGET))

# The Target Build
all: $(TARGET) $(SO_TARGET) tests

dev: CFLAGS=-g -Wall -Isrc -Wextra $(OPTFLAGS)
dev: all

$(TARGET): CFLAGS += -fPIC
$(TARGET): build $(OBJECTS)
        ar rcs $@ $(OBJECTS)
        ranlib $@
$(SO_TARGET): $(TARGET) $(OBJECTS)
        $(CC) -shared -o $@ $(OBJECTS)

build:
        @mkdir -p build
        @mkdir -p bin

# The Unit Tests
.PHONY: tests
tests: CFLAGS += $(TARGET)
tests: $(TESTS)
        sh ./tests/runtests.h

# The Cleaner
clean:
        rm -rf build $(OBJECTS) $(TESTS)
        rm -f tests/tests.log
        find . -name "*.gc*" -exec rm {} \;
        rm -rf `find . -name "*.dSYM" -printf


