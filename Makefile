
all: compile

compile:
	cc src/*.c -o build/main

clean:
	rm -f build/*

run: compile
	rlwrap ./build/main

_dummy := $(shell mkdir -p build)
