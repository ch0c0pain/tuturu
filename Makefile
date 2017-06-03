NAME := tuturu
BUILD := build
PREFIX :=
CFLAGS := -g -Wall -std=c99 -pedantic -c -D_XOPEN_SOURCE=500 -D_POSIX_C_SOURCE=200112L
LDFLAGS := -lncurses -lFLAC -lpulse-simple -lpthread

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
