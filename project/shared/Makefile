CXX = g++
CC  = g++

CPPFLAGS =  -std=c++11
CXXFLAGS =  -O2 -Wall -Wextra -pedantic-errors -Wold-style-cast 
CXXFLAGS += -std=c++11 

all: libcommunication.a

libcommunication.a: article.o newsgroup.o messagehandler.o packet.o
	ar rv libcommunication.a article.o newsgroup.o messagehandler.o packet.o
	ranlib libcommunication.a

clean:
	rm -f *.o libcommunication.a *.d*

%.d: %.cc
	@set -e; rm -f $@; \
         $(CPP) -MM $(CPPFLAGS) $< > $@.$$$$; \
         sed 's,\($*\)\.o[ :]*,\1.o $@ : ,g' < $@.$$$$ > $@; \
         rm -f $@.$$$$

SRC = $(wildcard *.cc)
include $(SRC:.cc=.d)