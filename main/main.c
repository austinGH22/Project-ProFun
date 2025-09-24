#include<stdio.h>
#include<string.h>
#include<stdlib.h>

// Function2 Add
void saverecordCSV(const char *EquipmentName,const char *EquipmentID,const char *Status,const char *MaintenanceData)
{
    FILE *fp = fopen("equipment-test.csv","a");
    if(fp == NULL)
    {
        printf("can't open file %s \n","equipment-test.csv");
        return ;
    }
    else 
    {
        fprintf(fp ,"%s,%s,%s,%s \n",EquipmentName,EquipmentID,Status,MaintenanceData);
        fclose(fp);
    }
}

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
    case 2: //Add
         char filename[]= "equipment-test.csv" ;
    char EquipmentName[50] ;
    char EquipmentID[6];
    char Status[6];
    char MaintenanceData[12];

    printf("** Enter information **\n");
    
    //EquipmentName input
    printf("EquipmentName :");
    scanf("%s",EquipmentName);

    //EquipmentID input
    printf("EquipmentID :");
    scanf("%s",EquipmentID);

    //EquipmentID input
    printf("Status :");
    scanf("%s",Status);

    //EquipmentID input
    printf("MaintenanceData :");
    scanf("%s",MaintenanceData);

    saverecordCSV(EquipmentName,EquipmentID,Status,MaintenanceData);
    printf("Finish");
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
