#ifndef PROJECT_H
#define PROJECT_H

#define MAX_LINE 256
#define MAX_FIELD 50

#define TEST_FILE "test_data.csv"
#define MOCK_INPUT "mock_input.txt"

typedef struct {
    char name[MAX_FIELD];
    char code[MAX_FIELD];
    char status[MAX_FIELD];
    char maintenanceDate[MAX_FIELD];
} Machine;

void trimNewline(char *str);
void toLowerCase(char *str);
int readCSVToArray(const char *filename, Machine **list);
void addMachine(const char *filename, Machine **list, int *count);
void searchMachine(Machine *list, int count, char *keyword);
void updateMachine(const char *filename, Machine *list, int count);
void deleteRecordCSV(const char *filename, Machine **list, int *count);

//unit test 
void create_test_csv();
void clear_csv();
void test_readCSVToArray_normal();
void test_addMachine_normal();
void test_readCSV_emptyFile();
void test_addMachine_firstEntry();
void test_addMachine_longInput();
void test_readCSV_invalidFormat();
void test_memoryLeaks();

//E2E test
void e2e_test();
#endif 

