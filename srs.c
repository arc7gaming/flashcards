#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "deck.c"

// https://www.geeksforgeeks.org/c/read-a-file-line-by-line-in-c/

int main(int argc, char **argv) {

    Deck deck = newDeck();

    FILE *fp = fopen(argv[1], "r");
    if (fp == NULL) {
        fprintf(stderr, "File missing\n");
        exit(EXIT_FAILURE);
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

    printf("Enter q to quit\n");

    for(;;) {
        if (isEmpty(deck)) {
            break;
        }

        card *current_card = deq(deck);

        printf("\n%s\n", current_card->text[0]);

        printf("Enter to see back: ");

        char ch;
        if (scanf("%c", &ch) == 1) {
            if (ch == 'q') {
              enq(deck, current_card->text[0], current_card->text[1], current_card->val);

              break;
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

            break;
        }
        
        while ((getchar()) != '\n');

        enq(deck, current_card->text[0], current_card->text[1], current_card->val + x);

    }
    
    fp = fopen(argv[1], "w");

    while (!isEmpty(deck)) {
        card *current_card = deq(deck);
        fputs(current_card->text[0], fp);
        fputs(current_card->text[1], fp);

        free(current_card);
    }

    fclose(fp);

    return 0;

}
