CC  = g++
CXX = g++

INCLUDES = 

CFLAGS   = -std=c++11 -g -Wall $(INCLUDES)
CXXFLAGS = -std=c++11 -g -Wall $(INCLUDES)

LDFLAGS = 
LDLIBS  = 

.PHONY: default
default: vfs

vfs: vfs.o
	$(CXX) $(LDFLAGS) -o vfs vfs.o $(LDLIBS)

vfs.o: vfs.cpp
	$(CXX) $(CXXFLAGS) -c vfs.cpp -o vfs.o

.PHONY: clean
clean:
	rm -f *.o *~ a.out core vfs

.PHONY: run
run: vfs
	./vfs

.PHONY: all
all: clean default