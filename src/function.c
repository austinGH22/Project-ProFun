#include "project.h" //import header

#include<stdio.h>
#include<string.h>
#include<stdlib.h>

//read
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

