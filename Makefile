CC = clang

CFLAGS = -Wall -Werror -std=c23

bin/flashcards: bin/srs.o bin/deck.o
	$(CC) $(CFLAGS) -o bin/flashcards bin/srs.o bin/deck.o

bin/srs.o: srs.c deck.h 
	$(CC) $(CFLAGS) -c srs.c -o bin/srs.o

bin/deck.o: deck.c
	$(CC) $(CFLAGS) -c deck.c -o bin/deck.o

clean:
	rm -f bin/*
