NAME := tuturu
BUILD := build
PREFIX :=
CFLAGS := -g -Wall -std=gnu99 -c
LDFLAGS := -lncurses

SOURCES := $(wildcard src/*.c)
OBJECTS := $(addprefix $(BUILD)/,$(notdir $(SOURCES:.c=.o)))

.PHONY: all

all: $(BUILD) $(BUILD)/$(NAME)

$(BUILD):
	mkdir -p $@

$(BUILD)/$(NAME): $(OBJECTS)
	gcc -g -o $@ $(OBJECTS) $(LDFLAGS)

$(BUILD)/%.o: src/%.c
	gcc -o $@ $< $(CFLAGS)

.PHONY: clean

clean:
	rm -rf $(BUILD)
