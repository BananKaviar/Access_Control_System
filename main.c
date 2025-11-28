
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

    GetInputInt("Enter Card number: ", &newCard->cardNumber);

    int accessChoice = 0;
    GetInputInt("Type 1 to give access, 0 to remove access: ", &accessChoice);
    newCard->accessStatus = (accessChoice != 0);

    if (newCard->accessStatus) {

        printf("Choose time shift:\n");
        printf("0 = Morning (06-14)\n");
        printf("1 = Afternoon (14-22)\n");
        printf("2 = Evening (22-06)\n");
        printf("3 = Always (24/7)\n");

        int tmpShift;
        GetInputInt("Enter shift (0-3): ", &tmpShift);

        
        newCard->shift = (TimeShift)tmpShift;

    } else {
        
        newCard->shift = SHIFT_NONE; 
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
        {0000, 201213, true, SHIFT_ALWAYS},
        {0001, 200114, true, SHIFT_MORNING},
        {0010, 200214, false, SHIFT_MORNING},
        {0011, 200314, true, SHIFT_AFTERNOON},
        {0100, 200414, true, SHIFT_AFTERNOON},
        {0101, 200514, false, SHIFT_EVENING},
        {0110, 200614, true, SHIFT_EVENING},
        {0111, 200714, false, SHIFT_MORNING},
        {1000, 200814, true, SHIFT_AFTERNOON},
        {1001, 200914, true, SHIFT_EVENING}
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
            for (int i = 0; i < listOfCards.count; i++){
                if (listOfCards.allCards[i].cardNumber == tmp.cardNumber){
                    found = i;
                    break;
                }
            }

                if (found != -1){
                    
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

                    printf("CURRENTLY LAMP IS: "COLOR_RED  "Red" COLOR_RESET" \n");
                }

                break;
            }
        }

    }
}




