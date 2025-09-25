#include<stdio.h>

int main(){
    
    int choice;
    //compusive only 1-5 choice 
    do {
     printf("##### Factory Equipment Operation Management System #####\n");
    printf("Menu\n");
    printf("1)Search\n");
    printf("2)Add\n");
    printf("3)update\n");
    printf("4)Delete\n");
    printf("5)Exit Program\n");

    
    printf("Choose function (1-5):");
    scanf("%d",&choice);
    } while (choice != 1 && choice !=2 && choice !=3 && choice !=4 && choice !=5 );

    switch (choice)
    {
    case 1:
        
        break;
    case 2:
        printf("lol");
        break;
    case 3:
        
        break;
    case 4:
        
        break;
    case 5:
        
        break;
    default:
        break;
    }
    
    return 0;
}
