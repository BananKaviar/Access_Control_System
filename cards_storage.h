#ifndef CARD_STORAGE_H
#define CARD_STORAGE_H

#include "cards.h"



void loadCardsFromFile(const char *filename, Card **cards, int *count);


void saveCardsToFile(const char *filename, Card *cards, int count);

#endif
