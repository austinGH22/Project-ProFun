#include<stdio.h>
#include<string.h>
#include<stdlib.h>

// Function1 Search
void searchCSV(const char *filename, const char *searchID) {
    FILE *fp = fopen(filename, "r");
    if (fp == NULL) {
        printf("⚠️ ไม่สามารถเปิดไฟล์ %s ได้\n", filename);
        return;
    }

    char line[256];
    int found = 0;

    while (fgets(line, sizeof(line), fp)) {
        char copy[256];
        strcpy(copy, line);

        // ตัด \n ออก
        copy[strcspn(copy, "\n")] = 0;

        // แยกค่าด้วยเครื่องหมาย comma
        char *EquipmentName   = strtok(copy, ",");
        char *EquipmentID     = strtok(NULL, ",");
        char *Status          = strtok(NULL, ",");
        char *MaintenanceData = strtok(NULL, ",");

        if (EquipmentID != NULL && strcmp(EquipmentID, searchID) == 0) {
            printf("✅ พบข้อมูล:\n");
            printf("Name: %s\n", EquipmentName);
            printf("ID: %s\n", EquipmentID);
            printf("Status: %s\n", Status);
            printf("Maintenance: %s\n", MaintenanceData);
            found = 1;
            break; // เจอแล้วหยุดเลย
        }
    }

    if (!found) {
        printf("⚠️ ไม่พบข้อมูลที่ค้นหา (ID: %s)\n", searchID);
    }

    fclose(fp);
}

// Function2 Add
void saverecordCSV(const char *EquipmentName,const char *EquipmentID,const char *Status,const char *MaintenanceData)
{
    FILE *fp = fopen("equipment.csv","a");
    if(fp == NULL)
    {
        printf("⚠️ Can't open file %s \n","equipment.csv");
        return ;
    }
    else 
    {
        fprintf(fp ,"%s,%s,%s,%s \n",EquipmentName,EquipmentID,Status,MaintenanceData);
        fclose(fp);
    }
}

// Function4 Delete
void deleteRecordCSV(const char *filename, const char *deleteID) {
    FILE *fp = fopen(filename, "r");
    if (fp == NULL) {
        printf("⚠️ ไม่สามารถเปิดไฟล์ %s ได้\n", filename);
        return;
    }

    FILE *temp = fopen("temp.csv", "w");
    if (temp == NULL) {
        printf("⚠️ ไม่สามารถสร้างไฟล์ชั่วคราวได้\n");
        fclose(fp);
        return;
    }

    char line[256];
    int found = 0;

    while (fgets(line, sizeof(line), fp)) {
        char copy[256];
        strcpy(copy, line);

        // ตัด \n ทิ้ง
        copy[strcspn(copy, "\n")] = 0;

        // แยกข้อมูลแต่ละ column
        char *EquipmentName = strtok(copy, ",");
        char *EquipmentID   = strtok(NULL, ",");
        char *Status        = strtok(NULL, ",");
        char *MaintenanceData = strtok(NULL, ",");

        if (EquipmentID != NULL && strcmp(EquipmentID, deleteID) == 0) {
            printf("✅ ลบข้อมูล ID: %s เรียบร้อย\n", deleteID);
            found = 1;
            // ไม่เขียนบรรทัดนี้ลง temp (ข้าม = ลบ)
            continue;
        }
        // ถ้าไม่ใช่ record ที่ต้องลบ → เขียนลง temp
        fputs(line, temp);
    }

    if (!found) {
        printf("⚠️ ไม่พบข้อมูล ID: %s\n", deleteID);
    }

    fclose(fp);
    fclose(temp);

    // ลบไฟล์เก่า → เปลี่ยนชื่อไฟล์ใหม่
    remove(filename);
    rename("temp.csv", filename);
}


int main(){
    char filename[] = "equipment.csv" ;
    char EquipmentName[50] ;
    char EquipmentID[6];
    char Status[6];
    char MaintenanceData[12];
    int choice;
    
    char searchID[10];
    char deleteID[10];
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
    case 1: //search
    
        break;
    case 2: //Add
        printf("** Enter information **\n");
    
        //EquipmentName input
        printf("EquipmentName :");
        scanf(" %[^\n]",EquipmentName);

        //EquipmentID input
        printf("EquipmentID :");
        scanf(" %[^\n]",EquipmentID);

        //EquipmentID input
        printf("Status :");
        scanf(" %[^\n]",Status);

        //EquipmentID input
        printf("MaintenanceData :");
        scanf(" %[^\n]",MaintenanceData);

        saverecordCSV(EquipmentName,EquipmentID,Status,MaintenanceData);
        printf("Finish");
        break;
    case 3:
        
        break;
    case 4:
        printf("กรอก EquipmentID ที่ต้องการลบ: ");
        scanf("%s", deleteID);
        deleteRecordCSV("equipment.csv", deleteID);
        break;
    case 5:
        
        break;
    default:
        break;
    }
    
    return 0;
}
