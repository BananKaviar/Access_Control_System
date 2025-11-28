#include <string.h>   
#include <ctype.h>    
#include <stdlib.h>   
#include <stdio.h>  
#include <windows.h>
#include <stdbool.h>
#include <time.h>

#include "safeinput.h"
#include "adminMenu.h"
#include "cards.h"




TimeShift GetCurrentTimeShift(void)
{
    time_t now = time(NULL);
    struct tm *lt = localtime(&now);
    int h = lt->tm_hour; // 0–23


    if (h >= 6 && h < 14) {
        return SHIFT_MORNING;     // 06:00–13:59
    } else if (h >= 14 && h < 22) {
        return SHIFT_AFTERNOON;   // 14:00–21:59
    } else {
        return SHIFT_EVENING;       // 22:00–05:59
    }
}

bool CardHasAccessNow(const Card *card)
{
    
    if (!card->accessStatus) {
        return false;
    }

    
    if (card->shift == SHIFT_ALWAYS) {
        return true;
    }

    TimeShift current = GetCurrentTimeShift();
    return (card->shift == current);
}