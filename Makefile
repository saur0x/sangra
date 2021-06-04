# This is the main compiler
CC := gcc
# and comment out the linker last line for sanity
# CC := clang --analyze

SRCDIR := src
BUILDDIR := build
LOGDIR := log

TARGET := bin/main
TESTTARGET := bin/test

SRCEXT := c

# Ignore test.c files and any files starting with an underscore.
SOURCES := $(shell find $(SRCDIR) -type f ! -name test.c ! -name '_*' -name *.$(SRCEXT))
OBJECTS := $(patsubst $(SRCDIR)/%,$(BUILDDIR)/%,$(SOURCES:.$(SRCEXT)=.o))

TESTS := $(shell find $(SRCDIR) -name test.$(SRCEXT))

CFLAGS := -g -Wall
TESTFLAGS := -D AUTOMATIC_TESTING

LIB :=
INC := -iquote include

$(TARGET): $(OBJECTS)
	@echo '[+] Linking'
	$(CC) -o $(TARGET) $^ $(LIB)

$(BUILDDIR)/%.o: $(SRCDIR)/%.$(SRCEXT)
	@echo '[+] Compiling'
	@mkdir -p $(shell dirname $@)
	$(CC) $(CFLAGS) $(INC) -c -o $@ $<

clean:
	@echo '[+] Cleaning'
	$(RM) -rf -- $(BUILDDIR) $(LOGDIR) $(TARGET)

test: $(OBJECTS)
	@mkdir -p $(LOGDIR)
	$(foreach test_file, $(TESTS),											\
		echo "\n[+] Testing $(test_file)";									\
		$(CC) $(TESTFLAGS) $(INC) -c -o $(BUILDDIR)/test $(test_file);		\
		$(CC) -o $(TESTTARGET) $(BUILDDIR)/test $(OBJECTS) $(LIB);			\
		valgrind --leak-check=full \
			--show-leak-kinds=all \
			--track-origins=yes \
			--verbose \
			--log-file=$(LOGDIR)/$(shell echo -n $(test_file) | tr '/' '_' | tr -d '\n').log \
			$(TESTTARGET); \
	)

# Tests
tester:
	$(CC) $(CFLAGS) test/test.c $(INC) $(LIB) -o bin/test

# Spikes
ticket:
	$(CC) $(CFLAGS) spikes/ticket.c $(INC) $(LIB) -o bin/ticket

.PHONY: clean
.PHONY: test
