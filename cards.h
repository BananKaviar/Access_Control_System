typedef struct {
    int cardNumber;
    int creationDate;
    int start;
    int end;
} Card;

typedef struct {
    Card *allCards;
    int count;
} CardList;