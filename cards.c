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


Card cards[10] = {
    {1, 201312, true, SHIFT_ALWAYS},
    {2, 201401, true,SHIFT_AFTERNOON},
    {3, 201402, false,SHIFT_EVENING},
    {4, 201403, true,SHIFT_MORNING},
    {5, 201404, true,SHIFT_AFTERNOON},
    {6, 201405, false, SHIFT_EVENING},
    {7, 201406, true, SHIFT_MORNING},
    {8, 201407, false, SHIFT_AFTERNOON},
    {9, 201408, true, SHIFT_EVENING},
    {10, 201409, true, SHIFT_MORNING}
};

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
    // If access flag is off, never allow
    if (!card->accessStatus) {
        return false;
    }

    // Admin cards always have access
    if (card->shift == SHIFT_ALWAYS) {
        return true;
    }

    TimeShift current = GetCurrentTimeShift();
    return (card->shift == current);
}