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
void addMachine(const char *filename, Machine m);
void searchMachine(const char *filename, const char *code);
void updateMachineStatus(const char *filename, const char *code, const char *newStatus);
void deleteMachine(const char *filename, const char *code);

#endif
