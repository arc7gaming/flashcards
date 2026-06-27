#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "deck.c"

// https://www.geeksforgeeks.org/c/read-a-file-line-by-line-in-c/

void readFile(Deck deck) {
  FILE *fp = fopen("cards.txt", "r");
  if (fp == NULL) {
    return;
  }
  char line[256];

  int i = 0;
  char *front;
  char *back;

  while (fgets(line, sizeof(line), fp)) {
    if (i == 0) {
      front = strdup(line);
      i++;
    }
    else if (i == 1) {
      back = strdup(line);
      i = 0;
      enq(deck, front, back, 0);
    }
  }
  fclose(fp);
}

void runCards(Deck deck) {
  if (isEmpty(deck)) {
    printf("No cards found\n");
    return;
  }
  for (;;) {
    card *current_card = deq(deck);

    printf("\n%s\n", current_card->text[0]);

    printf("Enter to see back: ");

    char ch;
    if (scanf("%c", &ch) == 1) {
      if (ch == 'q') {
        enq(deck, current_card->text[0], current_card->text[1], current_card->val);

        return;
      }
      printf("\n%s\n", current_card->text[1]);
    }
        
    printf("Enter fail/pass(1/2): ");  

    int x;
        
    if (scanf("%d", &x) == 1) {
      if (x >= 2) {  // pass 
        x = 2;
      }
      else {  // fail 
        x = 1;
      }
    }
    else {  // fail 
      enq(deck, current_card->text[0], current_card->text[1], current_card->val);

      return;
    }
        
    while ((getchar()) != '\n');

    enq(deck, current_card->text[0], current_card->text[1], current_card->val + x);
  }
}

void addCard(Deck deck) {
  FILE *fp = fopen("cards.txt", "a");

  printf("Enter front: ");
  
  char front[1024];
  char back[1024];

  scanf("%s", front);
  
  printf("Enter back: ");

  scanf("%s", back);

  fprintf(fp, "%s\n", front);
  fprintf(fp, "%s\n", back);

  readFile(deck);

  fclose(fp);
}

void emptyQueue(Deck deck) {
  FILE *fp = fopen("cards.txt", "w");
  while (!isEmpty(deck)) {
    card *current_card = deq(deck);
    fputs(current_card->text[0], fp);
    fputs(current_card->text[1], fp);

    free(current_card);
  }
  fclose(fp);
}

int main(int argc, char **argv) {

  printf("Enter q at any time to quit\n");
  
  Deck deck = newDeck();
  readFile(deck);

  for (;;) {
    printf("1. Open deck\n2. Add card\n>");

    int choice;
    scanf("%d", &choice);

    if (choice == 1) {
      runCards(deck);
    }
    else if (choice == 2) {
      addCard(deck);
    }
    else {
      emptyQueue(deck);
      return 0;
    }
  }

  return 0;

}
