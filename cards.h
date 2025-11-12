#include <stdlib.h>   
#include <stdio.h>  
#include <windows.h>
#include <stdbool.h>


typedef struct {
    int cardNumber;
    int creationDate;
    bool accessStatus;
}Card;

typedef struct{
    Card *allCards; 
    int count;
} CARDSLIST;