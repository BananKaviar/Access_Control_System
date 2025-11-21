
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
    Card *allCards; // this struct is more for listing all cards it stores and keeps a count on them
    int count;
} CARDSLIST;



int main(){
    CARDSLIST listOfCards;
    listOfCards.count = 0;
    listOfCards.allCards = NULL;

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

                    printf("Added card %d. Employee count: %d\n", tmp.cardNumber, 10+listOfCards.count);
                }
                break;
                }

            case 2:
                printf("List all\n");

                 for (int i = 0; i < 10; i++) {
                    printf("Number: %d\n", cards[i].cardNumber);
                    printf("Creation date: %d\n", cards[i].creationDate);
                 }

                for(int i = 0; i < listOfCards.count;i++){
                    printf("Number: %d\n", listOfCards.allCards[i].cardNumber);
                    printf("Creation date: %d\n", listOfCards.allCards[i].creationDate);

                 }

             printf("The employee count:%d\n", 10 +listOfCards.count);

                break;

            case 4:
                free(listOfCards.allCards);

                break;
        
            case 9: {
                int searchId;
                GetInputInt("Enter Card number to test scan: ", &searchId);

                const Card *foundCard = NULL;

                for (int i = 0; i < 10; i++) {
                    if (cards[i].cardNumber == searchId) {
                        foundCard = &cards[i];
                        break;
                    }
                }

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


// function that takes an id and returns true if the id is in the system

