CC=gcc
CFLAGS=-lpthread -Wall -Wextra -fpic -I/usr/include/libxml2 -lxml2 -lz -lm -ldl -g

OUT = ./bin/cinemaSimulator

SRC=$(wildcard ./src/*.c) 


all: $(OUT)
	
clean: 
	rm $(OUT)

$(OUT): $(SRC)
	$(CC) -o $@ $^ $(CFLAGS)
