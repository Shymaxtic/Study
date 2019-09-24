CC = g++
CPPFLAGS = -fPIC -Wall -Wextra -O2 -g
INCLUDEPATH = -I./ -I../
RM = rm -f
TARGET = test

SRCS = $(shell echo *.cpp)
OBJS = $(SRCS:.cpp=.o)

all: $(TARGET)

clean:
	@echo rm -f $(OBJS) $(TARGET)

$(TARGET): $(OBJS)
	@echo $(CC) $(LDFLAGS) $(INCLUDEPATH) -o $@ $^

$(OBJS)	: $(SRCS)
	@echo $(CC) $(CPPFLAGS) $(INCLUDEPATH) -o $@ $^