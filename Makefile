.PHONY = all clean

BINDIR = bin
INTERDIR = $(BINDIR)/intermediates
BINARY = $(BINDIR)/snake
SOURCEDIR = src
CODEDIRS = $(SOURCEDIR)

CC = gcc
CFLAGS = -MP -MD

CFILES = $(foreach DIR, $(CODEDIRS), $(wildcard $(DIR)/*.c))
OBJECTS = $(patsubst $(SOURCEDIR)/%.c, $(INTERDIR)/%.o, $(CFILES))
DEPFILES = $(OBJECTS:%.o=%.d)

all: $(BINARY)

$(BINARY): $(OBJECTS)
	$(CC) $^ -o $@

$(INTERDIR)%.o: $(SOURCEDIR)%.c $(INTERDIR) $(BINDIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(INTERDIR):
	mkdir -p $(INTERDIR)

$(BINDIR):
	mkdir -p $(BINDIR)

clean:
	rm $(BINARY) $(OBJECTS) $(DEPFILES)

-include $(DEPFILES)
