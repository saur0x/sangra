#
# TODO: Move `libmongoclient.a` to /usr/local/lib so this can work on production servers
#

CC := gcc # This is the main compiler
# CC := clang --analyze # and comment out the linker last line for sanity

SRCDIR := src
BUILDDIR := build
TARGET := bin/main

SRCEXT := c
SOURCES := $(shell find $(SRCDIR) -type f ! -name test.c -name *.$(SRCEXT))
OBJECTS := $(patsubst $(SRCDIR)/%,$(BUILDDIR)/%,$(SOURCES:.$(SRCEXT)=.o))
CFLAGS := -g -Wall
LIB :=
INC := -I include -I src

$(TARGET): $(OBJECTS)
	@echo '[+] Linking'
	$(CC) -o $(TARGET) $^ $(LIB)

$(BUILDDIR)/%.o: $(SRCDIR)/%.$(SRCEXT)
	@echo '[+] Compiling'
	@mkdir -p $(shell dirname $@)
	$(CC) $(CFLAGS) $(INC) -c -o $@ $<

clean:
	@echo '[+] Cleaning'
	$(RM) -r -- $(BUILDDIR) $(TARGET)

# Tests
tester:
	$(CC) $(CFLAGS) test/test.c $(INC) $(LIB) -o bin/test

# Spikes
ticket:
	$(CC) $(CFLAGS) spikes/ticket.c $(INC) $(LIB) -o bin/ticket

.PHONY: clean
