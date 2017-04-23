CXX = g++
CC  = g++

CPPFLAGS =  -std=c++11
CXXFLAGS =  -O2 -Wall -Wextra -pedantic-errors -Wold-style-cast 
CXXFLAGS += -std=c++11 

all: libproject.a

libproject.a: article.o newsgroup.o stream.o
	ar rv libproject.a article.o newsgroup.o stream.o
	ranlib libproject.a

clean:
	rm -f *.o libproject.a *.d*

%.d: %.cc
	@set -e; rm -f $@; \
         $(CPP) -MM $(CPPFLAGS) $< > $@.$$$$; \
         sed 's,\($*\)\.o[ :]*,\1.o $@ : ,g' < $@.$$$$ > $@; \
         rm -f $@.$$$$

SRC = $(wildcard *.cc)
include $(SRC:.cc=.d)