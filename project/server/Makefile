CXX = g++
CC  = g++

CPPFLAGS  = -std=c++11 -I../clientserver/
CXXFLAGS  = -g -O2 -Wall -W -pedantic-errors
CXXFLAGS += -Wmissing-braces -Wparentheses -Wold-style-cast 
LDFLAGS   = -g -L../clientserver/

LDLIBS = -lclientserver

PROGS = newsserver

all: $(PROGS)

newsserver: newsserver.o messagehandler.o

clean:
	rm -f *.o $(PROGS) *.d*

%.d: %.cc
	@set -e; rm -f $@; \
         $(CPP) -MM $(CPPFLAGS) $< > $@.$$$$; \
         sed 's,\($*\)\.o[ :]*,\1.o $@ : ,g' < $@.$$$$ > $@; \
         rm -f $@.$$$$

SRC = $(wildcard *.cc)
include $(SRC:.cc=.d)