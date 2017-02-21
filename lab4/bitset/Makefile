CXX = g++
CC  = $(CXX)

DEPFLAGS = -MT $@ -MMD -MP -MF $*.d

CPPFLAGS = -std=c++11
CXXFLAGS = -O2 -Wall -Wextra -pedantic-errors -Wold-style-cast
CXXFLAGS += $(DEPFLAGS)

PROGS = simplebitsettest bitsettest1 bitsettest2

all: $(PROGS)

simplebitsettest: simplebitsettest.o simplebitset.o

bitsettest1: bitsettest1.o bitset.o bitreference.o

bitsettest2: bitsettest2.o bitset.o bitreference.o

clean:
	rm -f *.o $(PROGS) *.d

SRC = $(wildcard *.cc)
-include $(SRC:.cc=.d)
