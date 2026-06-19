TARGET = SiliconPostLife
CC = gcc
SRCDIR = src
BUILDDIR = build
BINDIR = bin

SOURCES = $(wildcard $(SRCDIR)/*.c)
OBJECTS = $(patsubst $(SRCDIR)/%.c, $(BUILDDIR)/%.o, $(SOURCES))

SCENE_SOURCES = $(wildcard $(SRCDIR)/scenes/*.c)
SCENE_LIBS = $(patsubst $(SRCDIR)/scenes/%.c, $(BINDIR)/scenes/%.so, $(SCENE_SOURCES))

CFLAGS = -g -I$(SRCDIR) $(VERSION_FLAG)
LIBS = -lraylib -lm -lpthread -ldl -lcsv -rdynamic

prepare:
	@mkdir -p $(BUILDDIR)
	@mkdir -p $(BINDIR)/scenes
	@mkdir -p $(BINDIR)/res
	@cp $(SRCDIR)/scenes/scenes.inf $(BINDIR)/scenes/
	@cp -r $(SRCDIR)/res $(BINDIR)/res

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
