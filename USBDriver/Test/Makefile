CC = g++
CPPFLAGS = -fPIC -Wall -Wextra -O2 -g
INCLUDEPATH = -I./ -I../
RM = rm -f
TARGET = test

SRCS = $(shell echo *.cpp)
OBJS = $(SRCS:.cpp=.o)

all: $(TARGET)

clean:
	rm -f $(OBJS) $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(LDFLAGS) $(INCLUDEPATH) -o $@ $^

$(OBJS)	: $(SRCS)
	$(CC) $(CPPFLAGS) $(INCLUDEPATH) -c -o $@ $^