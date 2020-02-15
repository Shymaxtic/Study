# PYLIBPATH = $(shell python3-config --exec-prefix)/lib
# LIB = -L$(PYLIBPATH) $(shell python3-config --libs) -L$(BOOST_LIB) -lboost_python36
# OPTS = $(shell python3-config --includes) -I$(BOOST_INC) -O2 -fPIC

# location of the Python header files
PYTHON_INCLUDE = /usr/include/python3.6
 
# location of the Boost Python include files and library
BOOST_INC = /usr/local/boost_1_71_0/build/include
BOOST_LIB = /usr/local/boost_1_71_0/build/lib
 
# compile mesh classes
TARGET = zoo
 
$(TARGET).so: $(TARGET).o
	g++ -shared -Wl,--export-dynamic $(TARGET).o -L$(BOOST_LIB) -lboost_python36 -L/usr/lib/python3.6/config-3.6m-x86_64-linux-gnu -lpython3.6 -o $(TARGET).so
 
$(TARGET).o: $(TARGET).cpp
	g++ -I$(PYTHON_INCLUDE) -I$(BOOST_INC) -fPIC -c $(TARGET).cpp

clean:
	rm -rf *.so *.o

.PHONY: default clean