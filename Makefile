TARGET = SiliconPostLife
CC = gcc
SRCDIR = src
BUILDDIR = build
BINDIR = bin

SOURCES = $(wildcard $(SRCDIR)/*.c)
OBJECTS = $(patsubst $(SRCDIR)/%.c, $(BUILDDIR)/%.o, $(SOURCES))

SCENE_SOURCES = $(wildcard $(SRCDIR)/scenes/*.c)
SCENE_LIBS = $(patsubst $(SRCDIR)/scenes/%.c, $(BINDIR)/scenes/%.so, $(SCENE_SOURCES))

CFLAGS = -Wall -std=c99 -g -fPIC -I$(SRCDIR) $(VERSION_FLAG)
LIBS = -lraylib -lm -lpthread -ldl -lcsv -rdynamic

prepare:
	@mkdir -p $(BUILDDIR)
	@mkdir -p $(BINDIR)/scenes
	@cp $(SRCDIR)/scenes/scenes.inf $(BINDIR)/scenes/ 2>/dev/null || true

$(BUILDDIR)/%.o: $(SRCDIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

$(BINDIR)/$(TARGET): $(OBJECTS)
	$(CC) $(OBJECTS) -o $@ $(LIBS)

$(BINDIR)/scenes/%.so: $(SRCDIR)/scenes/%.c
	@mkdir -p $(BINDIR)/scenes
	$(CC) $(CFLAGS) -shared $< -o $@
	@chmod +x $@

clean:
	rm -rf $(BUILDDIR) $(BINDIR)

all: prepare $(BINDIR)/$(TARGET) $(SCENE_LIBS)
	@echo "--- Build complete ---"

run: all
	./$(BINDIR)/$(TARGET)
