CC := gcc
# CC := clang --analyze

MAIN := main
TEST := test

SRCEXT := c

# Directories
BINDIR := bin
BUILDDIR := build
INCLUDEDIR := include
SRCDIR := src
TESTDIR := tests

CFLAGS := -g -Wall
LIBRARY := -lm
INCLUDE := -iquote $(INCLUDEDIR)

# Ignore $(MAIN).$(SRCEXT), test.c, and any $(SRCEXT) files starting with an underscore.
SOURCES := $(shell find $(SRCDIR) -type f ! -name $(MAIN).$(SRCEXT) ! -name $(TEST).$(SRCEXT) ! -name _* -name *.$(SRCEXT))
OBJECTS := $(patsubst $(SRCDIR)/%,$(BUILDDIR)/%,$(SOURCES:.$(SRCEXT)=.o))

.PHONY: clean test

all: build

build: $(OBJECTS) $(SRCDIR)/$(MAIN).$(SRCEXT)
	@echo '[+] Building'
	@mkdir -pv $(BINDIR)
	$(CC) $(CFLAGS) $(INCLUDE) -o $(BINDIR)/$(MAIN) $^ $(LIBRARY)

clean:
	@echo '[+] Cleaning'
	$(RM) -rf -- $(BINDIR) $(BUILDDIR)

expand: $(SRCDIR)/$(MAIN).$(SRCEXT)
	@echo '[+] Expanding'
	$(CC) $(INCLUDE) -E $^

run: build
	@exec ./$(BINDIR)/$(MAIN)

test: $(OBJECTS) $(TESTDIR)/$(TEST).$(SRCEXT)
	@echo '[+] Testing'
	@mkdir -pv $(BINDIR)
	$(CC) $(CFLAGS) $(INCLUDE) -o $(BINDIR)/$(TEST) $^ $(LIBRARY)

$(BUILDDIR)/%.o: $(SRCDIR)/%.$(SRCEXT)
	@echo '[+] Compiling'
	@mkdir -pv $(shell dirname $@)
	$(CC) $(CFLAGS) $(INCLUDE) -c -o $@ $<
