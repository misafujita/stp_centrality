# Makefile

# names of the PROGRAMs and objects
PROGRAM = cnst
OBJS = \
	main.o \
	emalloc.o \
	mersenne.o \
	swap.o \
	input.o \
	binaryheap.o \
	dijkstra.o \
	kruskal.o \
	dnh.o \
	sph.o \
	adh.o

# redefinition of defined Macro
CC   = g++
CFLAGS = -g -Wall
MATH_OPTION = -lm

# header path
HEADER_PATH = -I . -I $(HEADER)

# suffix rules
.SUFFIXES: .c .o

# primary target
$(PROGRAM): $(OBJS)
	$(CC) -o $(PROGRAM) $^

# suffix rules
.c.o:
	$(CC) $(CFLAGS) $(HEADER_PATH) -o $@ -c $<

# clean
.PHONY: clean
clean:
	$(RM) $(PROGRAM) $(OBJS) *~

# clean
.PHONY: install
install:
	cp -f $(PROGRAM) $(BINDIR)
