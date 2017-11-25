CFLAGS+=-Wall -std=c++17 $(EXTRA_ARGS)
CC=g++

calc: calc.cpp parser.cpp
	$(CC) $(CFLAGS) -o $@ $^
