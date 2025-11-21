#include <stdio.h>
#include <stdlib.h>
#include "cards_storage.h"
#include "cards.h"

void loadCardsFromFile(const char *filename, Card **cards, int *count)
{
    FILE *f = fopen(filename, "r");
    if (!f) {
        // File doesn't exist → start with empty list
        *cards = NULL;
        *count = 0;
        return;
    }

    int total;
    fscanf(f, "%d", &total);
    *count = total;

    *cards = (Card *)malloc(sizeof(Card) * total);
       for (int i = 0; i < total; i++) {
        int statusInt, shiftInt;  // add these temps

        fscanf(f, "%d %d %d %d",
               &(*cards)[i].cardNumber,
               &(*cards)[i].creationDate,
               &statusInt,
               &shiftInt);

        (*cards)[i].accessStatus = statusInt != 0;
        (*cards)[i].shift = (TimeShift)shiftInt;
    }

    fclose(f);
}

void saveCardsToFile(const char *filename, Card *cards, int count)
{
    FILE *f = fopen(filename, "w");
    if (!f) {
        printf("ERROR: Could not open file for saving.\n");
        return;
    }

    // Write number of cards
    fprintf(f, "%d\n", count);

    // Write each card
    for (int i = 0; i < count; i++) {
        fprintf(f, "%d %d %d %d\n",
                cards[i].cardNumber,
                cards[i].creationDate,
                cards[i].accessStatus,
                cards[i].shift);
    }

    fclose(f);
}
