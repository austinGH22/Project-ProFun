#include<stdio.h>
#include<string.h>
#include<stdlib.h>

// add
void saverecordCSV(const char *EquipmentName,const char *EquipmentID,const char *Status,const char *MaintenanceData)
{
    FILE *fp = fopen("equipment-test2.csv","a");
    if(fp == NULL)
    {
        printf("can't open file %s \n","equipment-test2.csv");
        return ;
    }
    else 
    {
        fprintf(fp ,"%s,%s,%s,%s \n",EquipmentName,EquipmentID,Status,MaintenanceData);
        fclose(fp);
    }
}