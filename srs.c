#include "deck.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void readFile(Deck deck) {
  FILE *fp = fopen("cards.txt", "r");
  if (fp == NULL) {
    return;
  }
  char line[1024];

  int i = 0;
  char *front;
  char *back;

  while (fgets(line, sizeof(line), fp)) {
    if (i == 0) {
      front = strdup(line);
      i++;
    } else if (i == 1) {
      back = strdup(line);
      i = 0;
      enq(deck, front, back, 0);
    }
  }
  fclose(fp);
}

void runCards(Deck deck) {

  printf("Enter q to quit");

  for (;;) {
    card *current_card = deq(deck);

    printf("\n%s\n", current_card->text[0]);

    printf("Enter to see back: ");

    getc(stdin);

    printf("\n%s\n", current_card->text[1]);

    printf("Enter fail/pass(1/2): ");

    int x;

    char buffer[1024];
    while (fgets(buffer, sizeof(buffer), stdin)) {
      if (sscanf(buffer, "%d", &x) == 1) {
        if (x >= 2) { // pass
          x = 2;
        } else { // fail
          x = 1;
        }
        enq(deck, current_card->text[0], current_card->text[1],
            current_card->val + x);
        break;
      } else {
        enq(deck, current_card->text[0], current_card->text[1],
            current_card->val);
        free(current_card->text[0]);
        free(current_card->text[1]);
        free(current_card->text);
        free(current_card);
        return;
      }
    }
  }
}

void openDeck(Deck deck) {
  if (!isEmpty(deck))
    runCards(deck);
  else {
    printf("This deck is empty\n");
  }
}

void addCard(Deck deck) {
  FILE *fp = fopen("cards.txt", "a");

  printf("Enter front: ");

  char front[1024];
  char back[1024];

  fgets(front, sizeof(front), stdin);

  printf("Enter back: ");

  fgets(back, sizeof(back), stdin);

  fprintf(fp, "%s", front);
  fprintf(fp, "%s", back);

  char *front_copy = strdup(front);
  char *back_copy = strdup(back);
  enq(deck, front_copy, back_copy, 0);

  fclose(fp);
}

void emptyQueue(Deck deck) {
  FILE *fp = fopen("cards_temp.txt", "w");

  while (!isEmpty(deck)) {
    card *current_card = deq(deck);
    fputs(current_card->text[0], fp);
    fputs(current_card->text[1], fp);

    free(current_card);
  }

  fclose(fp);

  remove("cards.txt");
  rename("cards_temp.txt", "cards.txt");
}

int main(int argc, char **argv) {

  Deck deck = newDeck();
  readFile(deck);

  for (;;) {
    printf("1. Open deck\n2. Add card\n3. Quit\n> ");

    int choice;
    char buffer[1024];
    while (fgets(buffer, sizeof(buffer), stdin)) {
      if (sscanf(buffer, "%d", &choice) == 1) {
        break;
      } else {
        printf("Invalid input\n> ");
      }
    }

    if (choice == 1) {
      openDeck(deck);
    } else if (choice == 2) {
      addCard(deck);
    } else {
      emptyQueue(deck);
      return 0;
    }
  }

  return 0;
}
