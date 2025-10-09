#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "project.h"

#define TEST_FILE "test_data.csv"

void create_test_csv() {
    FILE *fp = fopen(TEST_FILE, "w");
    assert(fp != NULL);
    fprintf(fp,
        "Drill Press,E001,Operational,2025-07-24\n"
        "Lathe Machine,E002,Stopped,2024-06-25\n"
        "Milling Machine,E003,Operational,2024-03-27\n"
    );
    fclose(fp);
}

void clear_csv() {
    FILE *fp = fopen(TEST_FILE, "w");
    assert(fp != NULL);
    fclose(fp);
}

// normal tests
void test_readCSVToArray_normal() {
    printf("\nRunning test_readCSV]ToArray_normal...\n");
    create_test_csv();

    Machine *list = NULL;
    int count = readCSVToArray(TEST_FILE, &list);

    assert(count == 3);
    assert(strcmp(list[0].name, "Drill Press") == 0);
    assert(strcmp(list[1].code, "E002") == 0);
    assert(strcmp(list[2].status, "Operational") == 0);
    assert(strcmp(list[2].maintenanceDate, "2024-03-27") == 0);

    printf("test_readCSVToArray_normal passed!\n");
    free(list);
}

void test_addMachine_normal() {
    printf("\nRunning test_addMachine_normal...\n");
    clear_csv();

    Machine *list = NULL;
    int count = 0;

    FILE *mockInput = fopen("mock_input.txt", "w");
    assert(mockInput != NULL);
    fputs("Test Machine\nE999\nOperational\n2030-01-01\n", mockInput);
    fclose(mockInput);

    freopen("mock_input.txt", "r", stdin);
    addMachine(TEST_FILE, &list, &count);

    Machine *list2 = NULL;
    int count2 = readCSVToArray(TEST_FILE, &list2);

    assert(count2 == 1);
    assert(strcmp(list2[0].name, "Test Machine") == 0);
    assert(strcmp(list2[0].code, "E999") == 0);
    assert(strcmp(list2[0].status, "Operational") == 0);
    assert(strcmp(list2[0].maintenanceDate, "2030-01-01") == 0);

    printf("test_addMachine_normal passed!\n");
    free(list);
    free(list2);
}

// Boundary tests
void test_readCSV_emptyFile() {
    printf("\nRunning test_readCSV_emptyFile...\n");
    clear_csv();

    Machine *list = NULL;
    int count = readCSVToArray(TEST_FILE, &list);

    assert(count == 0);
    printf("test_readCSV_emptyFile passed!\n");
    free(list);
}

void test_addMachine_firstEntry() {
    printf("\nRunning test_addMachine_firstEntry...\n");
    clear_csv();

    Machine *list = NULL;
    int count = 0;

    FILE *mockInput = fopen("mock_input.txt", "w");
    fputs("BoundaryMachine\nE001\nOperational\n2025-12-31\n", mockInput);
    fclose(mockInput);

    freopen("mock_input.txt", "r", stdin);
    addMachine(TEST_FILE, &list, &count);

    Machine *list2 = NULL;
    int count2 = readCSVToArray(TEST_FILE, &list2);

    assert(count2 == 1);
    assert(strcmp(list2[0].code, "E001") == 0);

    printf("test_addMachine_firstEntry passed!\n");
    free(list);
    free(list2);
}

// Extreme tests
void test_addMachine_longInput() {
    printf("\nRunning test_addMachine_longInput...\n");
    clear_csv();

    char longName[300];
    memset(longName, 'A', 299);
    longName[299] = '\0';

    Machine *list = NULL;
    int count = 0;

    FILE *mockInput = fopen("mock_input.txt", "w");
    fprintf(mockInput, "%s\nE123\nStopped\n2031-01-01\n", longName);
    fclose(mockInput);

    freopen("mock_input.txt", "r", stdin);
    addMachine(TEST_FILE, &list, &count);

    Machine *list2 = NULL;
    int count2 = readCSVToArray(TEST_FILE, &list2);

    assert(count2 == 1);
    assert(strncmp(list2[0].name, "A", 1) == 0);  // Should start with 'A'

    printf("test_addMachine_longInput passed!\n");
    free(list);
    free(list2);
}

void test_readCSV_invalidFormat() {
    printf("\nRunning test_readCSV_invalidFormat...\n");

    FILE *fp = fopen(TEST_FILE, "w");
    assert(fp != NULL);
    fprintf(fp, "Missing,Comma,Here\nBrokenLineWithoutEnoughFields\n");
    fclose(fp);

    Machine *list = NULL;
    int count = readCSVToArray(TEST_FILE, &list);

    assert(count >= 0); // Function should not crash
    printf("test_readCSV_invalidFormat passed!\n");

    free(list);
}

// memory safety tests
void test_memoryLeaks() {
    printf("\nRunning test_memoryLeaks...\n");
    create_test_csv();

    for (int i = 0; i < 100; i++) {
        Machine *list = NULL;
        int count = readCSVToArray(TEST_FILE, &list);
        free(list); // make sure every allocation freed
    }

    printf("test_memoryLeaks passed! (use Valgrind to confirm)\n");
}

// main
int main() {
    printf("===== UNIT TEST START =====\n");

    //Normal Tests
    test_readCSVToArray_normal();
    test_addMachine_normal();

    //Boundary Tests
    test_readCSV_emptyFile();
    test_addMachine_firstEntry();

    //Extreme Tests
    test_addMachine_longInput();
    test_readCSV_invalidFormat();

    //Memory Safety Test
    test_memoryLeaks();

    printf("\n===== ALL TESTS PASSED SUCCESSFULLY =====\n\n");
    return 0;
}
