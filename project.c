#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100

typedef struct {
    char name[50];
    char id[10];
    char status[20];
    char date[15];
} Equipment;

Equipment list[MAX];
int count = 0;

// โหลดข้อมูลจากไฟล์ CSV
void loadFromCSV() {
    FILE *fp = fopen("equipment.csv", "r");
    if (fp == NULL) return;  // ถ้าไม่มีไฟล์ ให้ข้ามไป
    char line[200];
    fgets(line, sizeof(line), fp); // ข้ามบรรทัด header
    while (fgets(line, sizeof(line), fp)) {
        sscanf(line, "%49[^,],%9[^,],%19[^,],%14[^\n]",
               list[count].name, list[count].id,
               list[count].status, list[count].date);
        count++;
    }
    fclose(fp);
}

// บันทึกข้อมูลลงไฟล์ CSV
void saveToCSV() {
    FILE *fp = fopen("equipment.csv", "w");
    fprintf(fp, "EquipmentName,EquipmentID,Status,MaintenanceDate\n");
    for (int i = 0; i < count; i++) {
        fprintf(fp, "%s,%s,%s,%s\n",
                list[i].name, list[i].id,
                list[i].status, list[i].date);
    }
    fclose(fp);
}

// เพิ่มอุปกรณ์ใหม่
void addEquipment() {
    printf("ชื่ออุปกรณ์: "); scanf(" %[^\n]", list[count].name);
    printf("หมายเลขอุปกรณ์: "); scanf("%s", list[count].id);
    printf("สถานะ: "); scanf(" %[^\n]", list[count].status);
    printf("วันที่บำรุงรักษา (YYYY-MM-DD): "); scanf("%s", list[count].date);
    count++;
    saveToCSV();
    printf("✅ เพิ่มอุปกรณ์เรียบร้อย!\n");
}

// แสดงอุปกรณ์ทั้งหมด
void displayAll() {
    printf("\n--- รายการอุปกรณ์ทั้งหมด ---\n");
    for (int i = 0; i < count; i++) {
        printf("%s | %s | %s | %s\n",
               list[i].name, list[i].id,
               list[i].status, list[i].date);
    }
}

// เมนูหลัก
void displayMenu() {
    int choice;
    do {
        printf("\n=== ระบบจัดการอุปกรณ์ ===\n");
        printf("1. แสดงรายการอุปกรณ์\n");
        printf("2. เพิ่มอุปกรณ์ใหม่\n");
        printf("0. ออกจากโปรแกรม\n");
        printf("เลือกเมนู: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: displayAll(); break;
            case 2: addEquipment(); break;
            case 0: printf("ออกจากโปรแกรม...\n"); break;
            default: printf("เมนูไม่ถูกต้อง!\n");
        }
    } while (choice != 0);
}

int main() {
    loadFromCSV();
    displayMenu();
    return 0;
}
