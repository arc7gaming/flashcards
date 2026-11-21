#ifndef DECK_H
#define DECK_H

typedef struct Card {
  char **text;
  int val;
  struct Card *next;
} Card;

typedef struct Card *Deck;

Deck newDeck();

int isEmpty(Deck deck);

void enq(Deck deck, char *front, char *back, int x);

Card *deq(Deck deck);

#endif
