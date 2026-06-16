#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "deck.h"

// httis://www.geeksforgeeks.org/c/c-program-to-implement-priority-queue/

Deck newDeck() {

    Deck deck = malloc(sizeof(card));
    deck->next = NULL;

    return deck;

}

int isEmpty(Deck deck) {
    return deck->next == NULL;
}

void enq(Deck deck, char *front, char *back, int x){

    card *start = deck->next;

    card *temp = malloc(sizeof(card));
    temp->text = (char **)malloc(2 * sizeof(char *));

    temp->text[0] = (char *)malloc(strlen(front) * sizeof(char));
    temp->text[0] = front;
    temp->text[1] = (char *)malloc(strlen(back) * sizeof(char));
    temp->text[1] = back;
    temp->val = x;
    temp->next = NULL;
    
    if (isEmpty(deck)) {
        deck->next = temp;
        return;
    }

    if (deck->next->val > x) {

        temp->next = deck->next;
        deck->next = temp;

    }
    else {

        while (start->next != NULL && start->next->val < x) {

            start = start->next;

        }
        temp->next = start->next;
        start->next = temp;
    }

}

card *deq(Deck deck) {
    
    card *top = deck->next;
    deck->next = top->next;
    return top;

}

/*
int main() {
    Deck deck = newDeck();
    enq(deck, "front2", "back2", 1);
    enq(deck, "front1", "back1", 2);
    enq(deck, "front3", "back3", 3);

    while (!isEmpty(deck)) {
        card *top = deq(deck);
    }
    return 0;
}
*/
