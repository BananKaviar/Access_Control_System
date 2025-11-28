
#include <string.h>   
#include <ctype.h>    
#include <stdlib.h>   
#include <stdio.h>  
#include <windows.h>
#include <stdbool.h>

#include "safeinput.h"
#include "adminMenu.h"
#include "cards.h"
#include <time.h> 
#include "cards_storage.h"

#define COLOR_RED     "\x1b[31m"
#define COLOR_GREEN   "\x1b[32m"
#define COLOR_RESET   "\x1b[0m"





void createNew(Card *newCard){
    printf("Create a new card: \n");

    GetInputInt("Enter Creation date in the format (YYMMDD): ", &newCard->creationDate);  
    
    GetInputInt("Enter Card number:",&newCard->cardNumber);

    int accessChoice = 0;
    GetInputInt("Type 1 to give access, 0 to remove access: ", &accessChoice);
    newCard->accessStatus = (accessChoice != 0);


    if (newCard->accessStatus) {
    
    GetInputInt("Enter time shift (HHMM-HHMM): ", &newCard->shift);
    } else {
    
    newCard->shift = 0;
    }


    int shiftChoice = 0;
    printf("Select time shift:\n");
    printf(" 1. Morning shift\n");
    printf(" 2. Afternoon shift\n");
    printf(" 3. Night shift\n");
    printf(" 4. Admin (always access)\n");
    GetInputInt("Enter shift (1-4):",&shiftChoice);

    switch (shiftChoice) {
        case 1: newCard->shift = SHIFT_MORNING;    break;
        case 2: newCard->shift = SHIFT_AFTERNOON;  break;
        case 3: newCard->shift = SHIFT_EVENING;      break;
        case 4: newCard->shift = SHIFT_ALWAYS;      break;
        default:
            printf("Invalid choice, defaulting to Morning shift.\n");
            newCard->shift = SHIFT_MORNING;
            break;
    }
    
    
}



typedef struct{
    Card *allCards; 
    int count;
} CARDSLIST;



int main(){
    CARDSLIST listOfCards;
    loadCardsFromFile("cards.db", &listOfCards.allCards, &listOfCards.count);

    if (listOfCards.count == 0) {
    printf("No cards found on disk — loading default 10 cards.\n");

    Card defaultCards[10] = {
        {1, 201312, true, SHIFT_ALWAYS},
        {2, 201401, true, SHIFT_MORNING},
        {3, 201402, false, SHIFT_MORNING},
        {4, 201403, true, SHIFT_AFTERNOON},
        {5, 201404, true, SHIFT_AFTERNOON},
        {6, 201405, false, SHIFT_EVENING},
        {7, 201406, true, SHIFT_EVENING},
        {8, 201407, false, SHIFT_MORNING},
        {9, 201408, true, SHIFT_AFTERNOON},
        {10, 201409, true, SHIFT_EVENING}
    };

    listOfCards.count = 10;
    listOfCards.allCards = malloc(sizeof(Card) * 10);
    memcpy(listOfCards.allCards, defaultCards, sizeof(defaultCards));
}


    while(true){
        AdminMenu();

        int selection;
     
        while(true){
            bool ok = GetInputInt("Enter choice:", &selection);

            if(ok){
                break;
            }
            
            printf("Enter the right data!");
        }

        switch(selection){

            case 1:
                printf("The light turns ON it is: " COLOR_GREEN "Green" COLOR_RESET "\n");
                Sleep(3000);
                printf("The door is open Välkommen!\n");
                break;


            case 3: {
        
             Card tmp;
             createNew(&tmp);

            int found = -1;
            for (int i = 0; i < listOfCards.count; i++) {
                if (listOfCards.allCards[i].cardNumber == tmp.cardNumber) {
                    found = i;
                    break;
                }
            }

                if (found != -1) {
                    
                    listOfCards.allCards[found].accessStatus = tmp.accessStatus;

                    printf("Updated card %d: access is now %s.\n",
                        tmp.cardNumber,
                        listOfCards.allCards[found].accessStatus ? "ON" : "OFF");
                } else {
      
                    if (listOfCards.count == 0) {
                        listOfCards.allCards = (Card*)malloc(sizeof(Card));
                    } else {
                        int newSize = (listOfCards.count + 1) * (int)sizeof(Card);
                        listOfCards.allCards = (Card*)realloc(listOfCards.allCards, newSize);
                    }

                    listOfCards.allCards[listOfCards.count] = tmp;
                    listOfCards.count++;

                    printf("Added card %d. Employee count: %d\n", tmp.cardNumber, listOfCards.count);
                }
                break;
                }

            case 2:
              printf("List all\n");

                for (int i = 0; i < listOfCards.count; i++) {
                Card c = listOfCards.allCards[i];

            printf("Number: %d\n", c.cardNumber);
            printf("Creation date: %d\n", c.creationDate);
                }

            printf("The employee count: %d\n", listOfCards.count);

            break;

            case 4:
                saveCardsToFile("cards.db", listOfCards.allCards, listOfCards.count);
                printf("Cards saved. Goodbye!\n");
                free(listOfCards.allCards);
                exit(0);
        
            case 9: {
                int searchId;
                GetInputInt("Enter Card number to test scan: ", &searchId);

                const Card *foundCard = NULL;


                if (foundCard == NULL) {
                    for (int i = 0; i < listOfCards.count; i++) {
                        if (listOfCards.allCards[i].cardNumber == searchId) {
                            foundCard = &listOfCards.allCards[i];
                            break;
                        }
                    }
                }

                if (foundCard == NULL) {
                    printf("Card %d not in system.\n", searchId);
                    printf("CURRENTLY LAMP IS: " COLOR_RED "Red" COLOR_RESET " \n");
                    break;
                }

                if (CardHasAccessNow(foundCard)) {
                    printf("Card %d FOUND! Created %d\n",
                        foundCard->cardNumber, foundCard->creationDate);

                    printf("The light turns ON it is: " COLOR_GREEN "Green" COLOR_RESET "\n");
                } else {
                    printf("Card %d FOUND, but NO ACCESS at this time.\n",
                        foundCard->cardNumber);

                    printf("CURRENTLY LAMP IS: Red\n");
                }

                break;
            }
        }

    }
}




