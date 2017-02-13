CXX = g++
CC  = $(CXX)

DEPFLAGS = -MT $@ -MMD -MP -MF $*.d

CPPFLAGS = -std=c++11
CXXFLAGS = -O2 -Wall -Wextra -pedantic-errors -Wold-style-cast
CXXFLAGS += $(DEPFLAGS)

PROGS = Primtal date_test String

all: $(PROGS)

Primtal: Primtal.o

date_test: date_test.o date.o

String: String.o date.o
clean:
	rm -f *.o $(PROGS) *.d

SRC = $(wildcard *.cc)
-include $(SRC:.cc=.d)
