CC = clang

CFLAGS = -Wall -Werror -std=c23

flashcards: srs.o deck.o
	$(CC) $(CFLAGS) -o flashcards srs.o deck.o

srs.o: srs.c deck.h 
	$(CC) $(CFLAGS) -c srs.c

deck.o: deck.c
	$(CC) $(CFLAGS) -c deck.c

clean:
	rm -f srs.o
	rm -f deck.o
