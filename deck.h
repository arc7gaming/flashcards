typedef struct card {
    char **text;
    int val;
    struct card *next;
} card;

typedef struct card *Deck;

Deck newDeck();

int isEmpty(Deck deck);

void enq(Deck deck, char *front, char *back, int x);

card *deq(Deck deck);
