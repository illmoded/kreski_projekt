CC := g++
SRCDIR := src
BUILDDIR := build
TARGET := main.x
 
SRCEXT := cpp
SOURCES := $(shell find $(SRCDIR) -type f -name *.$(SRCEXT))
OBJECTS := $(patsubst $(SRCDIR)/%,$(BUILDDIR)/%,$(SOURCES:.$(SRCEXT)=.o))
CFLAGS := 
INC := -I include
LIB := `pkg-config --cflags --libs allegro-5.0 allegro_primitives-5.0 allegro_image-5.0`

.PHONY: run clean all

$(BUILDDIR)/%.o: $(SRCDIR)/%.$(SRCEXT)
	mkdir -p $(BUILDDIR)
	$(CC) -c -Wall $(CFLAGS) $(INC) -o $@ $< $(LIB)

$(TARGET): $(OBJECTS)
	$(CC) $^ -o $(TARGET) $(LIB)

all: $(TARGET)

clean:
	-rm -rf $(BUILDDIR)
	-rm $(TARGET)
	-rm *.txt

run: $(TARGET)
	./$(TARGET)
