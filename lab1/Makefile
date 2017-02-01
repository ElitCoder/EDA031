CXX = g++
CC  = g++

CPPFLAGS =  -std=c++11
CXXFLAGS =  -O2 -Wall -Wextra -pedantic-errors -Wold-style-cast -std=c++11 -g
LDFLAGS =   -L.
LDLIBS =	-l lab1

# Targets
PROGS = ltest hello encode decode

all: $(PROGS)

# Targets rely on implicit rules for compiling and linking
ltest: ltest.o

# hello.cc
hello: hello.o

# encode
encode: encode.o

# decode
decode: decode.o

# Phony targets
.PHONY: all clean

# Standard clean
clean:
	rm -f *.o $(PROGS) *.d* file.enc file.dec

# Generate dependencies in *.d files
%.d: %.cc
	@set -e; rm -f $@; \
         $(CPP) -MM $(CPPFLAGS) $< > $@.$$$$; \
         sed 's,\($*\)\.o[ :]*,\1.o $@ : ,g' < $@.$$$$ > $@; \
         rm -f $@.$$$$

# Include the *.d files
SRC = $(wildcard *.cc)
include $(SRC:.cc=.d)
