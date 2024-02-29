
BINFOLDER := bin/

INCFOLDER := inc/

SRCFOLDER := src/

OBJFOLDER := obj/
CC := gcc
CFLAGS := -std=c99 -w
LINKFLAGS := -lwiringPi -lpthread
SRCFILES := $(wildcard src/*.c)
CONFIG_FILE=`grep "^[^\#*/;]" $(FILE)`
all: $(SRCFILES:src/%.c=obj/%.o)
	$(CC) $(CFLAGS) obj/*.o -o bin/main $(LINKFLAGS)

obj/%.o: src/%.c
	$(CC) $(CFLAGS) -c $< -o $@ -I./inc $(LINKFLAGS)

run: bin/main
	bin/main

.PHONY: clean
clean:
	rm -rf obj/*.o
	rm -rf bin/main
	touch obj/.gitkeep
	touch bin/.gitkeep