#project settings
TARGET = SiliconPostlife
CC = gcc
SRCDIR = src
BUILDDIR = build
BINDIR = bin
SOURCES = $(wildcard $(SRCDIR)/*.c)
OBJECTS = $(patsubst $(SRCDIR)/%.c,$(BUILDDIR)/%.o,$(SOURCES))

#compiler options
#CFLAGS = -Wall -std=c99 -g -O2
CFLAGS = -Wall -std=c99 -g
LDFLAGS = 
LIBS = -lraylib -lm -lpthread -ldl -lcsv

#preparing
prepare:
	@mkdir -p $(BUILDDIR)
	@mkdir -p $(BINDIR)

$(BUILDDIR)/%.o: $(SRCDIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

$(BINDIR)/$(TARGET): $(OBJECTS)
	$(CC) $(OBJECTS) -o $@ $(LIBS)
	
clean:
	#@rm -rf $(BINDIR)
	@rm -rf $(BUILDDIR)

all: prepare $(BINDIR)/$(TARGET)   # all зависит от бинаря
	@echo "OK"

run: all
	./$(BINDIR)/$(TARGET)

