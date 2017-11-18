CFLAGS+=-std=c++17
# must support c++17 for real (variants)
CC=g++

calc: calc.cpp
	$(CC) $(CFLAGS) -o $@ $^
