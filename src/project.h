#ifndef PROJECT_H
#define PROJECT_H

#define MAX_LINE 256
#define MAX_FIELD 50

typedef struct {
    char name[MAX_FIELD];
    char code[MAX_FIELD];
    char status[MAX_FIELD];
    char maintenanceDate[MAX_FIELD];
} Machine;

// ฟังก์ชันหลัก
int readCSVToArray(const char *filename, Machine **list);
void addMachine(const char *filename, Machine **list, int *count);
void trimNewline(char *str);
void toLowerCase(char *str);
void searchMachine(Machine *list, int count, char *keyword);
void updateMachine(const char *filename, Machine *list, int count);
void deleteRecordCSV(const char *filename, Machine **list, int *count);

#endif // PROJECT_H
