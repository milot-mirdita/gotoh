PROGRAM = gotoh
C_FILES := $(wildcard *.cpp)
OBJS := $(patsubst %.cpp, %.o, $(C_FILES))
CC = g++-4.6
CFLAGS = -Wall -pedantic -Ilib -std=c++0x -Ofast -march=native -mtune=native -DONETWOTHREED -ggdb -ftree-vectorize -fno-strict-aliasing
LDFLAGS =

all: $(PROGRAM)

$(PROGRAM): .depend $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LDFLAGS) -o $(PROGRAM)

depend: .depend

.depend: cmd = gcc -MM -MF depend $(var); cat depend >> .depend;
.depend:
	@echo "Generating dependencies..."
	@$(foreach var, $(C_FILES), $(cmd))
	@rm -f depend

-include .depend

# These are the pattern matching rules. In addition to the automatic
# variables used here, the variable $* that matches whatever % stands for
# can be useful in special cases.
%.o: %.cpp
	$(CC) $(CFLAGS) -c $< -o $@

%: %.cpp
	$(CC) $(CFLAGS) -o $@ $<

clean:
	rm -f .depend *.o

.PHONY: clean depend
