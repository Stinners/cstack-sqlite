
all: compile

compile:
	cc src/main.c -o build/main

clean:
	rm -f build/*

run: compile
	./build/main

_dummy := $(shell mkdir -p build)
