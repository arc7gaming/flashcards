#include "deck.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// httis://www.geeksforgeeks.org/c/c-program-to-implement-priority-queue/

Deck newDeck() {

  Deck deck = malloc(sizeof(Card));
  deck->next = NULL;

  return deck;
}

int isEmpty(Deck deck) { return deck->next == NULL; }

void enq(Deck deck, char *front, char *back, int x) {

  Card *start = deck->next;

  Card *temp = malloc(sizeof(Card));
  temp->text = (char **)malloc(2 * sizeof(char *));

  temp->text[0] = strdup(front);
  temp->text[1] = strdup(back);
  temp->val = x;
  temp->next = NULL;

  if (isEmpty(deck)) {
    deck->next = temp;
    return;
  }

  if (deck->next->val > x) {

    temp->next = deck->next;
    deck->next = temp;

  } else {

    while (start->next != NULL && start->next->val < x) {

      start = start->next;
    }
    temp->next = start->next;
    start->next = temp;
  }
}

Card *deq(Deck deck) {

  if (isEmpty(deck))
    return NULL;

  Card *top = deck->next;
  deck->next = top->next;
  return top;
}

#ifdef TEST

int main() {
  Deck deck = newDeck();
  enq(deck, "front2", "back2", 1);
  enq(deck, "front1", "back1", 2);
  enq(deck, "front3", "back3", 3);

  while (!isEmpty(deck)) {
    Card *top = deq(deck);
  }
  return 0;
}

#endif
