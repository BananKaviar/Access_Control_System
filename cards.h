#include <stdlib.h>   
#include <stdio.h>  
#include <windows.h>
#include <stdbool.h>

typedef enum{
    SHIFT_MORNING,  //from 0600-1400
    SHIFT_AFTERNOON, //from 1400-2200
    SHIFT_EVENING, //from 2200-0600
    SHIFT_ALWAYS, //24X7 access
}TimeShift;


typedef struct {
    int cardNumber;
    int creationDate;
    bool accessStatus;
    TimeShift shift;
}Card;


extern Card cards[10];

void showAllCards(void);

TimeShift GetCurrentTimeShift(void);
bool CardHasAccessNow(const Card *card);

