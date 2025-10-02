#include "project.h" //import header

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include <ctype.h>

//Read
int readCSVToArray(const char *filename, Machine **list) {
    FILE *fp = fopen(filename, "r");
    if (!fp) {
        perror("File open failed");
        return 0;
    }

    Machine *temp = malloc(MAX_LINE * sizeof(Machine));
    int count = 0;
    char line[256];

    while (fgets(line, sizeof(line), fp)) {
        // ตัด \n หรือ \r ออก
        line[strcspn(line, "\r\n")] = 0;

        // อ่านข้อมูล โดย %[^,] มี space นำหน้า -> ตัดช่องว่างอัตโนมัติ
        if (sscanf(line, " %[^,], %[^,], %[^,], %[^,\n]",
                   temp[count].name,
                   temp[count].code,
                   temp[count].status,
                   temp[count].maintenanceDate) == 4) {
            count++;
        }
    }

    fclose(fp);

    *list = temp;
    return count;
}

//Add
void addMachine(const char *filename, Machine **list, int *count) {
    Machine newMachine;

    printf("Enter machine name: ");
    scanf(" %[^\n]", newMachine.name);

    printf("Enter machine code: ");
    scanf("%s", newMachine.code);

    printf("Enter status: ");
    scanf(" %[^\n]", newMachine.status);

    printf("Enter maintenance date (YYYY-MM-DD): ");
    scanf("%s", newMachine.maintenanceDate);

    // ขยายพื้นที่ array ด้วย realloc
    *list = realloc(*list, (*count + 1) * sizeof(Machine));
    if (*list == NULL) {
        printf("❌ Memory allocation failed.\n");
        return;
    }

    // ใส่ newMachine ไว้ท้าย array
    (*list)[*count] = newMachine;
    (*count)++;

    // เขียนลงไฟล์ CSV
    FILE *fp = fopen(filename, "a");
    if (fp == NULL) {
        printf("❌ Failed to open file.\n");
        return;
    }
    fprintf(fp, "%s,%s,%s,%s\n",
            newMachine.name,
            newMachine.code,
            newMachine.status,
            newMachine.maintenanceDate);
    fclose(fp);

    printf("✅ Machine added successfully!\n");
}

//search
// ฟังก์ชันแปลง string ให้เป็น lowercase
void toLowerCase(char *str) {
    for (int i = 0; str[i]; i++) {
        str[i] = tolower((unsigned char) str[i]);
    }
}

void searchMachine(Machine *list, int count, const char *keyword) {
    int found = 0;
    char lowerKeyword[100];
    strcpy(lowerKeyword, keyword);
    toLowerCase(lowerKeyword);

    for (int i = 0; i < count; i++) {
        char tempName[50], tempCode[10], tempStatus[20], tempDate[11];

        strcpy(tempName, list[i].name);
        strcpy(tempCode, list[i].code);
        strcpy(tempStatus, list[i].status);
        strcpy(tempDate, list[i].maintenanceDate);

        toLowerCase(tempName);
        toLowerCase(tempCode);
        toLowerCase(tempStatus);
        toLowerCase(tempDate);

        if (strstr(tempName, lowerKeyword) ||
            strstr(tempCode, lowerKeyword) ||
            strstr(tempStatus, lowerKeyword) ||
            strstr(tempDate, lowerKeyword)) {

            printf("\n--- Found ---\n");
            printf("Name: %s\n", list[i].name);
            printf("Code: %s\n", list[i].code);
            printf("Status: %s\n", list[i].status);
            printf("Maintenance Date: %s\n", list[i].maintenanceDate);
            found = 1;
        }
    }

    if (!found) {
        printf("❌ No machine found with keyword: %s\n", keyword);
    }
}
