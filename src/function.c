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
void trimNewline(char *str) {
    size_t len = strlen(str);
    if (len > 0 && str[len-1] == '\n') {
        str[len-1] = '\0';
    }
}

void toLowerCase(char *str) {
    for (int i = 0; str[i]; i++) {
        str[i] = tolower((unsigned char) str[i]);
    }
}

void searchMachine(Machine *list, int count, char *keyword) {
    int found = 0;

    // แปลง keyword ให้เป็นตัวเล็กทั้งหมด
    toLowerCase(keyword);

    for (int i = 0; i < count; i++) {
        char code[50], name[50], status[50], date[50];

        strcpy(code, list[i].code);
        strcpy(name, list[i].name);
        strcpy(status, list[i].status);
        strcpy(date, list[i].maintenanceDate);

        toLowerCase(code);
        toLowerCase(name);
        toLowerCase(status);
        toLowerCase(date);

        if (strstr(code, keyword) || strstr(name, keyword) ||
            strstr(status, keyword) || strstr(date, keyword)) {
            printf("✅ Found: %s | %s | %s | %s\n",
                   list[i].code, list[i].name,
                   list[i].status, list[i].maintenanceDate);
            found = 1;
        }
    }

    if (!found) {
        printf("❌ No machine found with keyword: %s\n", keyword);
    }
}


//update
void updateMachine(const char *filename, Machine *list, int count) {
    char code[20];
    printf("Enter machine code to update: ");
    scanf("%s", code);

    int found = -1;
    for (int i = 0; i < count; i++) {
        if (strcmp(list[i].code, code) == 0) {
            found = i;
            break;
        }
    }

    if (found == -1) {
        printf("❌ No machine found with code: %s\n", code);
        return;
    }

    int choice;
    printf("What do you want to update?\n");
    printf("1) Name\n");
    printf("2) Code\n");
    printf("3) Status\n");
    printf("4) Maintenance Date\n");
    printf("Choice: ");
    scanf("%d", &choice);

    switch (choice) {
        case 1:
            printf("Enter new name: ");
            scanf(" %[^\n]", list[found].name);
            break;
        case 2:
            printf("Enter new code: ");
            scanf("%s", list[found].code);
            break;
        case 3:
            printf("Enter new status: ");
            scanf(" %[^\n]", list[found].status);
            break;
        case 4:
            printf("Enter new maintenance date (YYYY-MM-DD): ");
            scanf("%s", list[found].maintenanceDate);
            break;
        default:
            printf("❌ Invalid choice\n");
            return;
    }

    // เขียนข้อมูลทั้งหมดกลับไปใหม่
    FILE *fp = fopen(filename, "w");
    if (fp == NULL) {
        printf("❌ Error opening file\n");
        return;
    }
    for (int i = 0; i < count; i++) {
        fprintf(fp, "%s,%s,%s,%s\n",
                list[i].code,
                list[i].name,
                list[i].status,
                list[i].maintenanceDate);
    }
    fclose(fp);

    printf("✅ Machine updated successfully!\n");
}


//delete
void deleteRecordCSV(const char *filename, const char *deleteID) {
    FILE *fp = fopen(filename, "r");
    if (fp == NULL) {
        printf("❌ Failed to open file %s \n", filename);
        return;
    }

    FILE *temp = fopen("temp.csv", "w");
    if (temp == NULL) {
        printf("❌ Failed to open file\n");
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
            printf(" deleted: %s✅ \n", deleteID);
            found = 1;
            // ไม่เขียนบรรทัดนี้ลง temp (ข้าม = ลบ)
            continue;
        }
        // ถ้าไม่ใช่ record ที่ต้องลบ เขียนลง temp
        fputs(line, temp);
    }

    if (!found) {
        printf("⚠️ Undefined Code: %s\n", deleteID);
    }
    fclose(fp);
    fclose(temp);
    remove(filename);
    rename("temp.csv", filename);
}


