#include<stdio.h>
#include<string.h>
#include<stdlib.h>

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

int main() {
    
    char deleteID[10];
    printf("กรอก EquipmentID ที่ต้องการลบ: ");
    scanf("%s", deleteID);
    deleteRecordCSV("equipment.csv", deleteID);
}