#ifndef PROJECT_H
#define PROJECT_H

#define MAX_LINE 256

// โครงสร้างข้อมูลเครื่องจักร
typedef struct {
    char name[50];
    char code[20];
    char status[20];
    char maintenanceDate[20];
} Machine;

int readCSVToArray(const char *filename, Machine **list);
void addMachine(const char *filename, Machine **list, int *count);
void trimNewline(char *str); 
void toLowerCase(char *str); 
void searchMachine(Machine *list, int count, char *keyword);
void updateMachine(const char *filename, Machine *list, int count);
void deleteRecordCSV(const char *filename, const char *deleteID);

#endif
