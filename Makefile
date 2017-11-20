CFLAGS+=-Wall -std=c++17 $(EXTRA_ARGS)
CC=g++

calc: calc.cpp
	$(CC) $(CFLAGS) -o $@ $^
