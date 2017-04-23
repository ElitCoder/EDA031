CXX = g++
CC  = g++

CPPFLAGS  = -std=c++11 -I../shared/
CXXFLAGS  = -O2 -Wall -W -pedantic-errors
CXXFLAGS += -Wmissing-braces -Wparentheses -Wold-style-cast 
LDFLAGS   = -L../shared/

LDLIBS = -lclientserver -lproject

PROGS = newsclient

all: $(PROGS)

newsclient: newsclient.o input.o process.o commander.o

clean:
	rm -f *.o $(PROGS) *.d*

%.d: %.cc
	@set -e; rm -f $@; \
         $(CPP) -MM $(CPPFLAGS) $< > $@.$$$$; \
         sed 's,\($*\)\.o[ :]*,\1.o $@ : ,g' < $@.$$$$ > $@; \
         rm -f $@.$$$$

SRC = $(wildcard *.cc)
include $(SRC:.cc=.d)