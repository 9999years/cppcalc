CFLAGS+=-std=c++17
CC=clang++

calc: calc.cpp
	$(CC) $(CFLAGS) -o $@ $^
