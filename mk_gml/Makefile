# Makefile

# names of the PROGRAMs and objects
PROGRAM = mk_gml
OBJS = \
	main.o \
	emalloc.o \
	input.o

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
