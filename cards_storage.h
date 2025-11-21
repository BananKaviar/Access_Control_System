#ifndef CARD_STORAGE_H
#define CARD_STORAGE_H

#include "cards.h"


// Loads cards from a file into a dynamic list
void loadCardsFromFile(const char *filename, Card **cards, int *count);

// Saves all cards from a list to a file
void saveCardsToFile(const char *filename, Card *cards, int count);

#endif
