CXX = g++
CC  = $(CXX)

DEPFLAGS = -MT $@ -MMD -MP -MF $*.d

CPPFLAGS = -std=c++11
CXXFLAGS = -O2 -Wall -Wextra -pedantic-errors -Wold-style-cast
CXXFLAGS += $(DEPFLAGS)

PROGS = nstest nstime

all: $(PROGS)

nstest: nstest.o vns.o mns.o umns.o hns.o

nstime: nstime.o vns.o mns.o umns.o hns.o

clean:
	rm -f *.o $(PROGS) *.d

SRC = $(wildcard *.cc)
-include $(SRC:.cc=.d)
