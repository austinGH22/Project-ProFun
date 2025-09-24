#include<stdio.h>
#include<string.h>
#include<stdlib.h>

// Function1 
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

//

int main()
{
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
    return 0;
}