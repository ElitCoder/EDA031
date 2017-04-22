CXX = g++
CC  = g++

CPPFLAGS  = -std=c++11 -I../clientserver/
CXXFLAGS  = -O2 -Wall -W -pedantic-errors
CXXFLAGS += -Wmissing-braces -Wparentheses -Wold-style-cast 
LDFLAGS   = -L../clientserver/

LDLIBS = -lclientserver

PROGS = newsserver

all: $(PROGS)

newsserver: newsserver.o messagehandler.o packet.o process.o newsgroup.o article.o databasememory.o database.o databasedisk.o

clean:
	rm -f *.o $(PROGS) *.d*

%.d: %.cc
	@set -e; rm -f $@; \
         $(CPP) -MM $(CPPFLAGS) $< > $@.$$$$; \
         sed 's,\($*\)\.o[ :]*,\1.o $@ : ,g' < $@.$$$$ > $@; \
         rm -f $@.$$$$

SRC = $(wildcard *.cc)
include $(SRC:.cc=.d)