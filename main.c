
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

    GetInputInt("Type 1 to give access and type 2 to remove access",&newCard ->accessStatus);
    
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


            case 3: 
            createNew(&listOfCards.allCards[listOfCards.count]);
            if()

            
            



            // case 3:
            //     createNew(&listOfCards.allCards[listOfCards.count]);
                
            //     printf("do we reach here?");
            //     int found =-1;
            //     for (int i = 0; i< listOfCards.count; i++){
            //         if(listOfCards.allCards[i].cardNumber == listOfCards.allCards[listOfCards.count].cardNumber){
            //             found = i;
            //         }
            //     }
            //     if (found != -1){
            //         char answer;
            //         GetInputChar("This card already exists. Do you want to delete it? (y/n): ", &answer);

            //         if (answer == 'y' || answer == 'Y'){
            //             for (int j = found; j < listOfCards.count-1; j++){
            //                 listOfCards.allCards[j] = listOfCards.allCards[j+1];
            //             }
            //             listOfCards.count--;
            //             printf("Card removed!\n");
            //         } else { 
            //             printf ("No changes were made\n");
            //         }
            //     } else {
            //         if(listOfCards.count == 0){
            //             listOfCards.allCards = malloc(sizeof(Card));
            //         } else {
            //             int newsize = (listOfCards.count + 1)* sizeof(Card);
            //             listOfCards.allCards = realloc(listOfCards.allCards, newsize);
            //         }
            //         listOfCards.count++;

            //         printf("The employee count: %d \n", listOfCards.count);
            //     }

            //     break;




                // int choice;
        
                // GetInputInt("Enter 1 for adding and 2 for removing access",&choice);

                // if(choice==1) {

                //     if (listOfCards.count == 0) {
                //         listOfCards.allCards = malloc(sizeof(Card));
                //     } else {
                //         int newSize = (listOfCards.count + 1) * sizeof(Card);
                //         listOfCards.allCards = realloc(listOfCards.allCards,newSize);
                //     }
                    
                //     createNew(&listOfCards.allCards[listOfCards.count]);

                //     listOfCards.count++ ;

                //     printf("The employee count:%d\n", listOfCards.count);

                   
                // } else if (choice == 2) {
                    
                //     int searchID;
                //     GetInputInt("Enter Card number to be removed: ",&searchID);

                //     int foundId = -1;

                //     int Cardsize= listOfCards.count;

                //     for (int i= 0; i<Cardsize; i++){
                //         if(listOfCards.allCards->cardNumber == searchID){
                //             foundId = i;
                //             break;

                //         } else {
                //             foundId= -1;
                //         }
                //     }
                    
                //     if (foundId == -1)
                //     printf("not found");
                //     else
                //     printf("found!");

                //     int removeCard = (listOfCards.count - 1)* sizeof(Card);
                //     listOfCards.allCards= realloc(listOfCards.allCards, removeCard);
                // }

                // break;


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

