
#include <string.h>   
#include <ctype.h>    
#include <stdlib.h>   
#include <stdio.h>  

#include "safeinput.h"
#include "adminMenu.h"

typedef struct {
    int cardNumber;
    char creationDate[20];
    int start;
    int end;  //I am creating a struct to assign the card with necessary information
}Card;


void createNew(Card *newCard){
    printf("Create a new card: \n");

    GetInput("Enter Creation date in the format (YYMMDD):  \n", newCard->creationDate,20);
    
    GetInputInt("Enter Card number:",&newCard->cardNumber);

    GetInputInt("Enter start day: ",&newCard ->start);

    GetInputInt("Enter end day: ",&newCard ->end);
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
            case 3:
            printf("Type 1. to add and 2. to remove access:");
            int choice;
            scanf(" %d", &choice);

                if (choice == 1) {

                if (listOfCards.count == 0) {
                    listOfCards.allCards = malloc(sizeof(Card));
                } else {
                    int newSize = (listOfCards.count + 1) * sizeof(Card);
                    listOfCards.allCards = realloc(listOfCards.allCards,newSize);
                }

                 createNew(&listOfCards.allCards[listOfCards.count]);
                listOfCards.count++ ;
                printf("The employee count:%d\n", listOfCards.count);

            // } else if (choice == 2) {
            //     printf ("Enter Card number to be removed: ");
            //     int searchID;
            //     scanf(" %d", &searchID);
            //     int foundIndex = -1;

            //     int size= listOfCards.count;

            // for (int i= 0; i<size; i++){
            //     if(listOfCards.allCards->cardNumber == searchID){
            //         foundIndex = i;
            //         break;

            //     }
            // }

            //     int removeCard = (listOfCards.count - 1)* sizeof(Card);
            //     listOfCards.allCards= realloc(listOfCards.allCards, removeCard);

            //     createNew(&listOfCards.allCards[listOfCards.count]);
            //     listOfCards.count-- ;
            //     printf("The employee count: %d\n", listOfCards.count);
            // } else {
            //     printf("Error!");
            //     break;
            // }

        

             
            //     break;
            

            //     createNew(&listOfCards.allCards[listOfCards.count]);
            //     listOfCards.count++ ;
            //     printf("The employee count:%d\n", listOfCards.count);
                
            //     break;

            case 2:
                printf("List all\n");

                for(int i = 0; i < listOfCards.count;i++){
                    printf("Number: %d\n", listOfCards.allCards[i].cardNumber);
                    printf("Creation date: %s\n", listOfCards.allCards[i].creationDate);
                }

                break;

            case 4:
                free(listOfCards.allCards);

                break;
        
            case 9:
            int size = sizeof(listOfCards.allCards)/sizeof(listOfCards.count);

            int searchId;

            printf("Enter the employee card number: ");
            scanf(" %d", &searchId);
            
            int foundIndex = -1;

            for (int i= 0; i<size; i++){
                if(listOfCards.allCards->cardNumber == searchId){
                    foundIndex = i;
                    break;

                }
            }

            if (foundIndex != -1){
                printf("Found card id in system! created on %s\n", listOfCards.allCards->creationDate);
                
            } else {
                printf("Employee with cardnumber %d not found.\n", searchId);
            }
            
        
                return 0;

        }
    }

    return 0;
}

// function that takes an id and returns true if the id is in the system

