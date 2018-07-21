CXX 			= g++
CC 				= gcc
OPTIMIZE 		= -g -Os
CXXFLAGS 		+= $(OPTIMIZE) \
				-Wall
				
CXXFLAGS 		+= -I./

LIBFLAGS		+= -lpthread
##############################################################
BUILDDIR		= ./builds
SOURCES			= $(wildcard ./*.c)
OBJECTS			= $(patsubst ./%.c,$(BUILDDIR)/%.o,$(SOURCES))
OUTPUT			= $(notdir $(shell pwd))
##############################################################
all:create $(OUTPUT)
	
create:
	@mkdir.exe -p $(BUILDDIR)
	
$(OUTPUT) : $(OBJECTS)
	$(CXX) -o $@ $^ $(CXXFLAGS) $(LIBFLAGS)

$(OBJECTS): $(SOURCES)
	$(CXX) -c -o $@ $^ $(CXXFLAGS) 
	
clean:
	rm -rf ./builds
	
