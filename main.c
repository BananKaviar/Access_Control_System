
#include <string.h>   
#include <ctype.h>    
#include <stdlib.h>   
#include <stdio.h>  
#include <windows.h>
#include <stdbool.h>

#include "safeinput.h"
#include "adminMenu.h"


typedef struct {
    int cardNumber;
    int creationDate;
    bool accessStatus;
}Card;
//add access to each card
//I am creating a struct to assign the card with necessary information



void createNew(Card *newCard){
    printf("Create a new card: \n");

    GetInputInt("Enter Creation date in the format (YYMMDD): ", &newCard->creationDate);  
    
    GetInputInt("Enter Card number:",&newCard->cardNumber);

    int accessChoice = 0;
    GetInputInt("Type 1 to give access, 0 to remove access: ", &accessChoice);
    newCard->accessStatus = (accessChoice != 0);
    
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
                printf("The green light turns ON!\n");
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

                for(int i = 0; i < listOfCards.count;i++){
                    printf("Number: %d\n", listOfCards.allCards[i].cardNumber);
                    printf("Creation date: %d\n", listOfCards.allCards[i].creationDate);

                 }

             printf("The employee count:%d\n", listOfCards.count);

                break;

            case 4:
                free(listOfCards.allCards);

                break;
        
            case 9:
                int size = sizeof(listOfCards.allCards)/sizeof(listOfCards.count);

                int searchId;

                GetInputInt("Enter Card number to be removed: ",&searchId);
            
                int foundIndex = -1;

                for (int i= 0; i<size; i++){
                    if(listOfCards.allCards->cardNumber == searchId){
                        foundIndex = i;
                        break;

                    }
                }

                if (foundIndex != -1){
                    printf("Found card id in system! created on %d\n", listOfCards.allCards->creationDate);
                    
                } else {
                    printf("Employee with cardnumber %d not found.\n", searchId);
                }
            
        
                break;

        }
    }

    return 0;
}


// function that takes an id and returns true if the id is in the system

